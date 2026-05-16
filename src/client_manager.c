/* src/client_manager.c
 * Kisi 2 — Bağlı istemci listesi implementasyonu
 *
 * GÖREV: 5 fonksiyonu implement et.
 *
 * Veri yapısı:
 *   static client_t clients[MAX_CLIENTS];
 *   fd == 0 olan slot BOŞ demektir.
 *
 * İpuçları:
 *   - client_add: boş slot bul (fd==0), doldur, client_cnt++
 *   - client_remove: fd'ye göre bul, memset ile sıfırla, client_cnt--
 *   - client_find: fd'ye göre bul, pointer döndür (bulamazsan NULL)
 *   - client_foreach: her dolu slot için callback(fd, arg) çağır
 *   - inet_ntop() ile IP adresini stringe çevir
 */
#include "client_manager.h"
#include "utils.h"

#include <string.h>
#include <arpa/inet.h>

static client_t clients[MAX_CLIENTS];
static int      client_cnt = 0;

void client_add(int fd, struct sockaddr_in *addr)
{
    /* TODO: implement et */
    (void)fd; (void)addr;
}

void client_remove(int fd)
{
    /* TODO: implement et */
    (void)fd;
}

client_t *client_find(int fd)
{
    /* TODO: implement et */
    (void)fd;
    return NULL;
}

int client_count(void)
{
    /* TODO: implement et */
    return client_cnt;
}

void client_foreach(void (*callback)(int fd, void *arg), void *arg)
{
    /* TODO: implement et */
    (void)callback; (void)arg;
}
