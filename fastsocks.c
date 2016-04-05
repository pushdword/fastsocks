#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fastsocks.h"
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/ssl.h> //missing TLS_server_method *

#define BACKLOG  10 

BIO * init_fastsocks(char* host_port)
{
    BIO *bio;
    bio = BIO_new_connect(host_port);
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
    
    return bio;
}

BIO* bind_local(char* port){
/*
    SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
    SSL * ssl;
    if(! SSL_CTX_load_verify_locations(ctx, NULL, "/etc/ssl/certs/"))
    {
        perror("couldn't load certificate!\n");
        exit(1);
    }
    
    BIO *bio;
    bio = BIO_new_ssl(ctx);
    BIO_get_ssl(bio, & ssl);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    bio = BIO_new_accept(port);
     if(BIO_do_accept(bio) <= 0) {
            fprintf(stderr, "Error accepting connection\n");
            ERR_print_errors_fp(stderr);
            exit(0);                
     }
    return bio;
*/
    
    BIO *sbio, *bbio, *acpt, *out;
    int len;
    char tmpbuf[1024];
    SSL_CTX *ctx;
    SSL *ssl;

    /* Might seed PRNG here */
    SSL_library_init();
    ctx = SSL_CTX_new(SSLv23_server_method()); //help here. TLS_server_method undefined. :(

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

    out = BIO_new_fp(stdout, BIO_NOCLOSE);

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

    if(BIO_do_handshake(sbio) <= 0) {
           fprintf(stderr, "Error in SSL handshake\n");
           ERR_print_errors_fp(stderr);
           exit(1);
    }
    return sbio;
}