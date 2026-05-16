# Görev Dağılımı

## Genel Mimari

```
[İstemciler] ──bağlan──▶ [epoll event loop] ──▶ [client_manager]
                                │                       │
                                ▼                       ▼
                          [veri al]              [broadcast]
                                │
                                ▼
                      [tüm istemcilere ilet]
```

---

## Kişi 1 — Sunucu Çekirdeği (Tamamlandı)

**Sahip olduğu dosyalar:**
- `src/server.c` — main() giriş noktası
- `src/epoll_core.c` — epoll event loop
- `src/epoll_core.h`
- `Makefile`
- `README.md`

**Görevi:**
Linux epoll mekanizmasıyla çalışan non-blocking TCP sunucusunu kurar.
Yeni bağlantı, veri alma ve kopma olaylarını tek event döngüsünde yönetir.
Kişi 2 ve 3'ün yazacağı modülleri çağırır — bu yüzden proje onlar olmadan tamamlanamaz.

**Bağımlılıklar:** Kişi 2'nin `client_manager` ve `broadcast` modüllerini bekler.

---

## Kişi 2 — İstemci Yönetimi & Broadcast 🔧 (Yapılacak)

**Sahip olduğu dosyalar:**
- `src/client_manager.c` — bağlı istemci listesi
- `src/client_manager.h`
- `src/broadcast.c` — mesaj yayınlama sistemi
- `src/broadcast.h`
- `src/utils.c` — loglama
- `src/utils.h`

**Görevi:**
- Bağlanan istemcileri bir dizide tutar (`client_add`, `client_remove`, `client_find`)
- Bir istemciden gelen mesajı geri kalanına iletir (`broadcast_message`)
- Zaman damgalı log sistemi yazar (`log_info`, `log_warn`, `log_err`)

**Teslim kriteri:** `make` hatasız çalışmalı, broadcast doğru çalışmalı.

**Talimatlar:** `KISILER/kisi2.md`

---

## Kişi 3 — Test & İstemci 🔧 (Yapılacak)

**Sahip olduğu dosyalar:**
- `client/client.c` — test istemcisi
- `client/load_test.sh` — yük testi scripti
- `tests/test_results.md` — test sonuçları

**Görevi:**
- Sunucuya bağlanan, mesaj gönderen ve alan istemci yazar
- 10+ istemciyle otomatik yük testi scripti yazar
- Test sonuçlarını `test_results.md`'ye doldurur

**Teslim kriteri:** `make test` ile 10 istemci başarıyla bağlanmalı.

**Talimatlar:** `KISILER/kisi3.md`

---

## İş Akışı

```
Kişi 1 → GitHub'a push eder
Kişi 2 → git clone → client_manager + broadcast + utils yazar → push
Kişi 3 → git clone → client + load_test yazar → test yapar → push
```

Proje ancak 3 kişinin katkısıyla derlenir ve çalışır.
