/**
 * @file Proje1.c
 * @description تنفيذ جميع الوظائف لتعريف وإدارة الأقسام والعاملين.
 * @assignment Lab Dersi 1. Ödev
 * @date 2024-04-27
 * @author Hala Jabban 2121221350
 */

#include "Proje1.h"

// 1. إنشاء هيكل Birim جديد
Birim yeniBirimOlustur(const char *birimAdi, unsigned short int birimKodu)
{
    Birim birim;
    birim.birimAdi = (char *)malloc(30 * sizeof(char));
    if (birim.birimAdi == NULL)
    {
        printf("Bellek tahsisi basarisiz oldu.\n");
        exit(1);
    }
    strncpy(birim.birimAdi, birimAdi, 29);
    birim.birimAdi[29] = '\0'; // تأكد من إنهاء السلسلة
    birim.birimKodu = birimKodu;
    birim.birimCalisanlar = NULL;
    birim.calisanSayisi = 0;
    return birim;
}

// 2. إنشاء هيكل Calisan جديد
Calisan yeniCalisanOlustur(const char *adi, const char *soyadi, unsigned short int birimKodu, float maas, int girisYili)
{
    Calisan calisan;
    calisan.calisanAdi = (char *)malloc(30 * sizeof(char));
    calisan.calisanSoyadi = (char *)malloc(30 * sizeof(char));
    if (calisan.calisanAdi == NULL || calisan.calisanSoyadi == NULL)
    {
        printf("Bellek tahsisi basarisiz oldu.\n");
        exit(1);
    }
    strncpy(calisan.calisanAdi, adi, 29);
    calisan.calisanAdi[29] = '\0';
    strncpy(calisan.calisanSoyadi, soyadi, 29);
    calisan.calisanSoyadi[29] = '\0';
    calisan.birimKodu = birimKodu;
    calisan.maas = maas;
    calisan.girisYili = girisYili;
    return calisan;
}

// 3. إضافة Birim إلى مصفوفة Birim
void birimEkle(Birim **birimler, int *birimSayisi, Birim yeniBirim)
{
    *birimler = (Birim *)realloc(*birimler, (*birimSayisi + 1) * sizeof(Birim));
    if (*birimler == NULL)
    {
        printf("Bellek yeniden tahsisi basarisiz oldu.\n");
        exit(1);
    }
    (*birimler)[*birimSayisi] = yeniBirim;
    (*birimSayisi)++;
}

// 4. إضافة Calisan إلى Birim معين
void calisanEkle(Birim *birim, Calisan calisan)
{
    birim->birimCalisanlar = (Calisan *)realloc(birim->birimCalisanlar, (birim->calisanSayisi + 1) * sizeof(Calisan));
    if (birim->birimCalisanlar == NULL)
    {
        printf("Bellek yeniden tahsisi basarisiz oldu.\n");
        exit(1);
    }
    birim->birimCalisanlar[birim->calisanSayisi] = calisan;
    birim->calisanSayisi++;
}

// 5. طباعة معلومات Calisan
void calisanBilgileriniYazdir(const Calisan *calisan)
{
    printf("Ad: %s | Soyad: %s | Birim Kodu: %d | Maas: %.2f | Giris Yili: %d\n",
           calisan->calisanAdi, calisan->calisanSoyadi, calisan->birimKodu, calisan->maas, calisan->girisYili);
}

// 6. طباعة معلومات Birim
void birimBilgileriniYazdir(const Birim *birim)
{
    printf("Birim Adi: %s | Birim Kodu: %d | Calisan Sayisi: %d\n", birim->birimAdi, birim->birimKodu, birim->calisanSayisi);
    for (int i = 0; i < birim->calisanSayisi; i++)
    {
        calisanBilgileriniYazdir(&birim->birimCalisanlar[i]);
    }
    printf("\n");
}

// 7. طباعة جميع أقسام Birim
void tumBirimleriYazdir(const Birim *birimler, int birimSayisi)
{
    for (int i = 0; i < birimSayisi; i++)
    {
        birimBilgileriniYazdir(&birimler[i]);
    }
}

