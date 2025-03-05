# hastane-acil-servis
# Hastane Yönetim Sistemi

Bu proje, hastane yönetimi için temel bir sistem sağlar. Sistem, hastaların kaydedilmesi, durumu güncellenmesi, reçete oluşturulması, randevu oluşturulması ve hastaların taburcu edilmesi gibi işlevleri içerir. Ayrıca, HL7 mesajları oluşturarak bu işlemleri standart bir formatta belgelemektedir.

## Özellikler

- Hasta ekleme
- Tüm hastaları görüntüleme
- Hasta durumu güncelleme
- Reçete oluşturma
- Tüm reçeteleri görüntüleme
- Randevu oluşturma
- Sıradaki hastayı görüntüleme
- Hastayı taburcu etme
- HL7 mesajı oluşturma

## Kurulum

Projeyi klonlayın:

```bash
git clone https://github.com/edaaerol/hastane-yonetim-sistemi.git
cd hastane-yonetim-sistemi
```

## Derleme ve Çalıştırma

Projeyi derlemek ve çalıştırmak için aşağıdaki adımları izleyin:

```bash
gcc -o hastane_yonetim_hl7 hastane_yonetimi_hl7.c
./hastane_yonetim_hl7
```

## Kullanım

Program çalıştırıldığında, aşağıdaki menü görünecektir:

```
1. Hasta Ekle
2. Tüm Hastaları Görüntüle
3. Hasta Durumu Güncelle
4. Randevu Oluştur
5. Sıradaki Hasta
6. Reçete Oluştur
7. Tüm Reçeteleri Görüntüle
8. Hastayı Taburcu Et
9. Çıkış
```

Bir seçenek girerek ilgili işlemi gerçekleştirebilirsiniz.

## HL7 Mesajları

HL7 (Health Level 7) mesajları, sağlık bilgi sistemleri arasında veri alışverişi için kullanılan standart bir formattır. Bu sistemde, her işlem için ilgili HL7 mesajı oluşturulmakta ve ekranda görüntülenmektedir.

Örnek bir HL7 mesajı:

```
MSH|^~\&|Hastane Bilgi Sistemi|Hastane|Hasta Kayit Sistemi|Hastane|2025-03-05 21:20:00||ADT^A01|123456|P|2.3
PID|1|123|123||John^Doe||19700101|M||2106-3|1234 Main St^^Metropolis^IL^12345^USA||(312)555-1212||(312)555-1213||S||PATID1234^2^M10|123456789|987654^^^&2.16.840.1.113883.19.3.2.1.1.9&ISO^MR
PV1|1|I|2000^2012^01||||004777^Doktor^Adi^A.|||||||||||V||2|A0
AL1|1||^Penicillin||Produces hives
ORC|RE|654321^Hastane|654321^Hastane||CM||||2025-03-05 21:20:00
OBR|1|||Complete Blood Count|||2025-03-05 21:20:00
OBX|1|NM|^WBC|1|6.7|10*3/uL|4.5-11.0|N|||F
```

## Lisans

Bu proje MIT Lisansı ile lisanslanmıştır. Daha fazla bilgi için `LICENSE` dosyasına bakabilirsiniz.
