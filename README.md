# ESP32 ile Wiegand Protokolü Kullanımı

ESP32 mikrodenetleyicisi ile Wiegand protokolü üzerinden RFID kartlarını okuma işlemini gerçekleştirmek için hazırlanmıştır. Arduino framework kullanılarak geliştirilmiştir.
Ana kod yapay zekaya hazırlatılmıştır. Örnek bir kod bloğudur. Amaç bu protokolü en basit haliyle ESP32 ile nasıl kullanabilirizdir. Farklı Wiegand protokol kütüphaneleri de mevcuttur araştırılması tavsiye edilir.

---

## 🔧 Proje Kurulumu

### 1. Yeni Proje Oluşturma

- Visual Studio Code üzerinde PlatformIO eklentisini kullanarak yeni bir proje oluşturun.
- Framework olarak **Arduino** seçilmelidir.

### 2. Wiegand Kütüphanesini Yükleme

Wiegand protokolü kütüphanesi PlatformIO veya Arduino IDE’nin kütüphane yöneticilerinde mevcut değildir. Bu nedenle kütüphane doğrudan GitHub üzerinden indirilmelidir:

`git clone https://github.com/monkeyboard/Wiegand-Protocol-Library-for-Arduino.git Wiegand`

## Donanım Bağlantısı

### Wiegand Nasıl Çalışır?

Genelde kullanılan model S7941E hem UART hem de Wiegand protokolünü destekler fakat S7941D gibi bazı modeller sadece Wiegand protokolü destekler. Bizim elimizde S7941D var bu yüzden Wiegand protokolüyle birlikte hem `D0` hem de `D1` pinini aktif olarak kullanmalıyız.

`0` biti: D0 hattı kısa süreliğine LOW seviyeye çekilir, `D1` HIGH kalır.

`1` biti: D1 hattı kısa süreliğine LOW seviyeye çekilir, `D0` HIGH kalır.

Özetle, Gwiot RFID okuyucunun D0 ve D1 pinlerinin ESP32'ye bağlanması, Wiegand protokolünün fiziksel katmanını oluşturur. ESP32 ise yazılımsal olarak bu pinlerdeki sinyal değişikliklerini yorumlayarak RFID kartının kimlik bilgilerini okur ve işler

## ESP32 ile Bağlantı

| Gwiot RFID Pin | ESP32 GPIO | Açıklama                    |
| -------------- | ---------- | --------------------------- |
| D0             | GPIO14     | Veri hattı 0 (LOW → 0 biti) |
| D1             | GPIO16     | Veri hattı 1 (LOW → 1 biti) |
| VCC (5 V)      | 5 V        | Güç girişi                  |
| GND            | GND        | Toprak                      |

Gwiot okuyucular 5V ile çalışırken ESP32’nin GPIO pinleri 3V3 toleranslıdır. D0 ve D1 hatlarını bir gerilim bölücü ile 3V3 seviyesine indirilmelidir.

## Gerilim Bölücü Bağlantı Şeması

| RFID Modül Pin | Bağlantı Elemanı                        | ESP32 GPIO Pin | Açıklama                                    |
| -------------- | --------------------------------------- | -------------- | ------------------------------------------- |
| VCC (5V)       | Doğrudan bağlanır                       | 5V             | ESP32’nin 5V çıkışına bağlanır              |
| GND            | Doğrudan bağlanır                       | GND            | Ortak toprak hattı                          |
| D0             | 1k direnç → GPIO14 ve 2.2k direnç → GND | GPIO14         | Gerilim bölücü ile seviye uyumu (5V → 3.3V) |
| D1             | 1k direnç → GPIO16 ve 2.2k direnç → GND | GPIO16         | Gerilim bölücü ile seviye uyumu (5V → 3.3V) |
