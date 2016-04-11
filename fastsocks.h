
/* 
 * File:   fastsocks.h
 * Author: pushdword
 *
 * Created on March 26, 2016, 10:15 PM
 */


#ifndef FASTSOCKS_H
#define FASTSOCKS_H
#include <stdint.h>
#ifndef REGMACROS_H
#include "regmacros.h"
#endif
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>


/*
 * LISTS
 */
/*
 * In order to take of multiple clients with threads we need to use lists.
 * We also need a lock system too.
 */
typedef struct list_bio{
    int index;
    BIO *b;
    struct list_bio* next;
}listbio_t;

typedef struct list_ctx{
    int index;
    SSL_CTX *ctx;
    struct list_ctx* next;
}listctx_t;

typedef struct list_threads{
    int index;
    pthread_t thread;
    struct list_threads* next;    
}listthreads_t;
typedef struct list_ssl{
    int index;
    SSL *ssl;
    struct list_ssl* next;
}listssl_t;

BIO* bind_local(char* port);
BIO* init_fastsocks(char*host_port);
void _dumpbuffer(void*data,size_t size);
//need these functions
void _dumplist_bio(listbio_t *list);
void _dumplist_ctx(listctx_t *list);
void _dumplist_threads(listthreads_t *list);
void _dumplist_ssl(listssl_t *list);

int addbiolist(listbio_t *list);
int addctxlist(listbio_t *list);
int addthreadlist(listbio_t *list);
int addssllist(listssl_t* list);

int removebiolistbyindex(listbio_t *list,int index);
int removectxlistbyindex(listctx_t *list,int index);
int removethreadlistbyindex(listthreads_t *list,int index);
int removessllistbyindex(listssl_t *list,int index);

int insertbiolist(listbio_t *list,int index);
int insertctxlist(listctx_t *list,int index);
int insertthreadlist(listthreads_t *list,int index);
int insertssllist(listssl_t *list,int index);


listbio_t* getbiolistbyindex(listbio_t *list,int index);
listctx_t* getctxlistbyindex(listctx_t *list,int index);
listthreads_t* getthreadlistbyindex(listthreads_t *list,int index);
listssl_t* getssllistbyindex(listssl_t *list,int index);

BIO* getbiobyindex(listbio_t *list,int index);
SSL_CTX* getctxbyindex(listctx_t *list,int index);
pthread_t getthreadbyindex(listthreads_t *list,int index);
SSL* getsslbyindex(listssl_t *list,int index);

/*
 
 *We have a server running a spacial service. We call it VNC Repeater.
 *When a client double clicks our application it will start on localhost a reverse
 * communication with their solicitation to register on server.
 * Server will find a free number and give it to the client.
 * Client must send an ack to service in order to register.
 * When it is done it will stablish an reverse VNC connection to our service.
 * Now client waits for the other end to connects.
 * 
 * The other end connects to this service.
 * It must authenticate first.
 * When authed so it must requires to connect to register number client (VNC reverse).
 * This service must find where it is (probably in mysql db?)
 * When it finds then send to the caller a packet saying 'ok, connect to our port XXXXX from your YYYYY port'.
 * This port will be linked (transfering) to the reverse VNC client but it MUST mach source ip, source port.
 * Maybe there is another way to autenticate? Caller and VNC server can comunicate to a localhost service that
 * talks to this service with header tokens like in HTTP protocol.
 * I must find a way to encrypt everything. 
 */

/*
enum header_type{
    reg_sol, //register solicitation -- must be client
    reg_res, //register response -- only the server can send
    reg_ack, //register acknowledgment -- only client must send it. 
    
    auth_sol, //caller authentication request
    auth_ack, //server acknowledgment to auth. only sends it when caller is authed. if not just ignores. *evil*
    
    conn_sol, //caller solicitation - wants to connect to client with reg number
    conn_res, //server response to the solicitation.
    conn_ack, //caller acknowledgment to the response if response its ACCEPTED (1).

};
*/

typedef struct _reg_sol{
    char header; //what header is this.
    char token[STRING_SIZE]; //random token by client.
}reg_sol;

typedef struct _reg_res{
    char header; //what header is this.
    char token[STRING_SIZE]; //if the same it's registed ok
    char reg[STRING_SIZE]; //registation number. it will be for dotted number.
}reg_res;

typedef struct _reg_ack{
    char header; //what header is this.
    char token[STRING_SIZE]; //end again the same token.
    char reg[STRING_SIZE]; //must send again the same reg number.
}reg_ack;

typedef struct _auth_sol{
    char header; //what header is this.
    char usr[MAX_FIELD_LEN];
    char pw[MAX_FIELD_LEN];
}auth_sol;

typedef struct _auth_ack{
    char header; //what header is this.
    char token[STRING_SIZE]; //use this to talk with server.
}auth_ack;

typedef struct _conn_sol{
    char header; //what header is this.
    char token[STRING_SIZE]; //auth token.
    char reg[STRING_SIZE]; //who the caller wants to connect to
}conn_sol;

typedef struct _conn_res{
    char header; //what header is this.
    uint32_t ip; //connect to this IP
    uint16_t port; //and to this port in order to connect
}conn_res;

typedef struct _conn_ack{
    char header; //what header is this.
    char token[STRING_SIZE];
    uint32_t ip; //connecting to this ip
    uint16_t port; //to this port.
}conn_ack;


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* FASTSOCKS_H */

