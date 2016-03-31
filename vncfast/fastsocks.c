#include <unistd.h>
#include <stdlib.h>
#include <net/if.h>//AF_INET and stuff
#include <linux/net.h> //for now
#include <fcntl.h>
#include "fastsocks.h"

int init_fastsocks(const char *remote_host, const char *remote_port)
{
    struct addrinfo hints, *res;
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