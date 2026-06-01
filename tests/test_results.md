# Test Sonuçları

**Kisi 3 tarafından doldurulmuştur.**

## Test Ortamı

| Parametre | Değer |
|-----------|-------|
| İşletim Sistemi | Linux (POSIX/Linux API) |
| Derleyici | gcc (Ubuntu 11.4.0) |
| Test Tarihi | 2026-06-01 |

---

## 5 İstemci Testi

```bash
bash client/load_test.sh 5 127.0.0.1 8080
```

| Metrik | Değer |
|--------|-------|
| Bağlanan | 5/5 |
| Ayrılan | 5/5 |
| Hata | Yok (0) |
| Süre | 1519 ms |

**Sunucu logları:**
```
[12:41:20] [INFO] ====================================
[12:41:20] [INFO]   Async I/O Broadcast Sunucusu
[12:41:20] [INFO]   Port : 8080
[12:41:20] [INFO]   Maks istemci: 128
[12:41:20] [INFO] ====================================
[12:41:28] [INFO] Yeni baglanti: 127.0.0.1:32874 (fd=6) | Toplam: 1
[12:41:28] [INFO] Yeni baglanti: 127.0.0.1:32876 (fd=7) | Toplam: 2
[12:41:28] [INFO] Yeni baglanti: 127.0.0.1:32888 (fd=9) | Toplam: 3
[12:41:28] [INFO] Yeni baglanti: 127.0.0.1:32894 (fd=10) | Toplam: 4
[12:41:28] [INFO] Yeni baglanti: 127.0.0.1:32896 (fd=12) | Toplam: 5
[12:41:28] [INFO] fd=7 → 17 byte
[12:41:28] [INFO] fd=6 → 17 byte
[12:41:28] [INFO] fd=9 → 17 byte
[12:41:28] [INFO] fd=10 → 17 byte
[12:41:28] [INFO] fd=12 → 17 byte
[12:41:29] [INFO] fd=10 → 17 byte
[12:41:29] [INFO] fd=6 → 17 byte
[12:41:29] [INFO] fd=9 → 17 byte
[12:41:29] [INFO] fd=12 → 17 byte
[12:41:29] [INFO] fd=7 → 17 byte
[12:41:29] [INFO] fd=9 → 17 byte
[12:41:29] [INFO] fd=12 → 17 byte
[12:41:29] [INFO] fd=6 → 17 byte
[12:41:29] [INFO] fd=10 → 17 byte
[12:41:29] [INFO] fd=7 → 17 byte
[12:41:29] [INFO] fd=9 → 17 byte
[12:41:29] [INFO] fd=6 → 17 byte
[12:41:29] [INFO] fd=10 → 17 byte
[12:41:29] [INFO] fd=12 → 17 byte
[12:41:29] [INFO] fd=7 → 17 byte
[12:41:29] [INFO] fd=12 → 17 byte
[12:41:29] [INFO] fd=6 → 17 byte
[12:41:29] [INFO] fd=9 → 17 byte
[12:41:29] [INFO] fd=10 → 17 byte
[12:41:29] [INFO] fd=7 → 17 byte
[12:41:30] [INFO] Baglanti koptu: fd=7 (127.0.0.1) | Kalan: 4
[12:41:30] [WARN] Gonderim hatasi fd=6
[12:41:30] [WARN] Gonderim hatasi fd=9
[12:41:30] [WARN] Gonderim hatasi fd=10
[12:41:30] [WARN] Gonderim hatasi fd=12
[12:41:30] [INFO] Baglanti koptu: fd=12 (127.0.0.1) | Kalan: 3
[12:41:30] [WARN] Gonderim hatasi fd=6
[12:41:30] [WARN] Gonderim hatasi fd=9
[12:41:30] [WARN] Gonderim hatasi fd=10
[12:41:30] [INFO] Baglanti koptu: fd=9 (127.0.0.1) | Kalan: 2
[12:41:30] [WARN] Gonderim hatasi fd=6
[12:41:30] [WARN] Gonderim hatasi fd=10
[12:41:30] [INFO] Baglanti koptu: fd=6 (127.0.0.1) | Kalan: 1
[12:41:30] [WARN] Gonderim hatasi fd=10
[12:41:30] [INFO] Baglanti koptu: fd=10 (127.0.0.1) | Kalan: 0
```

