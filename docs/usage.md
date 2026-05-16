# Kullanım Kılavuzu

## 1. Kurulum (Bir kez yapılır)

```bash
# WSL terminalinde proje klasörüne gir
cd /mnt/c/Users/KULLANICI/Desktop/async-io-server

# Gerekli araçları kur
sudo apt install gcc make -y

# Derle
make
```

---

## 2. Sunucuyu Başlat

**Terminal 1:**
```bash
./bin/server 8080
```
```
[INFO] Async I/O Broadcast Sunucusu
[INFO] Port : 8080
[INFO] Bekleniyor...
```
Bu terminal açık kalacak — sunucu loglarını buradan takip edersin.

---

## 3. İstemci Bağlan

**Terminal 2** (yeni WSL terminali aç):
```bash
./bin/client 127.0.0.1 8080
```

**Aynı ağdaki başka bilgisayardan bağlanmak için:**
```bash
# Önce sunucunun IP'sini öğren
ip addr | grep "inet 192"

# Diğer bilgisayardan
./bin/client 192.168.x.x 8080
```

---

## 4. Mesajlaş

Bağlandıktan sonra bir şeyler yaz ve Enter'a bas.  
Aynı sunucuya bağlı **tüm istemciler** mesajı görür.

```
merhaba
[127.0.0.1] merhaba        ← diğer istemcilerde görünür
```

Çıkmak için: `Ctrl+C`

---

## 5. Yük Testi (10 İstemci)

Sunucu çalışırken yeni bir terminalde:
```bash
bash client/load_test.sh 10 127.0.0.1 8080
```

---

## 6. Temizle & Yeniden Derle

```bash
make clean
make
```
