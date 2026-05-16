#!/bin/bash
# client/load_test.sh
# Kisi 3 — Otomatik yük testi
#
# GÖREV: N adet istemciyi arka planda başlat, sonuçları raporla.
#
# Kullanım: bash client/load_test.sh [istemci_sayisi] [ip] [port]
# Örnek:    bash client/load_test.sh 10 127.0.0.1 8080
#
# İpuçları:
#   - /dev/tcp/$IP/$PORT ile bash'ten TCP bağlantısı aç
#   - & ile arka planda çalıştır
#   - wait ile tümünün bitmesini bekle
#   - date +%s ile başlangıç/bitiş zamanı al

N=${1:-10}
IP=${2:-127.0.0.1}
PORT=${3:-8080}

echo "TODO: $N istemci $IP:$PORT adresine bağlanacak"

# TODO: implement et
