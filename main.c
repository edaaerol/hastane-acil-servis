#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Bu kod, bir hastane yönetim sistemi uygulamasının temel işlevlerini içerir. 
//Kullanıcılar hasta ekleyebilir, hasta bilgilerini güncelleyebilir, reçete oluşturabilir ve randevu oluşturabilir. 
//Ayrıca, HL7 formatında mesajlar oluşturulup kaydedilir.

// Baslik
void baslikGoster() {
    printf("-       Hastane Yonetim Sistemi      -\n");
    printf("--------------------------------------\n\n");
}

// Hasta Bilgileri Yapisi
typedef struct {
    int id;
    char ad[50];
    char soyad[50];
    char durum[100];
    int oncelik; // 1 acil, 0 normal
} Hasta;

// Bagli Liste Elemani
typedef struct Node {
    Hasta hasta;  // Hasta bilgilerini tutan bir yapı
    struct Node* sonraki;
} Node;  // Hastaları bağlı listede tutmak için kullanılan düğüm

// Ilac Bilgileri Yapisi
typedef struct {
    int id;
    char ilac_adi[50];
    char doz[20];
} Recete;

// Ilac Bilgileri Bagli Liste Elemani
typedef struct ReceteNode {
    Recete recete;  // İlaç bilgilerini tutan bir yapı
    struct ReceteNode* sonraki;
} ReceteNode;  // İlaçları bağlı listede tutmak için kullanılan düğüm

void hastaEkle();  // Yeni hasta kaydı oluşturma
void tumHastalariGoruntule();
void hastaDurumuGuncelle();
void receteOlustur();
void tumReceteleriGoruntule();
void randevuOlustur();
void siradakiHasta();
void hastayiTaburcuEt();
void menuGoster();
int hastaIdAl();
char* receteNoUret();
void hl7MesajiOlustur(Hasta hasta, const char* islem);
int oncelikSor();
int siraNoUret();
void kayitlariDosyayaKaydet();
void kayitlariDosyadanOku();
void hl7MesajiDosyayaKaydet(const char* mesaj);
void freeReceteNo(char* receteNo);
// Fonksiyon prototipleri, fonksiyonların ne türde ve hangi parametrelerle çalıştığını belirtir.

Node* hastaBas = NULL;  // Tüm hastaların listesinin başlangıç noktası
ReceteNode* receteBas = NULL;  // Tüm reçetelerin listesinin başlangıç noktası
Node* randevuKuyrugu = NULL;  // Muayene için bekleyen hastaların sırası
Node* randevuSon = NULL;  // Randevu sırasının sonu
Node* taburcuListeBas = NULL;  // Taburcu edilen hastaların listesi
int siraNo = 0;
// Global değişkenler tanımlanır. Bu değişkenler, programın her yerinde kullanılabilir.

int main() {
    int secim;

    baslikGoster();
    kayitlariDosyadanOku();

    while (1) {
        menuGoster();
        printf("Bir secenek girin: ");
        if (scanf("%d", &secim) != 1) {
            printf("Gecersiz giris! Lutfen bir sayi girin.\n");
            while (getchar() != '\n'); // Hatali girisi temizlemek icin buffer'i temizle
            continue;
        } 

        printf("\n");

        switch (secim) {
            case 1:
                hastaEkle();  // Yeni hasta kaydı oluşturma
                break;
            case 2:
                tumHastalariGoruntule();  // Sisteme kayıtlı tüm hastaları listeleme
                break;
            case 3:
                hastaDurumuGuncelle();    // Mevcut bir hastanın durumunu değiştirme
                break;
            case 4:
                randevuOlustur();  // Hastalar için randevu oluşturma
                break;  
            case 5:
                siradakiHasta();  // Sıradaki hastayı çağırma
                break;
            case 6:
                receteOlustur();  // Hastalar için ilaç reçetesi hazırlama
                break;
            case 7:
                tumReceteleriGoruntule();  // Oluşturulan tüm reçeteleri listeleme
                break;
            case 8:
                hastayiTaburcuEt();  // Bir hastayı sistemden çıkarma
                break;
            case 9:
                printf("Cikis yapiliyor...\n");
                exit(0);
            default:
                printf("Gecersiz secenek!\n");
        }

        printf("\n");
    }

    return 0;
}
// Kullanıcıdan seçim almak ve ilgili işlemleri yapmak için bir sonsuz döngü (while (1)) kullanılır. 
// Kullanıcı geçerli bir seçenek girmezse, hata mesajı gösterilir ve döngü devam eder. 
// Kullanıcı geçerli bir seçenek girerse, switch ifadesi kullanılarak ilgili fonksiyon çağrılır.

