/* src/epoll_core.h
 * Kisi 1 — epoll event loop arayüzü
 */
#ifndef EPOLL_CORE_H
#define EPOLL_CORE_H

#include <sys/epoll.h>
#include <netinet/in.h>

#define MAX_EVENTS  64
#define BUF_SIZE    4096

void server_run(int port);
void handle_new_connection(int epfd, int listen_fd);
void handle_client_data(int epfd, int client_fd);
void handle_disconnect(int epfd, int client_fd);

#endif
