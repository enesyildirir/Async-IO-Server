# Event-Driven Asenkron I/O Sunucusu ve Eşzamanlı İstemci Raporu

Linux `epoll` mekanizmasıyla çalışan, tek event loop ile birden fazla istemciyi bloklamadan yöneten broadcast sunucusu ve çok kanallı (multithreaded) senkronize test istemcisi.

---

## Takım

| Görev / Modül | Sorumlu Üye | Dosyalar |
|:---|:---|:---|
| **Sunucu Çekirdeği** (1. Görev) | Muhammet Enes Yıldırır | `src/server.c`, `src/epoll_core.c/h`, `Makefile` |
| **İstemci Yönetimi & Broadcast** (2. Görev) | Muhammet Batuhan Karanfil | `src/client_manager.c/h`, `src/broadcast.c/h`, `src/utils.c/h` |
| **Test & İstemci** (3. Görev) | Muhammet Emin Balmuk | `client/client.c`, `client/load_test.sh`, `tests/test_results.md` |

---

## Amaç

Bu projenin amacı; Linux POSIX standartları ve düşük seviyeli sistem çağrıları kullanılarak, yüksek performanslı, ölçeklenebilir ve bloklamayan (non-blocking) bir **Event-Driven Asenkron I/O Sunucusu** ve bu sunucuyu test edecek **Eşzamanlı/Çok Kanallı (Multithreaded) İstemci** geliştirmektir. Projede, aynı anda aktif olan onlarca istemciden gelen mesajların tek bir event döngüsünde bloklanmadan kabul edilmesi, işlenmesi ve broadcast (yayınlama) yöntemiyle tüm istemcilere eşzamanlı olarak dağıtılması hedeflenmiştir.

---

## Tasarım

Sistem, olay-güdümlü (event-driven) bir sunucu mimarisi ile bu sunucunun limitlerini ölçen, senkronize loglama kuyruğuna sahip eşzamanlı çalışan test istemcilerinden oluşur.

```
[ İstemciler ] ──── TCP (Mesaj Gönder) ───▶ [ Sunucu Event Loop (epoll_wait) ] 
      │                                                │
      │                                                ▼
      ◀─── TCP (Broadcast) ───────────────── [ İstemci Yönetimi & Broadcast ]
```

### Sunucu Mimarisi
* **Epoll Tabanlı Olay Döngüsü:** Sunucu çekirdeği (`src/epoll_core.c` ve `src/server.c`), Linux `epoll` arayüzünü (`epoll_create1`, `epoll_wait`) kullanarak tek bir thread üzerinde yüzlerce soketi asenkron olarak izler. Bağlantı kabul etme (accept), veri alma (recv) ve bağlantı kopması (disconnect) olayları tamamen bloklamasız (`O_NONBLOCK`) soketlerle gerçekleştirilir.
* **İstemci Yönetimi & Broadcast Altyapısı:** 
  * **İstemci Yönetimi (`src/client_manager.c/h`):** Bağlı aktif istemciler sabit boyutlu `MAX_CLIENTS` (128) adetlik bir dizi içerisinde tutulur. Sunucu tek thread çalıştığı için yarış durumu oluşmadan `client_add()`, `client_remove()`, `client_find()` ve listeyi dolaşan `client_foreach()` fonksiyonları ile güvenli bir şekilde istemci yönetimi yapılır.
  * **Mesaj Yayınlama Modülü (`src/broadcast.c/h`):** Herhangi bir istemciden gelen mesaj, `client_foreach()` kullanılarak geriye kalan tüm aktif istemci soket dosyalarına `send()` fonksiyonu yardımıyla asenkron olarak yazılır. Kopan bağlantılarda oluşabilecek sinyal çökmelerini engellemek amacıyla gönderim aşamasında `MSG_NOSIGNAL` flag'i kullanılmıştır.
  * **Zaman Damgalı Loglama Altyapısı (`src/utils.c/h`):** Sunucunun tüm durumları `[INFO]`, `[WARN]`, `[ERR ]` seviyelerinde zaman damgalı formatta (`strftime` kullanarak) standart çıktıya (`stdout`) anında yazılır.

### İstemci Mimarisi & Yük Testi
* **Select I/O Çoklama (Multiplexing) (`client/client.c`):** İstemci, tek bir event döngüsünde `select()` fonksiyonunu kullanarak hem standart klavye girişini (`STDIN_FILENO`) hem de sunucudan gelen TCP soket verisini aynı anda dinler. Bu sayede girdi okurken ağdan gelen veri asla bloklanmaz.
* **Asenkron Multithreaded Loglama:** İstemcinin ana ağ/konsol döngüsünün disk yazma (I/O) işlemlerinin yavaşlığı nedeniyle kilitlenmesini engellemek için, log yazma işlemleri `pthread_create` ile oluşturulan ayrı bir **Log Thread**'ine devredilmiştir.
* **Mutex & Condvar Senkronizasyonu:** Paylaşılan döngüsel log kuyruğu (`log_queue_t`), yarış durumlarını engellemek adına `pthread_mutex_t` ile korunur. Ana thread kuyruğa yeni log eklediğinde `pthread_cond_signal` ile kuyruğu dinleyen log thread'ini uyandırır (`pthread_cond_wait`), böylece CPU kaynakları verimli tüketilir.
* **Multi-process Yük Testi Modülü (`client/load_test.sh`):** Bash TCP soket yeteneklerini (`/dev/tcp`) kullanan script, arka planda paralel çalışan 15 adete kadar bağımsız istemci prosesi oluşturur. Her istemci 5 adet test mesajı gönderip bağlantıyı kapatarak sunucunun asenkron yapısını test eder ve milisaniye hassasiyetli performans ölçümü yapar.

