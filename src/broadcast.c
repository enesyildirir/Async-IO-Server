/* src/broadcast.c
 * Kisi 2 — Mesaj yayınlama implementasyonu
 *
 * GÖREV: 2 fonksiyonu implement et.
 *
 * İpuçları:
 *   - client_foreach() ile her istemci fd'sine eriş
 *   - send(fd, msg, len, MSG_NOSIGNAL) ile gönder
 *   - MSG_NOSIGNAL: kopuk bağlantıda SIGPIPE sinyali gelmesin
 *   - errno == EAGAIN → tampon dolu, bu seferlik atla (hata değil)
 *   - Gönderici (fd_sender) kendine mesaj almasın, onu atla
 */
#include "broadcast.h"
#include "client_manager.h"
#include "utils.h"

#include <sys/socket.h>
#include <string.h>
#include <errno.h>

void broadcast_message(int fd_sender, const char *msg, int len)
{
    /* TODO: implement et
     * İpucu: client_foreach ile her fd için send() yap,
     * fd_sender'ı atla.
     */
    (void)fd_sender; (void)msg; (void)len;
}

void broadcast_system_msg(const char *text)
{
    /* TODO: implement et
     * İpucu: broadcast_message'ı -1 sender ile çağır,
     * ya da doğrudan client_foreach kullan.
     */
    (void)text;
}
