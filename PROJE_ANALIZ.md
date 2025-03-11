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

## Akış Şemaları

### Ana Menü Akış Şeması
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
    G --> D
    H --> D
    I --> D
    J --> D
    K --> D
    L --> D
    M --> D
    N --> D
    O --> P[Bitir]
```

### Hasta Ekleme Akış Şeması
```mermaid
graph TD;
    A[Başla] --> B[Hasta Bilgilerini Al]
    B --> C[Bellek Tahsis Et]
    C --> D[Listeye Ekle]
    D --> E[HL7 Mesajı Oluştur]
    E --> F[Kayıtları Kaydet]
    F --> G[Mesaj Göster]
    G --> H[Bitir]
```

### Hasta Durumu Güncelleme Akış Şeması
```mermaid
graph TD;
    A[Başla] --> B[Hasta ID Al]
    B --> C[Yeni Durum Al]
    C --> D[Hasta Bul]
    D --> E[Durumu Güncelle]
    E --> F[HL7 Mesajı Oluştur]
    F --> G[Kayıtları Kaydet]
    G --> H[Mesaj Göster]
    H --> I[Bitir]
```

### Randevu Oluşturma Akış Şeması
```mermaid
graph TD;
    A[Başla] --> B[Hasta ID Al]
    B --> C[Hasta Bul]
    C --> D[Randevu Düğümü Oluştur]
    D --> E[Kuyruğa Ekle]
    E --> F[HL7 Mesajı Oluştur]
    F --> G[Mesaj Göster]
    G --> H[Bitir]
```
