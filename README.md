# Event-Driven Asenkron I/O Sunucusu

---

Linux `epoll` mekanizmasıyla çalışan, tek event loop ile birden fazla istemciyi bloklamadan yöneten broadcast sunucusu.

Event-Driven Asenkron I/O Sunucusu — Proje Raporu
Ders: Sistem Programlama
Dil: C (C11)
Mekanizma: epoll (Linux)
Senaryo: Çok istemcili broadcast mesajlaşma sistemi

Proje
Bu projede, birden fazla istemci bağlantısını tek bir thread ve tek bir event döngüsü ile yöneten, bloklamayan (non-blocking) bir TCP sunucusu geliştirilmiştir. Linux çekirdeğinin epoll mekanizması kullanılarak, herhangi bir istemciden gelen mesaj aynı anda bağlı olan diğer tüm istemcilere iletilmektedir (broadcast).

---

## Takım

| Kişi | Rol | Dosyalar |
|------|-----|----------|
| Kişi 1 | Sunucu çekirdeği | `server.c`, `epoll_core.c/h`, `Makefile` |
| Kişi 2 | İstemci yönetimi & broadcast | `client_manager.c/h`, `broadcast.c/h`, `utils.c/h` |
| Kişi 3 | Test & istemci | `client/client.c`, `client/load_test.sh` |

---

## Derleme & Çalıştırma

```bash
# Derle
make

# Sunucuyu başlat
./bin/server 8080

# İstemci bağlan
./bin/client 127.0.0.1 8080

# 10 istemci yük testi
make test
```

---

## Proje Yapısı

```
async-io-server/
├── src/
│   ├── server.c           ← main()
│   ├── epoll_core.c/h     ← event loop (Kişi 1)
│   ├── client_manager.c/h ← istemci listesi (Kişi 2)
│   ├── broadcast.c/h      ← mesaj yayınlama (Kişi 2)
│   └── utils.c/h          ← loglama (Kişi 2)
├── client/
│   ├── client.c           ← test istemcisi (Kişi 3)
│   └── load_test.sh       ← yük testi (Kişi 3)
├── tests/
│   └── test_results.md    ← test sonuçları (Kişi 3)
├── GOREV_DAGILIMI.md
├── REPORT.md
└── Makefile
```

---
