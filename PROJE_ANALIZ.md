# Proje Analiz Dökümanı

## Giriş

Bu belge, "Hastane Yönetim Sistemi" projesinin tasarımını ve çalışma mantığını açıklamaktadır. Proje, hastane operasyonlarını yönetmek için bir dizi işlevsellik sağlar ve hasta verilerini, reçeteleri ve randevuları yönetir.

## Akış Şemaları

### Hasta Ekleme Akış Şeması

```mermaid
graph TD;
    A["Kullanıcı 'Hasta Ekle' seçeneğini seçer"] --> B["Kullanıcıdan hasta bilgileri istenir"];
    B --> C["Yeni hasta bilgileri bağlı listeye eklenir"];
    C --> D["HL7 mesajı oluşturulur ve dosyaya kaydedilir"];
    D --> E["Hasta bilgileri dosyaya kaydedilir"];
    E --> F["Hasta eklendi mesajı görüntülenir"];
```

### Hasta Durumu Güncelleme Akış Şeması

```mermaid
graph TD;
    A["Kullanıcı 'Hasta Durumu Güncelle' seçeneğini seçer"] --> B["Kullanıcıdan güncellenecek hastanın ID'si istenir"];
    B --> C["Kullanıcıdan yeni durum bilgisi istenir"];
    C --> D["İlgili hasta bulunur ve durumu güncellenir"];
    D --> E["HL7 mesajı oluşturulur ve dosyaya kaydedilir"];
    E --> F["Hasta bilgileri dosyaya kaydedilir"];
    F --> G["Hasta durumu güncellendi mesajı görüntülenir"];
```

### Randevu Oluşturma Akış Şeması

```mermaid
graph TD;
    A["Kullanıcı 'Randevu Oluştur' seçeneğini seçer"] --> B["Kullanıcıdan randevu oluşturulacak hastanın ID'si istenir"];
    B --> C["İlgili hasta bulunur ve randevu kuyruğuna eklenir"];
    C --> D["HL7 mesajı oluşturulur ve dosyaya kaydedilir"];
    D --> E["Randevu oluşturuldu mesajı görüntülenir"];
```

### Sıradaki Hasta Akış Şeması

```mermaid
graph TD;
    A["Kullanıcı 'Sıradaki Hasta' seçeneğini seçer"] --> B["Randevu kuyruğunun başındaki hasta görüntülenir"];
    B --> C["Hasta randevu kuyruğundan çıkarılır"];
    C --> D["Sıradaki hasta bilgileri görüntülenir"];
```

### Hasta Taburcu Etme Akış Şeması

```mermaid
graph TD;
    A["Kullanıcı 'Hastayı Taburcu Et' seçeneğini seçer"] --> B["Kullanıcıdan taburcu edilecek hastanın ID'si istenir"];
    B --> C["İlgili hasta bulunur ve listeden çıkarılır"];
    C --> D["HL7 mesajı oluşturulur ve dosyaya kaydedilir"];
    D --> E["Hasta bilgileri dosyaya kaydedilir"];
    E --> F["Hasta taburcu edildi mesajı görüntülenir"];
```

## Çalışma Mantığı

- **Hasta Bilgileri:** Hasta bilgileri `Hasta` yapısında tutulur ve bağlı liste yapısı ile yönetilir.
- **Reçete Bilgileri:** Reçete bilgileri `Recete` yapısında tutulur ve bağlı liste yapısı ile yönetilir.
- **Randevu Sistemi:** Randevular, hastaların acil olup olmamasına göre önceliklendirilir ve bağlı liste ile yönetilir.
- **Dosya İşlemleri:** Hasta ve reçete bilgileri dosyaya kaydedilir ve dosyadan okunur. Ayrıca HL7 mesajları dosyaya kaydedilir.
- **HL7 Mesajları:** HL7 formatında mesajlar oluşturulur ve dosyaya kaydedilir.

## Sonuç

Bu proje, hastane yönetim sisteminin temel işlevlerini simüle eden bir C programıdır. Kullanıcı dostu arayüzü ve kapsamlı işlevleri ile hastane operasyonlarını etkin bir şekilde yönetmeyi amaçlar.
