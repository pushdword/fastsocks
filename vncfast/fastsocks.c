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
#include <openssl/ssl.h>
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
     ctx = SSL_CTX_new(SSLv23_client_method());

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

int bind_local(const char *addr,const char *port){
    int sock;
    struct addrinfo hints, *res;
    int reuseaddr = 1; /* True */
    const char *local_host, *local_port;
    
    local_host = addr;
    local_port = port;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(local_host, local_port, &hints, &res) != 0) {
        perror("getaddrinfo");
        return 1;
    }

    /* Create the socket */
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
        perror("socket");
        freeaddrinfo(res);
        return 1;
    }

    /* Enable the socket to reuse the address */
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1) {
        perror("setsockopt");
        freeaddrinfo(res);
        return 1;
    }

    /* Bind to the address */
    if (bind(sock, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        freeaddrinfo(res);
        return 1;
    }

    /* Listen */
    if (listen(sock, BACKLOG) == -1) {
        perror("listen");
        freeaddrinfo(res);
        return 1;
    }

    freeaddrinfo(res);
    
    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in their_addr;
    return accept(sock, (struct sockaddr*)&their_addr, &size);
}