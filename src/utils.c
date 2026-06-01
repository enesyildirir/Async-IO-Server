#include "utils.h" 
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

static void log_print(const char *level, const char *fmt, va_list ap)
{
    time_t now = time(NULL); // o anın saniye cinsinden değeri alınıyor
    struct tm *time_tm = localtime(&now); //saniye cinsiden değer yerel saat/dakika  cinsine çevriliyor.
    
    char timestamp[16]; //istediğimiz string formatı
    strftime(timestamp, sizeof(timestamp), "%H:%M:%S", time_tm); //zamanı istediğimiz string formatına çeviriyoruz

    printf("[%s] [%s] ", timestamp,level); //log kaydımızın ilk olarak saat ve level kısımlarını yazdırıyoruz
    vfprintf(stdout,fmt,ap); //kaydımızın geri kalan argümanlarınıda stdout üzerinden yazdırıyoruz

    printf("\n"); //diğer kayıt için alt kısıma geçiyoruz
    fflush(stdout); //buffer'ı terminale boşaltıyoruz
}

void log_info(const char *fmt, ...)
{
    va_list ap; 
    va_start(ap,fmt); // bu kısımda ek argüman kutusu başlatılıyor
    log_print("INFO",fmt,ap); 
    va_end(ap);
}

void log_warn(const char *fmt, ...)
{
    va_list ap; 
    va_start(ap,fmt); // bu kısımda ek argüman kutusu başlatılıyor
    log_print("WARN",fmt,ap); 
    va_end(ap);
}

void log_err(const char *fmt, ...)
{
    va_list ap; 
    va_start(ap,fmt); // bu kısımda ek argüman kutusu başlatılıyor
    log_print("ERR ",fmt,ap); 
    va_end(ap);
}
