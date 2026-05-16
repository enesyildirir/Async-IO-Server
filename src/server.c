/* src/server.c
 * Kisi 1 — Giriş noktası
 * Komut satırından port alır, sunucuyu başlatır.
 */
#include "epoll_core.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int port = 8080;

    if (argc >= 2) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            fprintf(stderr, "Gecersiz port: %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    server_run(port);
    return EXIT_SUCCESS;
}