// 8. حساب متوسط الراتب في Birim
float ortalamaMaasHesapla(const Birim *birim)
{
    if (birim->calisanSayisi == 0)
        return 0.0;
    float toplam = 0.0;
    for (int i = 0; i < birim->calisanSayisi; i++)
    {
        toplam += birim->birimCalisanlar[i].maas;
    }
    return toplam / birim->calisanSayisi;
}

// 9. قائمة العاملين الذين يتجاوز راتبهم المتوسط في Birim
void ustOrtalamayiAlanlariListele(const Birim *birim)
{
    float ortalama = ortalamaMaasHesapla(birim);
    printf("Birim: %s | Ortalama Maas: %.2f\n", birim->birimAdi, ortalama);
    printf("Ortalama Maasin Uzerinde Olan Calisanlar:\n");
    for (int i = 0; i < birim->calisanSayisi; i++)
    {
        if (birim->birimCalisanlar[i].maas > ortalama)
        {
            calisanBilgileriniYazdir(&birim->birimCalisanlar[i]);
        }
    }
    printf("\n");
}

// 10. قائمة أعلى راتب في كل Birim
void enYuksekMaasAlanlariListele(const Birim *birimler, int birimSayisi)
{
    for (int i = 0; i < birimSayisi; i++)
    {
        if (birimler[i].calisanSayisi == 0)
        {
            printf("Birim: %s | Calisan Yok\n", birimler[i].birimAdi);
            continue;
        }
        Calisan *enYuksek = &birimler[i].birimCalisanlar[0];
        for (int j = 1; j < birimler[i].calisanSayisi; j++)
        {
            if (birimler[i].birimCalisanlar[j].maas > enYuksek->maas)
            {
                enYuksek = &birimler[i].birimCalisanlar[j];
            }
        }
        printf("Birim: %s | En Yuksek Maas Alan Calisan:\n", birimler[i].birimAdi);
        calisanBilgileriniYazdir(enYuksek);
        printf("\n");
    }
}

// 11. تحديث الرواتب بناءً على الشروط المحددة
void maaslariGuncelle(Birim *birimler, int birimSayisi, float belirliMaas)
{
    for (int i = 0; i < birimSayisi; i++)
    {
        for (int j = 0; j < birimler[i].calisanSayisi; j++)
        {
            int calismaYili = 2024 - birimler[i].birimCalisanlar[j].girisYili;
            if (calismaYili > 10 && birimler[i].birimCalisanlar[j].maas < belirliMaas)
            {
                birimler[i].birimCalisanlar[j].maas = belirliMaas;
                printf("Maas guncellendi: ");
                calisanBilgileriniYazdir(&birimler[i].birimCalisanlar[j]);
            }
        }
    }
}

// 12. كتابة البيانات إلى الملفات
void verileriDosyayaYaz(const Birim *birimler, int birimSayisi, const char *birimDosyasi, const char *calisanDosyasi)
{
    FILE *birimFile = fopen(birimDosyasi, "w");
    if (birimFile == NULL)
    {
        printf("Birim dosyasi acilamadi.\n");
        return;
    }
    fprintf(birimFile, "%d\n", birimSayisi);
    for (int i = 0; i < birimSayisi; i++)
    {
        fprintf(birimFile, "%s %d %d\n", birimler[i].birimAdi, birimler[i].birimKodu, birimler[i].calisanSayisi);
    }
    fclose(birimFile);

    FILE *calisanFile = fopen(calisanDosyasi, "w");
    if (calisanFile == NULL)
    {
        printf("Calisan dosyasi acilamadi.\n");
        return;
    }
    for (int i = 0; i < birimSayisi; i++)
    {
        for (int j = 0; j < birimler[i].calisanSayisi; j++)
        {
            fprintf(calisanFile, "%s %s %d %.2f %d\n",
                    birimler[i].birimCalisanlar[j].calisanAdi,
                    birimler[i].birimCalisanlar[j].calisanSoyadi,
                    birimler[i].birimCalisanlar[j].birimKodu,
                    birimler[i].birimCalisanlar[j].maas,
                    birimler[i].birimCalisanlar[j].girisYili);
        }
    }
    fclose(calisanFile);
}