void menuGoster() { 
    printf("\n1. Hasta Ekle\n");
    printf("2. Tum Hastalari Goruntule\n");
    printf("3. Hasta Durumu Guncelle\n");
    printf("4. Randevu Olustur\n");
    printf("5. Siradaki Hasta\n");
    printf("6. Recete Olustur\n");
    printf("7. Tum Receteleri Goruntule\n");
    printf("8. Hastayi Taburcu Et\n");
    printf("9. Cikis\n");
}  // menuGoster fonksiyonu, kullanıcıya mevcut seçenekleri gösterir.

void hastaEkle() {
    Hasta hasta;
    Node* yeniNode = (Node*)malloc(sizeof(Node));
    if (yeniNode == NULL) {
        printf("Bellek tahsisi basarisiz oldu.\n");
        return;
    }

    printf("Hasta ID: ");
    scanf("%d", &hasta.id);
    printf("Hasta Adi: ");
    scanf("%49s", hasta.ad); // Güvenli giriş
    printf("Hasta Soyadi: ");
    scanf("%49s", hasta.soyad); // Güvenli giriş
    printf("Hasta Durumu: ");
    getchar(); // Önceki yeni satır karakterini temizle
    fgets(hasta.durum, sizeof(hasta.durum), stdin); // Güvenli giriş
    hasta.durum[strcspn(hasta.durum, "\n")] = 0; // Yeni satır karakterini kaldır
    hasta.oncelik = oncelikSor();
    int siraNo = siraNoUret();
    
    printf("Sira No: %d\n", siraNo);

    yeniNode->hasta = hasta;
    yeniNode->sonraki = hastaBas;
    hastaBas = yeniNode;

    hl7MesajiOlustur(hasta, "Hasta Ekle");
    kayitlariDosyayaKaydet();
    printf("\nHasta eklendi.\n");
} // hastaEkle fonksiyonu, yeni bir hasta kaydı oluşturur. Bellek tahsisi yapılır ve kullanıcının girdiği bilgiler hasta yapısına atanır. 
// Hasta acil mi, değil mi sorulur ve sıra numarası üretilir. Yeni hasta düğümü listenin başına eklenir. HL7 mesajı oluşturulur ve kayıtlar dosyaya kaydedilir.

void tumHastalariGoruntule() {
    Node* temp = hastaBas;
    if (temp == NULL) {
        printf("Kayitli hasta bulunmamaktadir.\n");
        return;
    }
    while (temp != NULL) {
        printf("ID: %d, Ad: %s, Soyad: %s, Durum: %s, Oncelik: %s\n", temp->hasta.id, temp->hasta.ad, temp->hasta.soyad, temp->hasta.durum, temp->hasta.oncelik ? "Acil" : "Normal");
        temp = temp->sonraki;
    }
} // tumHastalariGoruntule fonksiyonu, sistemde kayıtlı tüm hastaları görüntüler. Liste başından başlayarak her düğümdeki hasta bilgilerini ekrana yazdırır.

void hastaDurumuGuncelle() {
    int id = hastaIdAl();
    char yeniDurum[100];
    Node* temp = hastaBas;

    printf("Yeni Durum: ");
    getchar(); // Önceki yeni satır karakterini temizle
    fgets(yeniDurum, sizeof(yeniDurum), stdin); // Güvenli giriş
    yeniDurum[strcspn(yeniDurum, "\n")] = 0; // Yeni satır karakterini kaldır

    while (temp != NULL) {
        if (temp->hasta.id == id) {
            strcpy(temp->hasta.durum, yeniDurum);
            hl7MesajiOlustur(temp->hasta, "Hasta Durumu Guncelle");
            kayitlariDosyayaKaydet();
            printf("\nHasta durumu guncellendi.\n");
            return;
        }
        temp = temp->sonraki;
    }
    printf("Hasta bulunamadi.\n");
}  // hastaDurumuGuncelle fonksiyonu, mevcut bir hastanın durumunu günceller. Kullanıcıdan hasta ID'si ve yeni durum bilgisi alınır.
// Liste başından başlayarak ilgili hasta bulunur ve durumu güncellenir. HL7 mesajı oluşturulur ve kayıtlar dosyaya kaydedilir.

