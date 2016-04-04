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

/*
 * 
 */
int main(int argc, char** argv) {
    int sfd=bind_local("127.0.0.1","3434");
    
    struct _AuthenticateSolicitation *atsol;
    void *buffer = malloc(14);
    int drev = recv(sfd,buffer,14,NULL);
    fprintf(stdout,"recv:%d\n",drev);
    atsol=authenticate_solicitation__unpack(NULL,14,buffer);
    fprintf(stdout,"header:%d\nusername:%s\npassword:%s\n",atsol->header,atsol->usr,atsol->pw);
    
    //fwrite(buffer,14,1,stdout);
    
    
    
    free(buffer);
    return (EXIT_SUCCESS);
}