// 13. قراءة البيانات من الملفات
void verileriDosyadanOku(Birim **birimler, int *birimSayisi, const char *birimDosyasi, const char *calisanDosyasi)
{
    FILE *birimFile = fopen(birimDosyasi, "r");
    if (birimFile == NULL)
    {
        printf("Birim dosyasi acilamadi.\n");
        return;
    }

    fscanf(birimFile, "%d\n", birimSayisi);
    *birimler = (Birim *)malloc(*birimSayisi * sizeof(Birim));
    if (*birimler == NULL)
    {
        printf("Bellek tahsisi basarisiz oldu.\n");
        exit(1);
    }

    for (int i = 0; i < *birimSayisi; i++)
    {
        char tempBirimAdi[30];
        fscanf(birimFile, "%s %hu %d\n", tempBirimAdi, &((*birimler)[i].birimKodu), &((*birimler)[i].calisanSayisi));
        (*birimler)[i].birimAdi = (char *)malloc(30 * sizeof(char));
        if ((*birimler)[i].birimAdi == NULL)
        {
            printf("Bellek tahsisi basarisiz oldu.\n");
            exit(1);
        }
        strncpy((*birimler)[i].birimAdi, tempBirimAdi, 29);
        (*birimler)[i].birimAdi[29] = '\0';
        (*birimler)[i].birimCalisanlar = NULL;
    }
    fclose(birimFile);

    FILE *calisanFile = fopen(calisanDosyasi, "r");
    if (calisanFile == NULL)
    {
        printf("Calisan dosyasi acilamadi.\n");
        return;
    }

    for (int i = 0; i < *birimSayisi; i++)
    {
        if ((*birimler)[i].calisanSayisi > 0)
        {
            (*birimler)[i].birimCalisanlar = (Calisan *)malloc((*birimler)[i].calisanSayisi * sizeof(Calisan));
            if ((*birimler)[i].birimCalisanlar == NULL)
            {
                printf("Bellek tahsisi basarisiz oldu.\n");
                exit(1);
            }
            for (int j = 0; j < (*birimler)[i].calisanSayisi; j++)
            {
                char tempAdi[30];
                char tempSoyadi[30];
                fscanf(calisanFile, "%s %s %hu %f %d\n", tempAdi, tempSoyadi,
                       &((*birimler)[i].birimCalisanlar[j].birimKodu),
                       &((*birimler)[i].birimCalisanlar[j].maas),
                       &((*birimler)[i].birimCalisanlar[j].girisYili));

                (*birimler)[i].birimCalisanlar[j].calisanAdi = (char *)malloc(30 * sizeof(char));
                (*birimler)[i].birimCalisanlar[j].calisanSoyadi = (char *)malloc(30 * sizeof(char));
                if ((*birimler)[i].birimCalisanlar[j].calisanAdi == NULL || (*birimler)[i].birimCalisanlar[j].calisanSoyadi == NULL)
                {
                    printf("Bellek tahsisi basarisiz oldu.\n");
                    exit(1);
                }
                strncpy((*birimler)[i].birimCalisanlar[j].calisanAdi, tempAdi, 29);
                (*birimler)[i].birimCalisanlar[j].calisanAdi[29] = '\0';
                strncpy((*birimler)[i].birimCalisanlar[j].calisanSoyadi, tempSoyadi, 29);
                (*birimler)[i].birimCalisanlar[j].calisanSoyadi[29] = '\0';
            }
        }
    }
    fclose(calisanFile);
}

// 14. تحرير الذاكرة المخصصة
void bellekTemizle(Birim *birimler, int birimSayisi)
{
    for (int i = 0; i < birimSayisi; i++)
    {
        free(birimler[i].birimAdi);
        for (int j = 0; j < birimler[i].calisanSayisi; j++)
        {
            free(birimler[i].birimCalisanlar[j].calisanAdi);
            free(birimler[i].birimCalisanlar[j].calisanSoyadi);
        }
        free(birimler[i].birimCalisanlar);
    }
    free(birimler);
}