void receteOlustur() {
    Recete recete;
    ReceteNode* yeniNode = (ReceteNode*)malloc(sizeof(ReceteNode));
    if (yeniNode == NULL) {
        printf("Bellek tahsisi basarisiz oldu.\n");
        return;
    }

    printf("Recete ID: ");
    scanf("%d", &recete.id);
    printf("Ilac Adi: ");
    scanf("%49s", recete.ilac_adi); // Güvenli giriş
    printf("Doz: ");
    scanf("%19s", recete.doz); // Güvenli giriş

    yeniNode->recete = recete;
    yeniNode->sonraki = receteBas;
    receteBas = yeniNode;

    char* receteNo = receteNoUret();
    printf("\nRecete olusturuldu. Recete No: %s\n", receteNo);
    freeReceteNo(receteNo);
}  // receteOlustur fonksiyonu, yeni bir reçete oluşturur. Bellek tahsisi yapılır ve kullanıcının girdiği bilgiler reçete yapısına atanır. 
// Yeni reçete düğümü listenin başına eklenir. Reçete numarası üretilir ve ekrana yazdırılır.

void tumReceteleriGoruntule() {
    ReceteNode* temp = receteBas;
    if (temp == NULL) {
        printf("Kayitli recete bulunmamaktadir.\n");
        return;
    }
    while (temp != NULL) {
        printf("ID: %d, Ilac Adi: %s, Doz: %s\n", temp->recete.id, temp->recete.ilac_adi, temp->recete.doz);
        temp = temp->sonraki;
    }
}  // tumReceteleriGoruntule fonksiyonu, sistemde kayıtlı tüm reçeteleri görüntüler. Liste başından başlayarak her düğümdeki reçete bilgilerini ekrana yazdırır.

void randevuOlustur() {
    int hastaId = hastaIdAl();
    Node* hasta = hastaBas;

    while (hasta != NULL && hasta->hasta.id != hastaId) {
        hasta = hasta->sonraki;
    }

    if (hasta == NULL) {
        printf("Hasta bulunamadi\n");
        return;
    }

    Node* yeniNode = (Node*)malloc(sizeof(Node));
    if (yeniNode == NULL) {
        printf("Bellek tahsisi basarisiz oldu.\n");
        return;
    }

    yeniNode->hasta = hasta->hasta;
    yeniNode->sonraki = NULL;

    if (hasta->hasta.oncelik == 1) {
        // Acil hastalar öne alınır
        yeniNode->sonraki = randevuKuyrugu;
        randevuKuyrugu = yeniNode;
        if (randevuSon == NULL) {
            randevuSon = yeniNode;
        }
    } else {
        // Normal hastalar kuyruğun sonuna eklenir
        if (randevuSon == NULL) {
            randevuKuyrugu = yeniNode;
            randevuSon = yeniNode;
        } else {
            randevuSon->sonraki = yeniNode;
            randevuSon = yeniNode;
        }
    }

    hl7MesajiOlustur(hasta->hasta, "Randevu Olustur");
    printf("\nRandevu olusturuldu.\n");
}  // randevuOlustur fonksiyonu, hastalar için randevu oluşturur. Kullanıcıdan hasta ID'si alınır ve ilgili hasta bulunur. 
// Bellek tahsisi yapılır ve yeni randevu düğümü oluşturulur. Hasta acilse, randevu kuyruğunun başına eklenir. 
// Normal hastalar kuyruğun sonuna eklenir. HL7 mesajı oluşturulur ve randevu oluşturulduğu mesajı ekrana yazdırılır.

