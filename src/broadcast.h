/* src/broadcast.h
 * Kisi 2 — Mesaj yayınlama arayüzü
 * (Bu dosyaya dokunma, sadece broadcast.c'yi yaz)
 */
#ifndef BROADCAST_H
#define BROADCAST_H

/* fd_sender hariç tüm istemcilere mesaj gönder */
void broadcast_message(int fd_sender, const char *msg, int len);

/* Herkese sistem bildirimi gönder */
void broadcast_system_msg(const char *text);

typedef struct {
    int         fd_sender;
    const char *msg;
    int         len;
} broadcast_ctx_t;

#endif
