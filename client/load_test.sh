#!/bin/bash
# client/load_test.sh
# Muhammet Emin Balmuk — Otomatik yük testi
#
# 15 adet istemciyi arka planda başlatıp test sonuçlarını raporlama
#
# Kullanım: bash client/load_test.sh [istemci_sayisi] [ip] [port]
# Örnek:    bash client/load_test.sh 10 127.0.0.1 8080

N=${1:-15}
IP=${2:-127.0.0.1}
PORT=${3:-8080}

echo "=== Yük Testi Başlatılıyor ==="
echo "Bağlanacak istemci sayısı: $N"
echo "Hedef: $IP:$PORT"

# Süre ölçümü başlangıcı (milisaniye cinsinden)
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS compatibility
    start_time=$(date +%s)
else
    start_time=$(date +%s%3N)
fi

success_count=0
error_count=0

# Arka planda N adet istemci çalıştırıyoruz
for i in $(seq 1 $N); do
    (
        # TCP bağlantısı açmayı deniyoruz
        if ! exec 3<>/dev/tcp/$IP/$PORT; then
            echo "Istemci-$i: Baglanti kurulamadi!"
            exit 1
        fi
        
        # 5 adet test mesajı gönderiyoruz
        for j in $(seq 1 5); do
            echo "Client-$i mesaj-$j" >&3
            sleep 0.1
        done
        
        # Sunucunun yanıtları işlemesi için kısa bekleme süresi
        sleep 1
        
        # Bağlantıyı kapatıyoruz
        exec 3>&-
    ) &
done

# Tüm arka plan işlemlerinin tamamlanmasını bekliyoruz
wait

# Süre ölçümü bitişi
if [[ "$OSTYPE" == "darwin"* ]]; then
    end_time=$(date +%s)
    elapsed=$(( (end_time - start_time) * 1000 ))
else
    end_time=$(date +%s%3N)
    elapsed=$((end_time - start_time))
fi

echo "=== Yük Testi Tamamlandı ==="
echo "Toplam istemci sayısı: $N"
echo "Toplam geçen süre: ${elapsed} ms"
echo "Ortalama istemci başına süre: $((elapsed / N)) ms"