void siradakiHasta() {
    if (randevuKuyrugu == NULL) {
        printf("Bekleyen hasta yok\n");
        return;
    }

    Node* temp = randevuKuyrugu;
    printf("Siradaki Hasta - ID: %d, Ad: %s, Soyad: %s, Durum: %s, Oncelik: %s\n", temp->hasta.id, temp->hasta.ad, temp->hasta.soyad, temp->hasta.durum, temp->hasta.oncelik ? "Acil" : "Normal");
    randevuKuyrugu = randevuKuyrugu->sonraki;
    free(temp);

    if (randevuKuyrugu == NULL) {
        randevuSon = NULL;
    }
}  // siradakiHasta fonksiyonu, sıradaki hastayı çağırır. Randevu kuyruğunun başındaki hasta bilgileri ekrana yazdırılır ve düğüm serbest bırakılır. Kuyruk başı güncellenir.

void hastayiTaburcuEt() {
    int id = hastaIdAl();
    Node *temp = hastaBas, *onceki = NULL;

    while (temp != NULL && temp->hasta.id != id) {
        onceki = temp;
        temp = temp->sonraki;
    }

    if (temp == NULL) {
        printf("Hasta bulunamadi\n");
        return;
    }

    if (onceki == NULL) {
        hastaBas = temp->sonraki;
    } else {
        onceki->sonraki = temp->sonraki;
    }

    hl7MesajiOlustur(temp->hasta, "Hasta Taburcu Et");
    kayitlariDosyayaKaydet();
    free(temp);
    printf("\nHasta taburcu edildi.\n");
}  // hastayiTaburcuEt fonksiyonu, bir hastayı sistemden çıkarır. Kullanıcıdan hasta ID'si alınır ve ilgili hasta bulunur. 
// Hasta listeden çıkarılır, HL7 mesajı oluşturulur ve kayıtlar dosyaya kaydedilir. Hasta serbest bırakılır ve taburcu edildiği mesajı ekrana yazdırılır.

int hastaIdAl() {
    int id;
    printf("Hasta ID: ");
    scanf("%d", &id);
    return id;
}  // hastaIdAl fonksiyonu, kullanıcıdan hasta ID'si alır ve döndürür.

char* receteNoUret() {
    time_t t;
    srand((unsigned) time(&t));
    int randomNum = rand() % 1000000;

    char* receteNo = (char*) malloc(10 * sizeof(char));
    if (receteNo == NULL) {
        printf("Bellek tahsisi basarisiz oldu.\n");
        exit(1);
    }
    sprintf(receteNo, "%06d", randomNum);

    return receteNo;
}  // receteNoUret fonksiyonu rastgele bir reçete numarası oluşturur ve döner.

void freeReceteNo(char* receteNo) {
    free(receteNo);
}  // freeReceteNo fonksiyonu reçete numarasını serbest bırakır.

void hl7MesajiOlustur(Hasta hasta, const char* islem) {
    char mesaj[1024];
    char* receteNo = receteNoUret();

    snprintf(mesaj, sizeof(mesaj),
        "MSH|^~\\&|Hastane Bilgi Sistemi|Hastane|Hasta Kayit Sistemi|Hastane|%s||ADT^A01|%d|P|2.3\n"
        "PID|1|%d|%d||%s^%s||19700101|M||2106-3|1234 Main St^^Metropolis^IL^12345^USA||(312)555-1212||(312)555-1213||S||PATID1234^2^M10|123456789|987654^^^&2.16.840.1.113883.19.3.2.1.1.9&ISO^MR\n"
        "PV1|1|I|2000^2012^01||||004777^Doktor^Adi^A.|||||||||||V||2|A0\n"
        "AL1|1||^Penicillin||Produces hives\n"
        "ORC|RE|%s^Hastane|%s^Hastane||CM||||%s\n"
        "OBR|1|||Complete Blood Count|||%s\n"
        "OBX|1|NM|^WBC|1|6.7|10*3/uL|4.5-11.0|N|||F\n",
        __TIMESTAMP__, rand() % 1000000, hasta.id, hasta.id, hasta.ad, hasta.soyad,
        receteNo, receteNo, __TIMESTAMP__, __TIMESTAMP__);

    printf("\nHL7 Mesaji Olusturuluyor: %s\n%s\n", islem, mesaj);
    hl7MesajiDosyayaKaydet(mesaj);
    freeReceteNo(receteNo);
}  // hl7MesajiOlustur fonksiyonu, HL7 formatında bir mesaj oluşturur ve bu mesajı bir dosyaya kaydeder. 
//HL7 mesajları, sağlık sistemleri arasında veri paylaşımı için standart bir formattır. 
// Fonksiyon, hasta bilgilerini kullanarak mesajı oluşturur ve ardından mesajı dosyaya yazar.

