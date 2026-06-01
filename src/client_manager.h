#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <netinet/in.h>
#include <time.h>

#define MAX_CLIENTS 128

typedef struct {
    int  fd;
    char ip[INET_ADDRSTRLEN];
    int  port;
    time_t connected_at; 
} client_t;

void      client_add(int fd, struct sockaddr_in *addr);
void      client_remove(int fd);
client_t *client_find(int fd);
int       client_count(void);
void      client_foreach(void (*callback)(int fd, void *arg), void *arg);

#endif
