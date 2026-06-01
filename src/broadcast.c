#include "broadcast.h"
#include "client_manager.h"
#include "utils.h"

#include <sys/socket.h>
#include <string.h>
#include <errno.h>


static void send_to_client(int fd, void *arg)
{
    broadcast_ctx_t *ctx = (broadcast_ctx_t *)arg;

    if(fd == ctx->fd_sender) return;

    ssize_t n = send(fd, ctx->msg, ctx->len, MSG_NOSIGNAL);
    if (n < 0 && errno != EAGAIN)
        log_warn("Gonderim hatasi fd=%d", fd);
}

void broadcast_message(int fd_sender, const char *msg, int len)
{
    broadcast_ctx_t ctx = {fd_sender, msg, len};
    client_foreach(send_to_client, &ctx);
}

void broadcast_system_msg(const char *text)
{
    if (text == NULL)
        return;
    broadcast_message(-1, text, (int)strlen(text));
}