int oncelikSor() {
    char cevap;
    printf("Hasta durumu acil mi? (E/H): ");
    scanf(" %c", &cevap); // Note the space before %c to consume any trailing newline character
    if (cevap == 'E' || cevap == 'e') {
        return 1; // Acil
    }
    return 0; // Normal
}  // oncelikSor fonksiyonu, kullanıcıya hastanın durumunun acil olup olmadığını sorar ve buna göre 1 (acil) veya 0 (normal) döner.

int siraNoUret() {
    static int siraNo = 0;
    FILE *dosya = fopen("sira_no.txt", "r+");  // sira_no.txt: Otomatik sıra numarası üretimi için sayaç 
    if (dosya == NULL) {
        dosya = fopen("sira_no.txt", "w+");
        if (dosya == NULL) {
            printf("Sira numarasi dosyasi acilamadi.\n");
            exit(1);
        }
    }
    fscanf(dosya, "%d", &siraNo);
    siraNo++;
    rewind(dosya);
    fprintf(dosya, "%d", siraNo);
    fclose(dosya);
    return siraNo;
} // siraNoUret fonksiyonu, otomatik bir sıra numarası üretir ve bu numarayı bir dosyada saklar. Her çağrıldığında, mevcut sıra numarasını okur, bir artırır ve yeniden dosyaya yazar.

void kayitlariDosyayaKaydet() {
    FILE *dosya = fopen("hasta_kayitlari.txt", "w");  //hasta_kayitlari.txt: Hasta bilgileri
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    Node* temp = hastaBas;
    while (temp != NULL) {
        fprintf(dosya, "ID: %d, Ad: %s, Soyad: %s, Durum: %s, Oncelik: %s\n", 
                temp->hasta.id, temp->hasta.ad, temp->hasta.soyad, temp->hasta.durum, 
                temp->hasta.oncelik ? "Acil" : "Normal");
        temp = temp->sonraki;
    }

    fclose(dosya);
}  // kayitlariDosyayaKaydet fonksiyonu, hasta bilgilerini bir dosyaya yazar. Hasta listesinde gezinir ve her hastanın bilgilerini dosyaya kaydeder.

void kayitlariDosyadanOku() {
    FILE *dosya = fopen("hasta_kayitlari.txt", "r");
    if (dosya == NULL) {
        printf("Kayit dosyasi bulunamadi, yeni dosya olusturulacak.\n");
        return;
    }

    Hasta hasta;
    while (fscanf(dosya, "ID: %d, Ad: %49s, Soyad: %49s, Durum: %99[^\n], Oncelik: %49s\n",
                  &hasta.id, hasta.ad, hasta.soyad, hasta.durum, hasta.oncelik ? "Acil" : "Normal") != EOF) {
        Node* yeniNode = (Node*)malloc(sizeof(Node));
        if (yeniNode == NULL) {
            printf("Bellek tahsisi basarisiz oldu.\n");
            fclose(dosya);
            return;
        }
        yeniNode->hasta = hasta;
        yeniNode->sonraki = hastaBas;
        hastaBas = yeniNode;
    }
    fclose(dosya);
}  // kayitlariDosyadanOku fonksiyonu, hasta bilgilerini bir dosyadan okur ve hasta listesine ekler. Dosya bulunamazsa, yeni bir dosya oluşturulacağı belirtilir.

void hl7MesajiDosyayaKaydet(const char* mesaj) {
    FILE *dosya = fopen("hl7_mesajlari.txt", "a");  //hl7_mesajlari.txt: Sağlık sistemleri arasında veri paylaşımı için standart olan HL7 formatında mesajlar
    if (dosya == NULL) {
        printf("HL7 mesaj dosyasi acilamadi.\n");
        return;
    }
    fprintf(dosya, "%s\n", mesaj);
    fclose(dosya);
}  // hl7MesajiDosyayaKaydet fonksiyonu, HL7 mesajlarını bir dosyaya ekler. Mesajı dosyaya yazar ve dosyayı kapatır.
