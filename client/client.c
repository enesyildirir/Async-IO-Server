/* client/client.c
 * Kisi 3 — Test istemcisi
 *
 * GÖREV: Sunucuya bağlanan test istemcisini yaz.
 *
 * Kullanım: ./bin/client <ip> <port>
 * Örnek:    ./bin/client 127.0.0.1 8080
 *
 * Gereksinimler:
 *   1. socket() ile TCP soketi aç
 *   2. connect() ile sunucuya bağlan
 *   3. select() ile hem STDIN hem soketi aynı anda dinle:
 *      - Klavyeden giriş → send() ile sunucuya gönder
 *      - Soket verisi → ekrana yazdır
 *   4. Bağlantı kesilirse temiz çık
 *
 * İpuçları:
 *   - FD_ZERO, FD_SET, FD_ISSET makroları
 *   - fgets() ile klavye girişi al
 *   - recv() dönüşü 0 ise sunucu kapandı demek
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Kullanim: %s <ip> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* TODO: socket oluştur */

    /* TODO: sunucuya bağlan */

    /* TODO: select() döngüsü — klavye ve soket */

    return EXIT_SUCCESS;
}
