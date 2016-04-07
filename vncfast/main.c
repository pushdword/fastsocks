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
#define vncfast_ver "1.01"
#define _debugd(fmt, args...) fprintf(stderr, fmt, ##args);
#define _debugi(fmt, args...) fprintf(stdout, fmt, ##args);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <termios.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "regmacros.h"
#include "auth_struct.pb-c.h"
#include "fastsocks.h"
#include "../Register/debug.h"
/* OpenSSL headers */

#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

char token[STRING_SIZE];
/*
 * 
 */
void usage(){
    printf(
       "VNCFast version %s\n"
       "Options are:\n"
       "    -r: set remote IPv4 of register server\n"
       "    -p: set remote port of register server\n"
       "    -l: set local address of VNC server\n"
       "    -f: set file path to username:password\n"
       "    -i: set username and password from stdin\n"
            ,vncfast_ver);
}

int main(int argc, char** argv) {
    
    /*
     * arguments in VNCFast
     * -r remote ipv4 server
     * -p remote port
     * -l local address of VNC server
     * -f file for username and PW
     * -i ignore file for username and use stdin
     */
    if(argc==1){
        usage();
        return 1;
    }
    struct sockaddr_in rsv,lsv;
    char u[STRING_SIZE],p[STRING_SIZE];
    uint32_t rport=0;
    short rflag=0,pflag=0,lflag=0,fflag=0,iflag=0;
    opterr = 0;
    int c=0,ffile;
    while ((c = getopt (argc, argv, "r:p:l:f:i:")) != -1){
      switch (c)
       {
            case 'r':{
                //validation
                if(inet_aton(optarg,&rsv.sin_addr)==0){
                    _debugd("Invalid IPv4 address:%s\n",optarg);return 1;
                }
              rflag = 1;
              break;
            }
            case 'l':{
             if(inet_aton(optarg,&lsv.sin_addr)==0){
                 _debugd("Invalid IPv4 address:%s\n",optarg);return 1;
             }
             lflag=1;
             break;
            }
            case 'p':{
                rport=(uint32_t)strtol(optarg,0,10);
                if(rport>0 && rport<=65535){
                    pflag = 1;
                }
                else{
                    _debugd("Invalid port %u\n",rport);return 1;
                }
              break;
            }
          case 'f':{
              ffile=open(optarg,O_RDONLY);
              if(ffile>0){
                  perror("open()");
                  _debugd("Enter a valid file path\n");
                  usage();
                  return 1;
              }
              char line[STRING_SIZE];
              if(!fgets(line,STRING_SIZE,ffile)){
                  _debugd("%s seems to be empty\n",optarg);
                  return 1;
              }
              int ar=0;
              char *token=strtok(line,":");
              if(token==NULL){
                  _debugd("%s has errors\n",optarg);
                  return 1;
              }
              while (token != NULL) {
                  switch(ar){
                      case 0:{
                          strncpy(u,token,STRING_SIZE);
                          break;
                      }
                      case 1:{
                          strncpy(p,token,STRING_SIZE);
                          break;
                      }
                      default:{
                          _debugd("Syntax error on file %s\nShould be only one line and username:password",optarg);
                          return 1;
                      }
                  }
                  token = strtok(NULL,":");ar++;
              }
              fflag=1;
              break;
          }
          case 'i':{
                _debugi("Enter username[%d]:",STRING_SIZE);
                fgets(u,STRING_SIZE,stdin);
                _debugi("Enter password[%d]:",STRING_SIZE);
                struct termios oflags, nflags;
                /* disabling echo */
                tcgetattr(fileno(stdin), &oflags);
                nflags = oflags;
                nflags.c_lflag &= ~ECHO;
                nflags.c_lflag |= ECHONL;
                if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0) {
                    perror("tcsetattr");
                    return EXIT_FAILURE;
                }
                fgets(p,STRING_SIZE,stdin);
                /* restore terminal */
                if(tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0) {
                    perror("tcsetattr");
                    return EXIT_FAILURE;
                }
                break;
          }
          case '?':{
                _debugd("Invalid argument: %s\n",optarg);
                return 1;
                break;
            }
          default:{
              abort();
            }
        }
    }
    if(rflag==0) {
        _debugd("-r needed\n");
        usage();
        return 1;
    }
    if(pflag==0){
        _debugd("-p needed\n");
        usage();
        return 1;
    }
    if(lflag==0){
        _debugd("-l needed\n");
        usage();
        return 1;
    }
    if(fflag==0 && iflag==0){
        _debugd("-f or -i needed\n");
        usage();
        return 1;
    }
    if(fflag==1 && iflag==1){
        _debugd("only -f or -i is allowed! Not both!\n");
        usage();
        return 1;
    }
    
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
    /*
     *  1 - Connect to server.
     */
    BIO * bio;
    char host_port[30];snprintf(host_port,30,"%s:%u",inet_ntoa(rsv.sin_addr),rport);
    bio=init_fastsocks(host_port);
    /*
     * Send auth_sol packets
     */
    void *b;
    unsigned len;
    struct _AuthenticateSolicitation atsol = AUTHENTICATE_SOLICITATION__INIT;
    atsol.header=0x1; //sol
    atsol.has_header=1;
    atsol.usr = u;
    atsol.pw = p;
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

