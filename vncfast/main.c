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
#include "regmacros.h"
#include "fastsocks.h"
char token[STRING_SIZE];
/*
 * 
 */


int main(int argc, char** argv) {
    /*
     *  1 - Connect to server.
     */
    
    char *srv="nop.pt"; //testing server
    char *port="3434";//for testing
    int fd_s;
    
    fd_s=init_fastsocks(srv,port);
    if(fd_s==-1){
        exit(1);
    }
    /*
     * Send auth_sol packets
     */
    struct auth_sol atsol;
    header_type h;
    atsol.header=h.auth_sol;
    snprintf(atsol.usr,MAX_FIELD_LEN,"user1");//for testing ofc
    snprintf(atsol.pw,MAX_FIELD_LEN,"pass1");
    
    fprintf(stdout,"INFO:\tUsing default user and password for testing only\n");
    
    /*
     * 
     * Researching *need to send struct over a networked fd*
     * 
     */
    
    return (EXIT_SUCCESS);
}

