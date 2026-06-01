# Kişi 2 — Yapılacaklar

## Repoyu Klonla

```bash
git clone https://github.com/enesyildirir/async-io-server.git
cd async-io-server
```

## Senin Dosyaların

```
src/utils.h        ← arayüz tanımı (dokunma)
src/utils.c        ← YAZI: log fonksiyonlarını implement et
src/client_manager.h ← arayüz tanımı (dokunma)
src/client_manager.c ← YAZI: istemci listesini implement et
src/broadcast.h    ← arayüz tanımı (dokunma)
src/broadcast.c    ← YAZI: broadcast sistemini implement et
```

## Ne Yapman Gerekiyor?

### 1. utils.c — Loglama

`log_info`, `log_warn`, `log_err` fonksiyonlarını yaz.
Çıktı formatı şöyle olmalı: 
```
[14:32:01] [INFO] Yeni baglanti: 127.0.0.1 (fd=5)
[14:32:05] [WARN] Gonderim hatasi fd=7
```

İpucu: `time()`, `localtime()`, `strftime()`, `vprintf()` kullan.

---

### 2. client_manager.c — İstemci Listesi

`client_add`, `client_remove`, `client_find`, `client_count`, `client_foreach` fonksiyonlarını yaz.

- Sabit boyutlu dizi kullan: `client_t clients[MAX_CLIENTS]`
- `fd == 0` boş slot demek
- `client_foreach` her bağlı istemci için callback çağırır (broadcast bunu kullanır)

---

### 3. broadcast.c — Mesaj Yayınlama

`broadcast_message` ve `broadcast_system_msg` fonksiyonlarını yaz.

- `broadcast_message(fd_sender, msg, len)` → gönderen hariç herkese `send()` yap
- `broadcast_system_msg(text)` → herkese sistem mesajı gönder
- `send()` başarısız olursa `errno == EAGAIN` mi gerçek hata mı kontrol et
- `MSG_NOSIGNAL` bayrağını kullan (kopuk bağlantıda program çökmessin)

---

## Derleme Testi

```bash
make
```

Hata yoksa modüllerin çalışıyor demektir.

## Tamamlayınca

```bash
git add src/utils.c src/client_manager.c src/broadcast.c
git commit -m "feat: client_manager, broadcast ve utils implement edildi"
git push
```
