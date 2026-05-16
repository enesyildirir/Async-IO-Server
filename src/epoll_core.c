/* src/epoll_core.c
 * Kisi 1 — epoll event loop implementasyonu
 *
 * Sorumluluk:
 *   - TCP dinleme soketini kurar
 *   - epoll ile olayları bekler
 *   - Yeni bağlantı / veri / kopma olaylarını yönlendirir
 *   - Kisi 2'nin modüllerini (client_manager, broadcast) çağırır
 */
#include "epoll_core.h"
#include "client_manager.h"
#include "broadcast.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* Yardımcı: fd'yi non-blocking yap */
static int set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

/* Yardımcı: epoll'a fd ekle */
static int epoll_add(int epfd, int fd, uint32_t events)
{
    struct epoll_event ev;
    ev.events  = events;
    ev.data.fd = fd;
    return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}

/* Dinleme soketini oluştur  */
static int create_listen_socket(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port        = htons(port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(EXIT_FAILURE);
    }
    if (listen(fd, SOMAXCONN) < 0) {
        perror("listen"); exit(EXIT_FAILURE);
    }

    set_nonblocking(fd);
    return fd;
}

/*  Yeni bağlantıyı kabul et  */
void handle_new_connection(int epfd, int listen_fd)
{
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);

    int client_fd = accept(listen_fd,
                           (struct sockaddr *)&client_addr,
                           &addrlen);
    if (client_fd < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
            perror("accept");
        return;
    }

    set_nonblocking(client_fd);

    /* Kisi 2'nin modülü */
    client_add(client_fd, &client_addr);
    epoll_add(epfd, client_fd, EPOLLIN | EPOLLET);

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
    log_info("Yeni baglanti: %s:%d (fd=%d) | Toplam: %d",
             ip, ntohs(client_addr.sin_port),
             client_fd, client_count());

    char sys_msg[256];
    snprintf(sys_msg, sizeof(sys_msg),
             "[Server] %s katildi. Bagli istemci: %d\n",
             ip, client_count());
    broadcast_system_msg(sys_msg);

    char welcome[256];
    snprintf(welcome, sizeof(welcome),
             "[Server] Hosgeldiniz! Bagli istemci sayisi: %d\n",
             client_count());
    send(client_fd, welcome, strlen(welcome), MSG_NOSIGNAL);
}

/*  Bağlantı kopma  */
void handle_disconnect(int epfd, int client_fd)
{
    client_t *c = client_find(client_fd);
    char ip[INET_ADDRSTRLEN] = "bilinmiyor";
    if (c) strncpy(ip, c->ip, INET_ADDRSTRLEN);

    log_info("Baglanti koptu: fd=%d (%s) | Kalan: %d",
             client_fd, ip, client_count() - 1);

    char sys_msg[256];
    snprintf(sys_msg, sizeof(sys_msg),
             "[Server] %s ayrildi. Bagli istemci: %d\n",
             ip, client_count() - 1);

    epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, NULL);
    client_remove(client_fd);
    close(client_fd);

    broadcast_system_msg(sys_msg);
}

/* Gelen veriyi oku ve yayınla */
void handle_client_data(int epfd, int client_fd)
{
    char buf[BUF_SIZE];
    ssize_t n;

    while (1) {
        n = recv(client_fd, buf, sizeof(buf) - 1, 0);

        if (n > 0) {
            buf[n] = '\0';
            client_t *c = client_find(client_fd);
            char out[BUF_SIZE + 64];
            snprintf(out, sizeof(out), "[%s] %s",
                     c ? c->ip : "?", buf);
            log_info("fd=%d → %zd byte", client_fd, n);
            broadcast_message(client_fd, out, strlen(out));

        } else if (n == 0) {
            handle_disconnect(epfd, client_fd);
            return;

        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            log_warn("recv hatasi fd=%d", client_fd);
            handle_disconnect(epfd, client_fd);
            return;
        }
    }
}

/* Ana event döngüsü */
void server_run(int port)
{
    int listen_fd = create_listen_socket(port);

    int epfd = epoll_create1(0);
    if (epfd < 0) { perror("epoll_create1"); exit(EXIT_FAILURE); }

    epoll_add(epfd, listen_fd, EPOLLIN);

    log_info("====================================");
    log_info("  Async I/O Broadcast Sunucusu");
    log_info("  Port : %d", port);
    log_info("  Maks istemci: %d", MAX_CLIENTS);
    log_info("====================================");

    struct epoll_event events[MAX_EVENTS];

    while (1) {
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (nfds < 0) { perror("epoll_wait"); break; }

        for (int i = 0; i < nfds; i++) {
            int      fd = events[i].data.fd;
            uint32_t ev = events[i].events;

            if (fd == listen_fd) {
                handle_new_connection(epfd, listen_fd);
            } else if (ev & (EPOLLERR | EPOLLHUP)) {
                handle_disconnect(epfd, fd);
            } else if (ev & EPOLLIN) {
                handle_client_data(epfd, fd);
            }
        }
    }

    close(listen_fd);
    close(epfd);
}
