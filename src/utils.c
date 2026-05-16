/* src/utils.c
 * Kisi 2 — Zaman damgalı loglama sistemi
 *
 * GÖREV: Aşağıdaki 3 fonksiyonu implement et.
 *
 * Beklenen çıktı formatı:
 *   [14:32:01] [INFO] Yeni baglanti: 127.0.0.1 (fd=5)
 *   [14:32:05] [WARN] Gonderim hatasi fd=7
 *   [14:32:10] [ERR ] Socket hatasi
 *
 * İpuçları:
 *   - time(), localtime(), strftime() → saat damgası
 *   - va_list, va_start(), vprintf(), va_end() → değişken argüman
 *   - fflush(stdout) → çıktının hemen görünmesi için
 */
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/* TODO: log_print yardımcı fonksiyonunu yaz */

void log_info(const char *fmt, ...)
{
    /* TODO: implement et */
    (void)fmt;
}

void log_warn(const char *fmt, ...)
{
    /* TODO: implement et */
    (void)fmt;
}

void log_err(const char *fmt, ...)
{
    /* TODO: implement et */
    (void)fmt;
}
