#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "fastsocks.h"
#include "auth_struct.pb-c.h"
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/ssl.h> //using TLSv1_2

#define BACKLOG  10 

BIO * init_fastsocks(char* host_port)
{
/*
    SSL_library_init();
    SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
    SSL * ssl;
    if(! SSL_CTX_load_verify_locations(ctx, NULL, "/etc/ssl/certs/"))
    {
        perror("couldn't load certificate!\n");
        exit(1);
    }
    
    BIO *bio;
    bio = BIO_new_ssl_connect(ctx);
    BIO_get_ssl(bio, & ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    BIO_set_conn_hostname(bio, host_port);

    if(bio == NULL)
    {
        perror("BIO_new_connect() to ");
        printf("%s\n",host_port);
        exit(1);
    }

    if(BIO_do_connect(bio) <= 0)
    {
        perror("BIO_do_connect()\n");
        exit(1);
    }
*/
     BIO *sbio, *out;
     SSL_CTX *ctx;
     SSL *ssl;

     /* We would seed the PRNG here if the platform didn't
      * do it automatically
      */
     SSL_library_init();
     ctx = SSL_CTX_new(TLSv1_2_client_method());

     /* We'd normally set some stuff like the verify paths and
      * mode here because as things stand this will connect to
      * any server whose certificate is signed by any CA.
      */

     sbio = BIO_new_ssl_connect(ctx);

     BIO_get_ssl(sbio, &ssl);

     if(!ssl) {
       fprintf(stderr, "Can't locate SSL pointer\n");
       /* whatever ... */
       exit(1);
     }

     /* Don't want any retries */
     SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

     /* We might want to do other things with ssl here */

     /* An empty host part means the loopback address */
     BIO_set_conn_hostname(sbio, host_port);

     out = BIO_new_fp(stdout, BIO_NOCLOSE);
     if(BIO_do_connect(sbio) <= 0) {
            fprintf(stderr, "Error connecting to server\n");
            ERR_print_errors_fp(stderr);
            /* whatever ... */
     }

     if(BIO_do_handshake(sbio) <= 0) {
            fprintf(stderr, "Error establishing SSL connection\n");
            ERR_print_errors_fp(stderr);
            /* whatever ... */
     }
    
    return sbio;
}


void _dumpbuffer(void*data,size_t size){
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i) {
        printf("%02X ", ((unsigned char*)data)[i]);
        if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
            ascii[i % 16] = ((unsigned char*)data)[i];
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == size) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf("|  %s \n", ascii);
            } else if (i+1 == size) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    printf(" ");
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
}


BIO* bind_local(char* port){
    BIO *sbio, //server bio
        *bbio, //buffer bio
        *acpt, //accept bio
        *out; //out? bio
    SSL_CTX *ctx;
    SSL *ssl;

    /* Might seed PRNG here */
    SSL_library_init();
    ctx = SSL_CTX_new(TLSv1_2_server_method()); 

    if (!SSL_CTX_use_certificate_file(ctx,"/etc/ssl/certs/server.pem",SSL_FILETYPE_PEM)
           || !SSL_CTX_use_PrivateKey_file(ctx,"/etc/ssl/protohandler.pem",SSL_FILETYPE_PEM) //meh I did generate it and encrypt. :/
           || !SSL_CTX_check_private_key(ctx)) {

           fprintf(stderr, "Error setting up SSL_CTX\n");
           ERR_print_errors_fp(stderr);
           return 0;
    }

    /* Might do other things here like setting verify locations and
     * DH and/or RSA temporary key callbacks
     */

    /* New SSL BIO setup as server */
    sbio=BIO_new_ssl(ctx,0);

    BIO_get_ssl(sbio, &ssl);

    if(!ssl) {
      fprintf(stderr, "Can't locate SSL pointer\n");
      /* whatever ... */
    }

    /* Don't want any retries */
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    /* Create the buffering BIO */

    bbio = BIO_new(BIO_f_buffer());

    /* Add to chain */
    sbio = BIO_push(bbio, sbio);

    acpt=BIO_new_accept(port);

    /* By doing this when a new connection is established
     * we automatically have sbio inserted into it. The
     * BIO chain is now 'swallowed' by the accept BIO and
     * will be freed when the accept BIO is freed. 
     */

    BIO_set_accept_bios(acpt,sbio);

    out = BIO_new_fp(stdout, BIO_NOCLOSE); //if you write to out is the same as writing into stdout

    /* Setup accept BIO */
    if(BIO_do_accept(acpt) <= 0) {
           fprintf(stderr, "Error setting up accept BIO\n");
           ERR_print_errors_fp(stderr);
           return 0;
    }

/* Now wait for incoming connection */
    if(BIO_do_accept(acpt) <= 0) {
           fprintf(stderr, "Error in connection\n");
           ERR_print_errors_fp(stderr);
           return 0;
    }
    /* We only want one connection so remove and free
     * accept BIO
     */
    sbio = BIO_pop(acpt);
    BIO_free_all(acpt);

    //server bio do the handshake to the clients.
    if(BIO_do_handshake(sbio) <= 0) {
           fprintf(stderr, "Error in SSL handshake\n");
           ERR_print_errors_fp(stderr);
           exit(1);
    }
    return sbio; //should it?
}

// STOPPED HERE. CONTINUE TOMOROW
char *waitForToken(BIO* sbio){
    int correct=0;
    while(!correct){
        struct _AuthenticateResponse *atres;
        void *buffer = malloc(512);
        int drev;
        drev = BIO_read(sbio,buffer,512);
        _debugi("read:%d\n",drev);
        assert(drev>0);
        atres = authenticate_response__unpack(NULL,drev,buffer);
        /*
         * checkup for protocol
         */
        if(atres->has_header!=1){
            continue;//must have header.
        }
        //ok if it has
        if(atres->header==0x2){ //if is a response
            return atres->token;
        }
    }
}
