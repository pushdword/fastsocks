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
    drev = BIO_read(bio,buffer,512);
    assert(drev>0);
    atsol=authenticate_solicitation__unpack(NULL,drev,buffer);
    if(atsol->has_header==1)
        fprintf(stdout,"header:%d\n",atsol->header);
    fprintf(stdout,"username:%s\npassword:%s\n\n\n",atsol->usr,atsol->pw);
    _dumpbuffer(buffer,drev);
    free(buffer);
    return (EXIT_SUCCESS);
}