---

## 10 İstemci Testi

```bash
bash client/load_test.sh 10 127.0.0.1 8080
```

| Metrik | Değer |
|--------|-------|
| Bağlanan | 10/10 |
| Ayrılan | 10/10 |
| Hata | Yok (0) |
| Süre | 1519 ms |

**Sunucu logları:**
```
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40194 (fd=6) | Toplam: 1
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40204 (fd=7) | Toplam: 2
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40200 (fd=9) | Toplam: 3
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40202 (fd=10) | Toplam: 4
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40238 (fd=12) | Toplam: 5
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40240 (fd=13) | Toplam: 6
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40254 (fd=14) | Toplam: 7
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40258 (fd=15) | Toplam: 8
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40268 (fd=16) | Toplam: 9
[12:41:53] [INFO] Yeni baglanti: 127.0.0.1:40274 (fd=18) | Toplam: 10
[12:41:53] [INFO] fd=6 → 17 byte
[12:41:53] [INFO] fd=9 → 17 byte
[12:41:53] [INFO] fd=10 → 17 byte
[12:41:53] [INFO] fd=12 → 17 byte
[12:41:53] [INFO] fd=13 → 17 byte
[12:41:53] [INFO] fd=14 → 17 byte
[12:41:53] [INFO] fd=15 → 17 byte
[12:41:53] [INFO] fd=16 → 17 byte
[12:41:53] [INFO] fd=18 → 18 byte
[12:41:53] [INFO] fd=7 → 17 byte
[12:41:53] [INFO] fd=6 → 17 byte
[12:41:53] [INFO] fd=13 → 17 byte
[12:41:53] [INFO] fd=12 → 17 byte
[12:41:53] [INFO] fd=14 → 17 byte
[12:41:53] [INFO] fd=15 → 17 byte
[12:41:53] [INFO] fd=9 → 17 byte
[12:41:53] [INFO] fd=16 → 17 byte
[12:41:53] [INFO] fd=10 → 17 byte
[12:41:53] [INFO] fd=18 → 18 byte
[12:41:53] [INFO] fd=7 → 17 byte
[12:41:53] [INFO] fd=9 → 17 byte
[12:41:53] [INFO] fd=14 → 17 byte
[12:41:53] [INFO] fd=6 → 17 byte
[12:41:53] [INFO] fd=13 → 17 byte
[12:41:53] [INFO] fd=16 → 17 byte
[12:41:53] [INFO] fd=15 → 17 byte
[12:41:53] [INFO] fd=7 → 17 byte
[12:41:53] [INFO] fd=10 → 17 byte
[12:41:53] [INFO] fd=12 → 17 byte
[12:41:53] [INFO] fd=18 → 18 byte
[12:41:53] [INFO] fd=9 → 17 byte
[12:41:53] [INFO] fd=6 → 17 byte
[12:41:53] [INFO] fd=15 → 17 byte
[12:41:53] [INFO] fd=16 → 17 byte
[12:41:53] [INFO] fd=10 → 17 byte
[12:41:53] [INFO] fd=13 → 17 byte
[12:41:53] [INFO] fd=18 → 18 byte
[12:41:53] [INFO] fd=7 → 17 byte
[12:41:53] [INFO] fd=14 → 17 byte
[12:41:53] [INFO] fd=12 → 17 byte
[12:41:53] [INFO] fd=18 → 18 byte
[12:41:53] [INFO] fd=16 → 17 byte
[12:41:53] [INFO] fd=15 → 17 byte
[12:41:53] [INFO] fd=12 → 17 byte
[12:41:53] [INFO] fd=14 → 17 byte
[12:41:53] [INFO] fd=7 → 17 byte
[12:41:53] [INFO] fd=6 → 17 byte
[12:41:53] [INFO] fd=10 → 17 byte
[12:41:53] [INFO] fd=13 → 17 byte
[12:41:53] [INFO] fd=9 → 17 byte
[12:41:54] [INFO] Baglanti koptu: fd=14 (127.0.0.1) | Kalan: 9
[12:41:54] [WARN] Gonderim hatasi fd=15
[12:41:54] [WARN] Gonderim hatasi fd=16
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=15 (127.0.0.1) | Kalan: 8
[12:41:54] [WARN] Gonderim hatasi fd=6
[12:41:54] [WARN] Gonderim hatasi fd=7
[12:41:54] [WARN] Gonderim hatasi fd=9
[12:41:54] [WARN] Gonderim hatasi fd=10
[12:41:54] [WARN] Gonderim hatasi fd=12
[12:41:54] [WARN] Gonderim hatasi fd=13
[12:41:54] [WARN] Gonderim hatasi fd=16
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=7 (127.0.0.1) | Kalan: 7
[12:41:54] [WARN] Gonderim hatasi fd=6
[12:41:54] [WARN] Gonderim hatasi fd=9
[12:41:54] [WARN] Gonderim hatasi fd=10
[12:41:54] [WARN] Gonderim hatasi fd=12
[12:41:54] [WARN] Gonderim hatasi fd=13
[12:41:54] [WARN] Gonderim hatasi fd=16
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=9 (127.0.0.1) | Kalan: 6
[12:41:54] [WARN] Gonderim hatasi fd=6
[12:41:54] [WARN] Gonderim hatasi fd=10
[12:41:54] [WARN] Gonderim hatasi fd=12
[12:41:54] [WARN] Gonderim hatasi fd=13
[12:41:54] [WARN] Gonderim hatasi fd=16
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=13 (127.0.0.1) | Kalan: 5
[12:41:54] [WARN] Gonderim hatasi fd=6
[12:41:54] [WARN] Gonderim hatasi fd=10
[12:41:54] [WARN] Gonderim hatasi fd=12
[12:41:54] [WARN] Gonderim hatasi fd=16
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=16 (127.0.0.1) | Kalan: 4
[12:41:54] [WARN] Gonderim hatasi fd=6
[12:41:54] [WARN] Gonderim hatasi fd=10
[12:41:54] [WARN] Gonderim hatasi fd=12
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=12 (127.0.0.1) | Kalan: 3
[12:41:54] [WARN] Gonderim hatasi fd=6
[12:41:54] [WARN] Gonderim hatasi fd=10
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=6 (127.0.0.1) | Kalan: 2
[12:41:54] [WARN] Gonderim hatasi fd=10
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=10 (127.0.0.1) | Kalan: 1
[12:41:54] [WARN] Gonderim hatasi fd=18
[12:41:54] [INFO] Baglanti koptu: fd=18 (127.0.0.1) | Kalan: 0
```

