#include "client_manager.h"
#include "utils.h"

#include <string.h>
#include <arpa/inet.h>

static client_t clients[MAX_CLIENTS];
static int      client_cnt = 0;

void client_add(int fd, struct sockaddr_in *addr)
{
    for(int i=0; i<MAX_CLIENTS; i++) //boş slot bulmak için döngü
    {
        if(clients[i].fd == 0) //boş olan ilk slota clienti yerleştirip argümanları dolduruyoruz
        {
            clients[i].fd = fd;
            clients[i].port = ntohs(addr->sin_port);
            clients[i].connected_at = time(NULL);
            inet_ntop(AF_INET, &addr->sin_addr, clients[i].ip, sizeof(clients[i].ip));
            client_cnt++; //toplam client sayısını artırıyoruz
            return;
        }
    }
}

void client_remove(int fd)
{
    for(int i = 0; i<MAX_CLIENTS; i++) //parametre olarak alınan fd değerindeki slotu bulmak için döngü
    {
        if(clients[i].fd == fd) //eşleşen fd slotunu bulduktan sonra memset fonksiyonu ile clientin tüm alanlarının temizlenmesini sağlıyoruz 
        {
            memset(&clients[i],0,sizeof(client_t));
            if(client_cnt > 0) //client count'u azaltıyoruz
            {
                client_cnt--;
            }
            return;
        }
    }
}

client_t *client_find(int fd)
{
    for(int i = 0; i<MAX_CLIENTS; i++)
    {
        if(clients[i].fd == fd) //aranan clientin bilgilerini pointer olarak eşleşen slottaki bilgileriyle return ediyoruz
        {
            return &clients[i];
        }
    }
    return NULL;
}

int client_count(void)
{
    return client_cnt;
}

void client_foreach(void (*callback)(int fd, void *arg), void *arg)
{
    for(int i = 0; i<MAX_CLIENTS; i++)
    {
        if(clients[i].fd != 0) //dolu slotlardaki clientler için callback fonksiyonlarını çağrıyoruz
        {
            callback(clients[i].fd, arg);
        }
    }
}
