#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Baslik
void baslikGoster() {
    printf("**************************************\n");
    printf("*       Hastane Yonetim Sistemi      *\n");
    printf("**************************************\n\n");
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
typedef struct Nodo {
    Hasta hasta;
    struct Nodo* sonraki;
} Nodo;

// Ilac Bilgileri Yapisi
typedef struct {
    int id;
    char ilac_adi[50];
    char doz[20];
} Recete;

// Ilac Bilgileri Bagli Liste Elemani
typedef struct ReceteNodo {
    Recete recete;
    struct ReceteNodo* sonraki;
} ReceteNodo;

// Fonksiyon Prototipleri
void hastaEkle();
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

// Global Degiskenler
Nodo* hastaBas = NULL;
ReceteNodo* receteBas = NULL;
Nodo* randevuKuyrugu = NULL;
Nodo* randevuSon = NULL;
Nodo* taburcuListeBas = NULL;

int main() {
    int secim;

    baslikGoster();

    while (1) {
        menuGoster();
        printf("Bir secenek girin: ");
        scanf("%d", &secim);

        printf("\n");

        switch (secim) {
            case 1:
                hastaEkle();
                break;
            case 2:
                tumHastalariGoruntule();
                break;
            case 3:
                hastaDurumuGuncelle();
                break;
            case 4:
                randevuOlustur();
                break;
            case 5:
                siradakiHasta();
                break;
            case 6:
                receteOlustur();
                break;
            case 7:
                tumReceteleriGoruntule();
                break;
            case 8:
                hastayiTaburcuEt();
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
}

void hastaEkle() {
    Hasta hasta;
    Nodo* yeniNodo = (Nodo*)malloc(sizeof(Nodo));

    printf("Hasta ID: ");
    scanf("%d", &hasta.id);
    printf("Hasta Adi: ");
    scanf("%s", hasta.ad);
    printf("Hasta Soyadi: ");
    scanf("%s", hasta.soyad);
    printf("Hasta Durumu: ");
    scanf("%s", hasta.durum);
    hasta.oncelik = oncelikSor();
    int siraNo = siraNoUret();
    
    printf("Sira No: %d\n", siraNo);

    yeniNodo->hasta = hasta;
    yeniNodo->sonraki = hastaBas;
    hastaBas = yeniNodo;

    hl7MesajiOlustur(hasta, "Hasta Ekle");
    printf("\nHasta eklendi.\n");
}

void tumHastalariGoruntule() {
    Nodo* temp = hastaBas;
    if (temp == NULL) {
        printf("Kayitli hasta bulunmamaktadir.\n");
        return;
    }
    while (temp != NULL) {
        printf("ID: %d, Ad: %s, Soyad: %s, Durum: %s, Oncelik: %s\n", temp->hasta.id, temp->hasta.ad, temp->hasta.soyad, temp->hasta.durum, temp->hasta.oncelik ? "Acil" : "Normal");
        temp = temp->sonraki;
    }
}

void hastaDurumuGuncelle() {
    int id = hastaIdAl();
    char yeniDurum[100];
    Nodo* temp = hastaBas;

    printf("Yeni Durum: ");
    scanf("%s", yeniDurum);

    while (temp != NULL) {
        if (temp->hasta.id == id) {
            strcpy(temp->hasta.durum, yeniDurum);
            hl7MesajiOlustur(temp->hasta, "Hasta Durumu Guncelle");
            printf("\nHasta durumu guncellendi.\n");
            return;
        }
        temp = temp->sonraki;
    }
    printf("Hasta bulunamadi.\n");
}

void receteOlustur() {
    Recete recete;
    ReceteNodo* yeniNodo = (ReceteNodo*)malloc(sizeof(ReceteNodo));

    printf("Recete ID: ");
    scanf("%d", &recete.id);
    printf("Ilac Adi: ");
    scanf("%s", recete.ilac_adi);
    printf("Doz: ");
    scanf("%s", recete.doz);

    yeniNodo->recete = recete;
    yeniNodo->sonraki = receteBas;
    receteBas = yeniNodo;

    char* receteNo = receteNoUret();
    printf("\nRecete olusturuldu. Recete No: %s\n", receteNo);
    free(receteNo);
}

void tumReceteleriGoruntule() {
    ReceteNodo* temp = receteBas;
    if (temp == NULL) {
        printf("Kayitli recete bulunmamaktadir.\n");
        return;
    }
    while (temp != NULL) {
        printf("ID: %d, Ilac Adi: %s, Doz: %s\n", temp->recete.id, temp->recete.ilac_adi, temp->recete.doz);
        temp = temp->sonraki;
    }
}

void randevuOlustur() {
    int hastaId = hastaIdAl();
    Nodo* hasta = hastaBas;

    while (hasta != NULL && hasta->hasta.id != hastaId) {
        hasta = hasta->sonraki;
    }

    if (hasta == NULL) {
        printf("Hasta bulunamadi\n");
        return;
    }

    Nodo* yeniNodo = (Nodo*)malloc(sizeof(Nodo));
    yeniNodo->hasta = hasta->hasta;
    yeniNodo->sonraki = NULL;

    if (randevuSon == NULL) {
        randevuKuyrugu = yeniNodo;
        randevuSon = yeniNodo;
    } else {
        randevuSon->sonraki = yeniNodo;
        randevuSon = yeniNodo;
    }

    hl7MesajiOlustur(hasta->hasta, "Randevu Olustur");
    printf("\nRandevu olusturuldu.\n");
}

void siradakiHasta() {
    if (randevuKuyrugu == NULL) {
        printf("Bekleyen hasta yok\n");
        return;
    }

    Nodo* temp = randevuKuyrugu;
    printf("Siradaki Hasta - ID: %d, Ad: %s, Soyad: %s, Durum: %s, Oncelik: %s\n", temp->hasta.id, temp->hasta.ad, temp->hasta.soyad, temp->hasta.durum, temp->hasta.oncelik ? "Acil" : "Normal");
    randevuKuyrugu = randevuKuyrugu->sonraki;
    free(temp);

    if (randevuKuyrugu == NULL) {
        randevuSon = NULL;
    }
}

void hastayiTaburcuEt() {
    int id = hastaIdAl();
    Nodo* temp = hastaBas;
    Nodo* onceki = NULL;

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

    temp->sonraki = taburcuListeBas;
    taburcuListeBas = temp;

    hl7MesajiOlustur(temp->hasta, "Hasta Taburcu Et");
    printf("\nHasta taburcu edildi.\n");
}

int hastaIdAl() {
    int id;
    printf("Hasta ID: ");
    scanf("%d", &id);
    return id;
}

char* receteNoUret() {
    time_t t;
    srand((unsigned) time(&t));
    int randomNum = rand() % 1000000;

    char* receteNo = (char*) malloc(10 * sizeof(char));
    sprintf(receteNo, "%06d", randomNum);

    return receteNo;
}

void hl7MesajiOlustur(Hasta hasta, const char* islem) {
    printf("\nHL7 Mesaji Olusturuluyor: %s\n", islem);
    printf("MSH|^~\\&|Hastane Bilgi Sistemi|Hastane|Hasta Kayit Sistemi|Hastane|%s||ADT^A01|%d|P|2.3\n", __TIMESTAMP__, rand() % 1000000);
    printf("PID|1|%d|%d||%s^%s||19700101|M||2106-3|1234 Main St^^Metropolis^IL^12345^USA||(312)555-1212||(312)555-1213||S||PATID1234^2^M10|123456789|987654^^^&2.16.840.1.113883.19.3.2.1.1.9&ISO^MR\n",
           hasta.id, hasta.id, hasta.ad, hasta.soyad);
    printf("PV1|1|I|2000^2012^01||||004777^Doktor^Adi^A.|||||||||||V||2|A0\n");
    printf("AL1|1||^Penicillin||Produces hives\n");
    printf("ORC|RE|%s^%s|%s^%s||CM||||%s\n", receteNoUret(), "Hastane", receteNoUret(), "Hastane", __TIMESTAMP__);
    printf("OBR|1|||Complete Blood Count|||%s\n", __TIMESTAMP__);
    printf("OBX|1|NM|^WBC|1|6.7|10*3/uL|4.5-11.0|N|||F\n");
    printf("\n");
}

int oncelikSor() {
    char cevap;
    printf("Hasta durumu acil mi? (E/H): ");
    scanf(" %c", &cevap); // Note the space before %c to consume any trailing newline character
    if (cevap == 'E' || cevap == 'e') {
        return 1; // Acil
    }
    return 0; // Normal
}

int siraNoUret() {
    static int siraNo = 0;
    return ++siraNo;
}
