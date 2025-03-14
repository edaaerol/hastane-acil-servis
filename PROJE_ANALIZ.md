# Hastane Yönetim Sistemi Proje Analizi

## Projenin Amacı
Bu proje, bir hastane yönetim sistemi uygulamasının temel işlevlerini içerir. Kullanıcılar hasta ekleyebilir, hasta bilgilerini güncelleyebilir, reçete oluşturabilir ve randevu oluşturabilir. Ayrıca, HL7 formatında mesajlar oluşturulup kaydedilir.

## Kullanıcı İhtiyaçları
- **Hasta Ekleme:** Yeni hasta kaydı oluşturma ve bilgilerini saklama.
- **Hasta Bilgilerini Görüntüleme:** Sisteme kayıtlı tüm hastaların bilgilerini listeleme.
- **Hasta Durumunu Güncelleme:** Mevcut bir hastanın durumunu değiştirme.
- **Reçete Oluşturma:** Hastalar için ilaç reçetesi hazırlama.
- **Randevu Oluşturma:** Hastalar için randevu oluşturma ve randevu sırasını yönetme.
- **Sıradaki Hastayı Çağırma:** Randevu sırasındaki sıradaki hastayı çağırma.
- **Hasta Taburcu Etme:** Bir hastayı sistemden çıkarma.
- **HL7 Mesajları:** HL7 formatında mesajlar oluşturma ve kaydetme.

## Sistem Gereksinimleri
- **Girdi:** Hasta bilgileri, reçete bilgileri, randevu bilgileri.
- **Çıktı:** Hasta listesi, reçete listesi, randevu listesi, HL7 mesajları.
- **Veri Depolama:** Hasta bilgileri, reçete bilgileri ve HL7 mesajları dosyalarda saklanır.
- **Bellek Yönetimi:** Dinamik bellek tahsisi kullanılarak bağlı listeler oluşturulur.

## Fonksiyonlar ve İşlevleri
- **baslikGoster:** Programın başlığını ekrana yazdırır.
- **menuGoster:** Kullanıcıya mevcut seçenekleri gösterir.
- **hastaEkle:** Yeni hasta kaydı oluşturur.
- **tumHastalariGoruntule:** Sisteme kayıtlı tüm hastaları listeleme.
- **hastaDurumuGuncelle:** Mevcut bir hastanın durumunu günceller.
- **receteOlustur:** Yeni bir reçete oluşturur.
- **tumReceteleriGoruntule:** Sistemde kayıtlı tüm reçeteleri görüntüler.
- **randevuOlustur:** Hastalar için randevu oluşturur.
- **siradakiHasta:** Sıradaki hastayı çağırır.
- **hastayiTaburcuEt:** Bir hastayı sistemden çıkarır.
- **hastaIdAl:** Kullanıcıdan hasta ID'si alır.
- **receteNoUret:** Rastgele bir reçete numarası oluşturur.
- **freeReceteNo:** Reçete numarasını serbest bırakır.
- **hl7MesajiOlustur:** HL7 formatında bir mesaj oluşturur.
- **oncelikSor:** Hastanın acil olup olmadığını sorar.
- **siraNoUret:** Otomatik bir sıra numarası üretir.
- **kayitlariDosyayaKaydet:** Hasta bilgilerini bir dosyaya yazar.
- **kayitlariDosyadanOku:** Hasta bilgilerini bir dosyadan okur.
- **hl7MesajiDosyayaKaydet:** HL7 mesajlarını bir dosyaya ekler.

## Akış Şeması
```mermaid
graph TD;
    A[Başla] --> B[Başlık Göster]
    B --> C[Kayıtları Oku]
    C --> D[Menü Göster]
    D --> E[Seçim Yap]
    E --> F{Seçim}
    F --> |1| G[Hasta Ekle]
    F --> |2| H[Tüm Hastaları Görüntüle]
    F --> |3| I[Hasta Durumu Güncelle]
    F --> |4| J[Randevu Oluştur]
    F --> |5| K[Sıradaki Hasta]
    F --> |6| L[Reçete Oluştur]
    F --> |7| M[Tüm Reçeteleri Görüntüle]
    F --> |8| N[Hastayı Taburcu Et]
    F --> |9| O[Cikis]
    G --> G1[Hasta Bilgilerini Al]
    G1 --> G2[Bellek Tahsis Et]
    G2 --> G3[Listeye Ekle]
    G3 --> G4[HL7 Mesajı Oluştur]
    G4 --> G5[Kayıtları Kaydet]
    G5 --> G6[Mesaj Göster]
    G6 --> D
    H --> H1[Tüm Hastaları Listele]
    H1 --> D
    I --> I1[Hasta ID Al]
    I1 --> I2[Yeni Durum Al]
    I2 --> I3[Hasta Bul]
    I3 --> I4[Durumu Güncelle]
    I4 --> I5[HL7 Mesajı Oluştur]
    I5 --> I6[Kayıtları Kaydet]
    I6 --> I7[Mesaj Göster]
    I7 --> D
    J --> J1[Hasta ID Al]
    J1 --> J2[Hasta Bul]
    J2 --> J3[Randevu Düğümü Oluştur]
    J3 --> J4[Kuyruğa Ekle]
    J4 --> J5[HL7 Mesajı Oluştur]
    J5 --> J6[Mesaj Göster]
    J6 --> D
    K --> K1[Sıradaki Hastayı Çağır]
    K1 --> D
    L --> L1[Reçete Bilgilerini Al]
    L1 --> L2[Bellek Tahsis Et]
    L2 --> L3[Listeye Ekle]
    L3 --> L4[Reçete Numarası Üret]
    L4 --> L5[Mesaj Göster]
    L5 --> D
    M --> M1[Tüm Reçeteleri Listele]
    M1 --> D
    N --> N1[Hasta ID Al]
    N1 --> N2[Hasta Bul]
    N2 --> N3[Hasta Çıkar]
    N3 --> N4[HL7 Mesajı Oluştur]
    N4 --> N5[Kayıtları Kaydet]
    N5 --> N6[Mesaj Göster]
    N6 --> D
    O --> P[Bitir]
```

## Geliştirme Süreci
Bu bölümde, projenin geliştirme aşamaları ve süreçleri hakkında bilgi verilir.

- **Aşama 1:** Analiz ve Planlama
- **Aşama 2:** Tasarım
- **Aşama 3:** Geliştirme
- **Aşama 4:** Test ve Doğrulama
- **Aşama 5:** Dağıtım ve Bakım

## Sonuç
Bu bölümde, projenin genel sonuçları ve elde edilen başarılar özetlenir.

- **Başarı 1:** Açıklama
- **Başarı 2:** Açıklama
- **Başarı 3:** Açıklama
