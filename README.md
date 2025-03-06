# hastane-acil-servis
# Hastane Yönetim Sistemi

Bu proje, bir hastane yönetim sistemini simüle eden bir C programıdır. Bu sistem, hastaların kaydını tutar, reçete oluşturur, randevu planlar ve hastaları taburcu eder. Ayrıca HL7 mesajları oluşturur ve kayıtları dosyalarda saklar.

## İçindekiler
- [Başlangıç](#başlangıç)
- [Özellikler](#özellikler)
- [Kurulum](#kurulum)
- [Kullanım](#kullanım)
- [Yapı](#yapı)
- [Katkıda Bulunma](#katkıda-bulunma)
- [Lisans](#lisans)

## Başlangıç

Bu talimatlar, projenin yerel makinenizde nasıl çalıştırılacağını gösterir.

### Gereksinimler

- C derleyicisi (gcc veya clang önerilir)
- Bir metin düzenleyici (Visual Studio Code, Sublime Text, vs.)

## Özellikler

- Hastaların kayıt edilmesi
- Hastaların durumlarının güncellenmesi
- Reçete oluşturma ve görüntüleme
- Randevu oluşturma ve sıradaki hastayı görüntüleme
- Hastayı taburcu etme
- HL7 mesajları oluşturma ve kaydetme
- Kayıtların dosyaya kaydedilmesi ve dosyadan okunması

## Kurulum

1. Bu projeyi yerel makinenize klonlayın.
    ```bash
    git clone https://github.com/kullanici_adi/hastane-yonetim-sistemi.git
    cd hastane-yonetim-sistemi
    ```

2. Projeyi derleyin.
    ```bash
    gcc main.c -o hastane_yonetim_sistemi
    ```

## Kullanım

Derlenen programı çalıştırın.
```bash
./hastane_yonetim_sistemi
```

Program çalıştığında aşağıdaki menü görünecektir:
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

## Yapı

- `main.c`: Ana program dosyası.
- `Hasta`, `Nodo`, `Recete`, `ReceteNodo` yapıları: Hasta ve reçete bilgilerini tutan yapılar.
- Fonksiyonlar:
  - `baslikGoster()`: Başlığı görüntüler.
  - `menuGoster()`: Menü seçeneklerini görüntüler.
  - `hastaEkle()`: Yeni bir hasta ekler.
  - `tumHastalariGoruntule()`: Tüm hastaları görüntüler.
  - `hastaDurumuGuncelle()`: Bir hastanın durumunu günceller.
  - `receteOlustur()`: Yeni bir reçete oluşturur.
  - `tumReceteleriGoruntule()`: Tüm reçeteleri görüntüler.
  - `randevuOlustur()`: Yeni bir randevu oluşturur.
  - `siradakiHasta()`: Sıradaki hastayı görüntüler.
  - `hastayiTaburcuEt()`: Bir hastayı taburcu eder.
  - `kayitlariDosyayaKaydet()`: Kayıtları dosyaya kaydeder.
  - `kayitlariDosyadanOku()`: Kayıtları dosyadan okur.
  - `hl7MesajiOlustur()`: HL7 mesajı oluşturur.
  - `hl7MesajiDosyayaKaydet()`: HL7 mesajını dosyaya kaydeder.

## Lisans

Bu proje MIT Lisansı ile lisanslanmıştır - detaylar için `LICENSE` dosyasına bakın.