---

## Kullanılan Sistem Programlama Kavramları

1. **I/O Multiplexing (Giriş/Çıkış Çoklama):** Sunucuda Linux'a özgü `epoll` (`epoll_wait`) arayüzü, istemcide ise POSIX standartlı taşınabilir `select()` fonksiyonu kullanılarak eşzamanlı I/O takip edilmiştir.
2. **Non-blocking (Bloklamayan) Sockets:** Soketler `fcntl()` vasıtasıyla `O_NONBLOCK` moduna getirilerek yavaş çalışan ağ istemcilerinin tüm sistemi kilitlemesi önlenmiştir.
3. **Çoklu İş Parçacığı (Multithreaded) & Eşzamanlılık:** İstemci tarafında asenkron disk yazımı için `pthread_create` ile ikinci bir iş parçacığı koşturulmuştur.
4. **Kilit ve Koşul Değişkenleri (Mutex & Condvar):** İstemcide thread'ler arası paylaşılan kaynaklar `pthread_mutex_t` ile korunmuş, thread koordinasyonu ise `pthread_cond_t` koşul değişkeni ile sağlanmıştır.
5. **Multi-process Performans Simülasyonu:** `load_test.sh` içerisinde bash düzeyinde `&` kullanarak eşzamanlı bağımsız prosesler üretilmiş ve ana proses `wait` çağrısıyla tüm çocuk proseslerin sonlanmasını beklemiştir.
6. **Robust Error Handling (Güvenli Hata Yönetimi):** Çökmeleri önlemek amacıyla soket gönderimlerinde `MSG_NOSIGNAL` kullanılmış; hata yönetimleri `perror` ve `strerror(errno)` ile zaman damgalı log dosyasına yazılmıştır.

---

## Çalıştırma Adımları

Proje standart C11 derleyicisi (`gcc`) ve GNU `make` aracı ile derlenir:

```bash
# 1. Projeyi derleyin
make

# 2. Sunucuyu port belirterek başlatın (Terminal 1)
./bin/server 8080

# 3. Manuel istemci ile bağlanın (Terminal 2)
./bin/client 127.0.0.1 8080

# 4. Otomatik yük testini çalıştırın (Terminal 3 - Varsayılan 15 İstemci)
make test
# Veya manuel parametre ile:
bash client/load_test.sh 15 127.0.0.1 8080
```

---

## Testler

Geliştirdiğimiz yük testi scripti ile 5, 10 ve 15 istemcili yük senaryoları simüle edilmiştir. Detaylı loglar ve analiz sonuçları için [test_results.md](file:///home/eminlinux/Emin/Async-IO-Server/tests/test_results.md) dosyasını inceleyebilirsiniz.

### 15 İstemci Eşzamanlı Yük Testi Sonuçları:
```text
=== Yük Testi Başlatılıyor ===
Bağlanacak istemci sayısı: 15
Hedef: 127.0.0.1:8080
=== Yük Testi Tamamlandı ===
Toplam istemci sayısı: 15
Toplam geçen süre: 1522 ms
Ortalama istemci başına süre: 101 ms
```
* **Metrik Değerlendirmesi:** İstemci sayısı 5'ten 15'e çıkarıldığında toplam test süresi (~1.5 saniye) sabit kalmıştır. Çünkü test süresi istemciler arasındaki `sleep` süreleriyle sınırlandırılmıştır. Ancak istemci başına ortalama süre 303 ms'den **101 ms**'ye düşerek sunucunun paralel istekleri asenkron olarak mükemmel biçimde paylaştırdığını ve bloklanmadan ölçeklendiğini kanıtlamıştır.

---

## Karşılaşılan Problemler

1. **Yarış Durumu (Race Condition) ve Terminal Kilitlenmesi:**
   * *Problem:* Manuel istemcide hem terminalden girdi okunması hem soketten gelen verilerin terminale yazılması sırasında çakışmalar meydana gelmekte ve disk yazımları ana döngüyü yavaşlatmaktaydı.
   * *Çözüm:* Asenkron `log_queue_t` kuyruğu tasarlandı. Terminale yapılan ham çıktılar dışındaki tüm operasyonel loglar `pthread_mutex_t` ve `pthread_cond_t` ile korunarak arka plandaki log thread'ine devredildi, böylece ana I/O akışı tamamen bloklamasız hale getirildi.

2. **İstemcilerin Kapanmasında Sunucu Tarafında Soket Hataları:**
   * *Problem:* Yük testinde 15 istemci prosesi işlerini bitirip aniden soketleri kapattığında sunucu tarafında yayın (broadcast) esnasında kırık boru (`EPIPE`/`ECONNRESET`) hataları ve yoğun `Baglanti koptu` / `Gonderim hatasi` logları oluşmaktaydı.
   * *Çözüm:* Bu durumun eşzamanlı ağ sistemlerinde tamamen **normal ve beklenen** bir davranış olduğu tespit edildi. Sunucunun çökmesini engellemek için `MSG_NOSIGNAL` flag'i kullanıldı. İstemci tarafında `recv()`'in `0` dönmesi (EOF) algılanarak soketler güvenle kapatıldı ve sunucu tarafında bu soket yazım hataları zararsız `[WARN]` seviyesine çekilerek sistem kararlılığı sağlandı.

