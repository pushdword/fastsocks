/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: pushdword
 *
 * Created on April 3, 2016, 11:59 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "regmacros.h"
#include "fastsocks.h"
#include "auth_struct.pb-c.h"
/* OpenSSL headers */

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/* Initializing OpenSSL */

/*
 * Service
 */

int processClient(BIO* clientbio){
    struct _AuthenticateSolicitation *atsol;
    void *buffer = malloc(512);
    int drev;
    drev = BIO_read(clientbio,buffer,512);
    if(drev<=0)
        exit(0);
    atsol=authenticate_solicitation__unpack(NULL,drev,buffer);
    if(atsol->has_header==1)
        fprintf(stdout,"header:%d\n",atsol->header);
    fprintf(stdout,"username:%s\npassword:%s\n\n\n",atsol->usr,atsol->pw);
    _dumpbuffer(buffer,drev);
    free(buffer);
    return 0;
}

int main(int argc, char** argv) {
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    BIO* serverBIO,*cbio;
    serverBIO=bind_local("3434");
    processClient(serverBIO);
    return (EXIT_SUCCESS);
}

