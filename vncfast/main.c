/*
 * The point of this is to bind a localhost port to connect the local VNC server through that port
 * and it will connect to a remote server running fastsocks service.
 * This service will register or not and connect it to clients.
 * 1 - Ask for authenticate (I need a way to use a username and maybe password?)
 * 2 - If already authed just panic. In service when the connection breaks it will remove from db. so no worries?
 * 3 - When received the token it must use it in order to exchange stuff we will see:
 * 4 - asks for registation (aka asks for a registation number like in other remote services)
 * 5 - When all done then probe the system if 5900 is free.
 * 6 - If is free then starts vnc server.
 * 7 - Shows to the user the registation number.
 * 8 - When fastsocks service tells incoming client so we need to parse the IPv4 and 16bit Port integer to connect.
 * 9 - When done transfer the connection will be made to that ip and port.
 * *   transfer it to VNC server port. and you are done :D
 */

/* 
 * File:   main.c
 * Author: pushdword
 *
 * Created on March 31, 2016, 10:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "regmacros.h"
#include "auth_struct.pb-c.h"
#include "fastsocks.h"
/* OpenSSL headers */

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

char token[STRING_SIZE];
/*
 * 
 */


int main(int argc, char** argv) {
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    /*
     *  1 - Connect to server.
     */
    BIO * bio;    
    bio=init_fastsocks("127.0.0.1:3434");
    /*
     * Send auth_sol packets
     */
    void *b;
    unsigned len;
    struct _AuthenticateSolicitation atsol = AUTHENTICATE_SOLICITATION__INIT;
    atsol.header=0x1; //sol
    atsol.has_header=1;
    atsol.usr = "istoeumutilizadormaior";
    atsol.pw = "p!aSDskaqWEsnaqwendkDAS";
    len = authenticate_solicitation__get_packed_size(&atsol);
    /*
     * 
     * Researching *need to send struct over a networked fd*
     * 
     */
    b=malloc(len);
    authenticate_solicitation__pack(&atsol,b);
    /*
     * Ok it works. Now send it via socket :D
     */
    BIO_write(bio,b,len);
    free(b);
    //now we wait for the response.
    waitForToken();
    
    //wait.
    BIO_reset(bio);
    BIO_free_all(bio);
    return (EXIT_SUCCESS);
}

