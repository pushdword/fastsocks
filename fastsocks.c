#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>

#include "fastsocks.h"

#define BACKLOG  10 

int init_fastsocks(const char *remote_host, const char *remote_port)
{
    struct addrinfo hints;
    struct addrinfo *res;
    int server = -1;
    unsigned int disconnected = 0;
    fd_set set;
    unsigned int max_sock;

    /* Get the address info */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(remote_host, remote_port, &hints, &res) != 0) {
        perror("getaddrinfo");
        return -1;
    }

    /* Create the socket */
    server = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server == -1) {
        perror("socket");
        return;
    }

    /* Connect to the host */
    if (connect(server, res->ai_addr, res->ai_addrlen) == -1) {
        perror("connect");
        return;
    }
    return server;
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