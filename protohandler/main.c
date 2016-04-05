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
#include "../Register/regmacros.h"
#include "fastsocks.h"
#include "auth_struct.pb-c.h"
/* OpenSSL headers */

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

/* Initializing OpenSSL */



/*
 * 
 */
int main(int argc, char** argv) {
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    BIO* bio,*cbio;
    
    struct _AuthenticateSolicitation *atsol;
    void *buffer = malloc(512);
    int drev;
    bio=bind_local("3434");
    cbio = BIO_pop(bio);
    
    drev = BIO_read(bio,buffer,512);
    assert(drev>=0);
    fprintf(stdout,"recv:%d\n",drev);
    atsol=authenticate_solicitation__unpack(NULL,drev,buffer);
    if(atsol->has_header==1)
        fprintf(stdout,"header:%d\n",atsol->header);
    fprintf(stdout,"username:%s\npassword:%s\n",atsol->usr,atsol->pw);

    
    free(buffer);
    return (EXIT_SUCCESS);
}