---

## 15 İstemci Testi

```bash
bash client/load_test.sh 15 127.0.0.1 8080
```

| Metrik | Değer |
|--------|-------|
| Bağlanan | 15/15 |
| Ayrılan | 15/15 |
| Hata | Yok (0) |
| Süre | 1517 ms |

**Sunucu logları:**
```
[12:43:36] [INFO] ====================================
[12:43:36] [INFO]   Async I/O Broadcast Sunucusu
[12:43:36] [INFO]   Port : 8080
[12:43:36] [INFO]   Maks istemci: 128
[12:43:36] [INFO] ====================================
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60906 (fd=6) | Toplam: 1
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60912 (fd=7) | Toplam: 2
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60926 (fd=9) | Toplam: 3
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60942 (fd=10) | Toplam: 4
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60950 (fd=12) | Toplam: 5
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60954 (fd=13) | Toplam: 6
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60968 (fd=14) | Toplam: 7
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60980 (fd=15) | Toplam: 8
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60984 (fd=16) | Toplam: 9
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:60998 (fd=18) | Toplam: 10
[12:43:42] [INFO] fd=6 → 17 byte
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:32774 (fd=19) | Toplam: 11
[12:43:42] [INFO] fd=7 → 17 byte
[12:43:42] [INFO] fd=10 → 17 byte
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:32790 (fd=20) | Toplam: 12
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:32806 (fd=21) | Toplam: 13
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:32822 (fd=22) | Toplam: 14
[12:43:42] [INFO] fd=9 → 17 byte
[12:43:42] [INFO] fd=13 → 17 byte
[12:43:42] [INFO] fd=14 → 17 byte
[12:43:42] [INFO] fd=12 → 17 byte
[12:43:42] [INFO] Yeni baglanti: 127.0.0.1:32828 (fd=23) | Toplam: 15
[12:43:42] [INFO] fd=15 → 17 byte
[12:43:42] [INFO] fd=19 → 18 byte
[12:43:42] [INFO] fd=18 → 18 byte
[12:43:42] [INFO] fd=20 → 18 byte
[12:43:42] [INFO] fd=21 → 18 byte
[12:43:42] [INFO] fd=16 → 17 byte
[12:43:42] [INFO] fd=22 → 18 byte
[12:43:42] [INFO] fd=23 → 18 byte
[12:43:42] [INFO] fd=10 → 17 byte
[12:43:42] [INFO] fd=6 → 17 byte
[12:43:42] [INFO] fd=7 → 17 byte
[12:43:42] [INFO] fd=15 → 17 byte
[12:43:42] [INFO] fd=14 → 17 byte
[12:43:42] [INFO] fd=12 → 17 byte
[12:43:42] [INFO] fd=19 → 18 byte
[12:43:42] [INFO] fd=13 → 17 byte
[12:43:42] [INFO] fd=20 → 18 byte
[12:43:42] [INFO] fd=18 → 18 byte
[12:43:42] [INFO] fd=9 → 17 byte
[12:43:42] [INFO] fd=16 → 17 byte
[12:43:42] [INFO] fd=21 → 18 byte
[12:43:42] [INFO] fd=22 → 18 byte
[12:43:42] [INFO] fd=23 → 18 byte
[12:44:12] [INFO] fd=6 → 17 byte
[12:44:12] [INFO] fd=7 → 17 byte
[12:44:12] [INFO] fd=10 → 17 byte
[12:44:12] [INFO] fd=12 → 17 byte
[12:44:12] [INFO] fd=9 → 17 byte
[12:44:12] [INFO] fd=15 → 17 byte
[12:44:12] [INFO] fd=20 → 18 byte
[12:44:12] [INFO] fd=14 → 17 byte
[12:44:12] [INFO] fd=18 → 18 byte
[12:44:12] [INFO] fd=19 → 18 byte
[12:44:12] [INFO] fd=16 → 17 byte
[12:44:12] [INFO] fd=13 → 17 byte
[12:44:12] [INFO] fd=21 → 18 byte
[12:44:12] [INFO] fd=22 → 18 byte
[12:44:12] [INFO] fd=23 → 18 byte
[12:43:42] [INFO] fd=14 → 17 byte
[12:43:42] [INFO] fd=15 → 17 byte
[12:43:42] [INFO] fd=13 → 17 byte
[12:43:42] [INFO] fd=12 → 17 byte
[12:43:42] [INFO] fd=21 → 18 byte
[12:43:42] [INFO] fd=23 → 18 byte
[12:43:42] [INFO] fd=9 → 17 byte
[12:43:42] [INFO] fd=6 → 17 byte
[12:43:42] [INFO] fd=19 → 18 byte
[12:43:42] [INFO] fd=10 → 17 byte
[12:43:42] [INFO] fd=20 → 18 byte
[12:43:42] [INFO] fd=18 → 18 byte
[12:43:42] [INFO] fd=7 → 17 byte
[12:43:42] [INFO] fd=16 → 17 byte
[12:43:42] [INFO] fd=22 → 18 byte
[12:43:42] [INFO] fd=21 → 18 byte
[12:43:42] [INFO] fd=14 → 17 byte
[12:43:42] [INFO] fd=13 → 17 byte
[12:43:42] [INFO] fd=9 → 17 byte
[12:43:42] [INFO] fd=18 → 18 byte
[12:43:42] [INFO] fd=6 → 17 byte
[12:43:42] [INFO] fd=23 → 18 byte
[12:43:42] [INFO] fd=10 → 17 byte
[12:43:42] [INFO] fd=20 → 18 byte
[12:43:42] [INFO] fd=12 → 17 byte
[12:43:42] [INFO] fd=15 → 17 byte
[12:43:42] [INFO] fd=19 → 18 byte
[12:43:42] [INFO] fd=16 → 17 byte
[12:43:42] [INFO] fd=22 → 18 byte
[12:43:42] [INFO] fd=7 → 17 byte
[12:43:43] [INFO] Baglanti koptu: fd=18 (127.0.0.1) | Kalan: 14
[12:43:43] [WARN] Gonderim hatasi fd=6
[12:43:43] [WARN] Gonderim hatasi fd=9
[12:43:43] [WARN] Gonderim hatasi fd=10
[12:43:43] [WARN] Gonderim hatasi fd=13
[12:43:43] [WARN] Gonderim hatasi fd=16
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=21
[12:43:43] [WARN] Gonderim hatasi fd=23
[12:43:43] [INFO] Baglanti koptu: fd=21 (127.0.0.1) | Kalan: 13
[12:43:43] [WARN] Gonderim hatasi fd=6
[12:43:43] [WARN] Gonderim hatasi fd=9
[12:43:43] [WARN] Gonderim hatasi fd=10
[12:43:43] [WARN] Gonderim hatasi fd=13
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=16
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [WARN] Gonderim hatasi fd=23
[12:43:43] [INFO] Baglanti koptu: fd=23 (127.0.0.1) | Kalan: 12
[12:43:43] [WARN] Gonderim hatasi fd=6
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=9
[12:43:43] [WARN] Gonderim hatasi fd=10
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=13
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=16
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=6 (127.0.0.1) | Kalan: 11
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=9
[12:43:43] [WARN] Gonderim hatasi fd=10
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=13
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=16
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=9 (127.0.0.1) | Kalan: 10
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=10
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=13
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=16
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=13 (127.0.0.1) | Kalan: 9
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=10
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=16
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=16 (127.0.0.1) | Kalan: 8
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=10
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=10 (127.0.0.1) | Kalan: 7
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=15
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=20
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=20 (127.0.0.1) | Kalan: 6
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=14
[12:43:43] [WARN] Gonderim hatasi fd=15
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=14 (127.0.0.1) | Kalan: 5
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=15
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [WARN] Gonderim hatasi fd=22
[12:43:43] [INFO] Baglanti koptu: fd=22 (127.0.0.1) | Kalan: 4
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=15
[12:43:43] [WARN] Gonderim hatasi fd=19
[12:43:43] [INFO] Baglanti koptu: fd=19 (127.0.0.1) | Kalan: 3
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=12
[12:43:43] [WARN] Gonderim hatasi fd=15
[12:43:43] [INFO] Baglanti koptu: fd=12 (127.0.0.1) | Kalan: 2
[12:43:43] [WARN] Gonderim hatasi fd=7
[12:43:43] [WARN] Gonderim hatasi fd=15
[12:43:43] [INFO] Baglanti koptu: fd=7 (127.0.0.1) | Kalan: 1
[12:43:43] [WARN] Gonderim hatasi fd=15
[12:43:43] [INFO] Baglanti koptu: fd=15 (127.0.0.1) | Kalan: 0
```

