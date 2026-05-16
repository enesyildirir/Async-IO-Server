# Kişi 3 — Yapılacaklar

## Repoyu Klonla

```bash
git clone https://github.com/KULLANICIAD/async-io-server.git
cd async-io-server
```

> ⚠️ Kişi 2'nin modülleri tamamlanmadan `make` çalışmaz.
> Kişi 2 push edince sen de `git pull` yapıp devam edebilirsin.

## Senin Dosyaların

```
client/client.c       ← YAZI: test istemcisi
client/load_test.sh   ← YAZI: otomatik yük testi
tests/test_results.md ← DOLDUR: test sonuçları
```

## Ne Yapman Gerekiyor?

### 1. client/client.c — Test İstemcisi

Sunucuya TCP bağlantısı açan, mesaj gönderip alan program yaz.

**Gereksinimler:**
- `./bin/client 127.0.0.1 8080` şeklinde çalışsın
- Hem klavyeyi hem soketi aynı anda dinlesin → `select()` kullan
- Sunucudan gelen mesajları ekrana bassın
- Bağlantı kesilince temiz çıksın

**İpucu:** `select()` ile `STDIN_FILENO` ve soket fd'sini aynı anda izle.

---

### 2. client/load_test.sh — Yük Testi

Bash scripti ile N adet istemciyi arka planda başlat.

```bash
#!/bin/bash
N=${1:-10}
IP=${2:-127.0.0.1}
PORT=${3:-8080}

for i in $(seq 1 $N); do
    (
        exec 3<>/dev/tcp/$IP/$PORT
        for j in $(seq 1 5); do
            echo "Client-$i mesaj-$j" >&3
            sleep 0.1
        done
        sleep 1
        exec 3>&-
    ) &
done
wait
```

Script çalıştırılabilir olmalı: `chmod +x client/load_test.sh`

---

### 3. tests/test_results.md — Test Sonuçları

Sunucuyu başlat, yük testini çalıştır, sonuçları tabloya yaz:

| İstemci Sayısı | Bağlanan | Ayrılan | Hata | Süre |
|----------------|----------|---------|------|------|
| 5  | | | | |
| 10 | | | | |

Sunucu loglarını da ekle.

---

## Test Komutu

```bash
# Terminal 1 — sunucu
./bin/server 8080

# Terminal 2 — yük testi
bash client/load_test.sh 10 127.0.0.1 8080
```

## Tamamlayınca

```bash
git add client/client.c client/load_test.sh tests/test_results.md
git commit -m "feat: test istemcisi ve yuk testi eklendi"
git push
```
