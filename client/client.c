/* client/client.c
 Muhammet Emin Balmuk — Test istemcisi
 
 Sunucuya bağlanıp mesaj gönderen ve alan test istemcisini yazma
 
 Kullanım: ./bin/client <ip> <port>
 Örnek:    ./bin/client 127.0.0.1 8080
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <stdarg.h>

#define LOG_QUEUE_MAX 256
#define LOG_MSG_SIZE 512

// Log kuyruğu yapısı
typedef struct {
    char messages[LOG_QUEUE_MAX][LOG_MSG_SIZE];
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int done;
} log_queue_t;

static log_queue_t g_log_queue;
static pthread_t g_log_thread;
static FILE *g_log_file = NULL;

// Log kuyruğu başlatma
void log_queue_init(void) {
    g_log_queue.head = 0;
    g_log_queue.tail = 0;
    g_log_queue.count = 0;
    g_log_queue.done = 0;
    pthread_mutex_init(&g_log_queue.mutex, NULL);
    pthread_cond_init(&g_log_queue.cond, NULL);
}

// Güvenli kuyruğa log ekleme
void log_write(const char *level, const char *fmt, ...) {
    pthread_mutex_lock(&g_log_queue.mutex);
    if (g_log_queue.count < LOG_QUEUE_MAX) {
        char formatted[LOG_MSG_SIZE - 64];
        va_list args;
        va_start(args, fmt);
        vsnprintf(formatted, sizeof(formatted), fmt, args);
        va_end(args);

        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

        snprintf(g_log_queue.messages[g_log_queue.tail], LOG_MSG_SIZE,
                 "[%s] [%s] %s\n", timestamp, level, formatted);

        g_log_queue.tail = (g_log_queue.tail + 1) % LOG_QUEUE_MAX;
        g_log_queue.count++;
        pthread_cond_signal(&g_log_queue.cond);
    }
    pthread_mutex_unlock(&g_log_queue.mutex);
}

// Log yazıcı thread fonksiyonu
void *log_thread_func(void *arg) {
    (void)arg;
    while (1) {
        pthread_mutex_lock(&g_log_queue.mutex);
        while (g_log_queue.count == 0 && !g_log_queue.done) {
            pthread_cond_wait(&g_log_queue.cond, &g_log_queue.mutex);
        }

        if (g_log_queue.count == 0 && g_log_queue.done) {
            pthread_mutex_unlock(&g_log_queue.mutex);
            break;
        }

        char msg[LOG_MSG_SIZE];
        strncpy(msg, g_log_queue.messages[g_log_queue.head], LOG_MSG_SIZE);
        g_log_queue.head = (g_log_queue.head + 1) % LOG_QUEUE_MAX;
        g_log_queue.count--;

        pthread_mutex_unlock(&g_log_queue.mutex);

        if (g_log_file) {
            fputs(msg, g_log_file);
            fflush(g_log_file);
        }
    }
    return NULL;
}

// Log kuyruğu temizleme
void log_queue_cleanup(void) {
    pthread_mutex_lock(&g_log_queue.mutex);
    g_log_queue.done = 1;
    pthread_cond_signal(&g_log_queue.cond);
    pthread_mutex_unlock(&g_log_queue.mutex);

    pthread_join(g_log_thread, NULL);

    pthread_mutex_destroy(&g_log_queue.mutex);
    pthread_cond_destroy(&g_log_queue.cond);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Kullanim: %s <ip> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Log dosyasını açma
    g_log_file = fopen("client.log", "a");
    if (!g_log_file) {
        perror("fopen client.log");
        return EXIT_FAILURE;
    }

    log_queue_init();
    if (pthread_create(&g_log_thread, NULL, log_thread_func, NULL) != 0) {
        perror("pthread_create");
        fclose(g_log_file);
        return EXIT_FAILURE;
    }

    log_write("INFO", "Istemci baslatildi. Hedef: %s:%s", argv[1], argv[2]);

    // TCP Soketi oluşturma
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        log_write("ERROR", "Soket olusturulamadi: %s", strerror(errno));
        log_queue_cleanup();
        fclose(g_log_file);
        return EXIT_FAILURE;
    }

    // Sunucu adres yapılandırması
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        fprintf(stderr, "Gecersiz IP adresi: %s\n", argv[1]);
        log_write("ERROR", "Gecersiz IP adresi: %s", argv[1]);
        close(sock);
        log_queue_cleanup();
        fclose(g_log_file);
        return EXIT_FAILURE;
    }

    // Sunucuya bağlanma
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        log_write("ERROR", "%s:%s adresine baglanti basarisiz: %s", argv[1], argv[2], strerror(errno));
        close(sock);
        log_queue_cleanup();
        fclose(g_log_file);
        return EXIT_FAILURE;
    }

    printf("Sunucuya baglanildi! Cikis yapmak icin 'exit' yazabilir veya Ctrl+D basabilirsiniz.\n");
    log_write("INFO", "Sunucuya basariyla baglanildi. %s:%s (sock fd=%d)", argv[1], argv[2], sock);

    char buf[1024];
    int running = 1;

    // select() döngüsü
    while (running) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(sock, &read_fds);

        int max_fd = sock > STDIN_FILENO ? sock : STDIN_FILENO;

        int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity < 0) {
            if (errno == EINTR) continue;
            perror("select");
            log_write("ERROR", "Select hatasi: %s", strerror(errno));
            break;
        }

        // Klavyeden giriş var mı kontrolü
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            if (fgets(buf, sizeof(buf), stdin) == NULL) {
                printf("\nBaglanti sonlandiriliyor (EOF).\n");
                log_write("INFO", "Istemci tarafindan baglanti sonlandirildi (EOF)");
                running = 0;
                break;
            }

            size_t len = strlen(buf);
            if (len > 0 && buf[len - 1] == '\n') {
                buf[len - 1] = '\0';
                len--;
            }

            if (strcmp(buf, "exit") == 0) {
                printf("Baglanti sonlandiriliyor.\n");
                log_write("INFO", "Istemci tarafindan baglanti sonlandirildi (exit)");
                running = 0;
                break;
            }

            // Mesajın sonuna yeni satırı ekleyip gönderiyoruz
            buf[len] = '\n';
            buf[len + 1] = '\0';

            ssize_t sent = send(sock, buf, strlen(buf), 0);
            if (sent < 0) {
                perror("send");
                log_write("ERROR", "Mesaj gonderilemedi: %s", strerror(errno));
                break;
            } else {
                buf[len] = '\0'; // Loglama için yeni satırı temizliyoruz
                log_write("INFO", "Gonderildi: %s", buf);
            }
        }

        // Soketten gelen veri var mı kontrolü
        if (FD_ISSET(sock, &read_fds)) {
            ssize_t n = recv(sock, buf, sizeof(buf) - 1, 0);
            if (n > 0) {
                buf[n] = '\0';
                printf("%s", buf);
                fflush(stdout);

                // Loglama için sondaki yeni satırı temizliyoruz
                if (buf[n - 1] == '\n') {
                    buf[n - 1] = '\0';
                }
                log_write("INFO", "Alindi: %s", buf);
            } else if (n == 0) {
                printf("\nSunucu baglantiyi sonlandirdi.\n");
                log_write("INFO", "Sunucu baglantiyi kapatti.");
                running = 0;
            } else {
                perror("recv");
                log_write("ERROR", "Recv hatasi: %s", strerror(errno));
                running = 0;
            }
        }
    }

    close(sock);
    log_write("INFO", "Soket kapatildi. Program sonlandiriliyor.");
    log_queue_cleanup();

    if (g_log_file) {
        fclose(g_log_file);
    }

    return EXIT_SUCCESS;
}