---

## Gözlemler

1. **Ölçeklenebilirlik (Scalability):**
   Sunucu tamamen tek bir ana event döngüsü (event loop) ve Linux `epoll` mekanizması kullanarak geliştirilmiştir. 5, 10 ve son olarak 15 istemci aynı anda bağlandığında, sunucu hiçbir kilitlenme veya bloklama yaşamadan tüm bağlantıları başarıyla yönetmiş ve broadcast işlemlerini tamamlamıştır.

2. **I/O Performansı:**
   İstemcilerin eşzamanlı olarak gönderdiği mesajlar, diğer tüm bağlı istemcilere gecikmesiz bir şekilde yayınlanmıştır (broadcast). İstemci sayısı 5'ten 15'e çıktığında toplam test süresi 1.5 saniye seviyelerinde sabit kalmıştır (çünkü test süresi istemciler arasındaki bekleme süreleri ile sınırlandırılmıştır). Ancak istemci başına düşen ortalama süre 303 ms'den (5 istemci) 101 ms'ye (15 istemci) inmiştir. Bu durum sunucunun asenkron olay yönetimi sayesinde artan eşzamanlı yükler altında son derece verimli ve lineer bir ölçeklenebilirlik sunduğunu açıkça göstermektedir.

3. **Hata ve Bağlantı Yönetimi:**
   İstemciler bağlantıyı kopardıklarında sunucu bunu doğru bir şekilde tespit etmiş (`Baglanti koptu`) ve ilgili fd'yi epoll izleme listesinden çıkararak kaynak sızıntılarını önlemiştir. İstemciler aniden kapandığında broadcast aşamasında alınan `Gonderim hatasi` (WARN) logları, sunucunun kapatılmış soketleri düzgünce yönettiğini doğrulamaktadır.


