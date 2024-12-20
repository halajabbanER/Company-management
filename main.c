/**
 * @file main.c
 * @description وظيفة main لاختبار جميع الوظائف لتعريف وإدارة الأقسام والعاملين.
 * @assignment Lab Dersi 1. Ödev
 * @date 2024-04-27
 * @author Hala Jabban 2121221350
 */

#include <stdio.h>
#include "Proje1.h"
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "UTF-8");

    // التحقق من عدد المدخلات
    if (argc != 3)
    {
        printf("Kullanim: %s <birimler.txt> <calisanlar.txt>\n", argv[0]);
        return 1;
    }

    const char *birimDosyasi = argv[1];
    const char *calisanDosyasi = argv[2];

    int birimSayisi = 0;
    Birim *birimler = NULL;
    
        // قراءة البيانات من الملفات عند بدء البرنامج
        verileriDosyadanOku(&birimler, &birimSayisi, birimDosyasi, calisanDosyasi);
        printf("Dosyalardan veriler basariyla okundu.\n\n");

        // إضافة قسم جديد
        Birim yeniBirimMuhasebe = yeniBirimOlustur("Muhasebe", 101);
        birimEkle(&birimler, &birimSayisi, yeniBirimMuhasebe);
        printf("Yeni birim eklendi:\n");
        birimBilgileriniYazdir(&birimler[birimSayisi - 1]);

        Birim yeniBirimHR = yeniBirimOlustur("HR", 102);
        birimEkle(&birimler, &birimSayisi, yeniBirimHR);

        Birim yeniBirimIT = yeniBirimOlustur("IT", 103);
        birimEkle(&birimler, &birimSayisi, yeniBirimIT);

        Birim yeniBirimMarketing = yeniBirimOlustur("Marketing", 104);
        birimEkle(&birimler, &birimSayisi, yeniBirimMarketing);

        // إضافة موظف جديد إلى قسم 101 (Muhasebe)
        Calisan yeniCalisanMuhasebe = yeniCalisanOlustur("Ali", "Veli", 101, 5000.0, 2015);
        calisanEkle(&birimler[birimSayisi - 4], yeniCalisanMuhasebe);


         // قسم Muhasebe

        // إضافة موظف جديد إلى قسم 102 (HR)
        Calisan yeniCalisanHR = yeniCalisanOlustur("ibrahem", "Ali", 102, 4500.0, 2018);
        calisanEkle(&birimler[birimSayisi - 3], yeniCalisanHR); // قسم HR


        // إضافة موظف جديد إلى قسم 103 (IT)
        Calisan yeniCalisanIT = yeniCalisanOlustur("hala", "Smith", 103, 7000.0, 2020);
        calisanEkle(&birimler[birimSayisi - 2], yeniCalisanIT); // قسم IT

        // إضافة موظف جديد إلى قسم 104 (Marketing)
        Calisan yeniCalisanMarketing = yeniCalisanOlustur("Zain", "Khaled", 104, 5500.0, 2021);
        calisanEkle(&birimler[birimSayisi - 1], yeniCalisanMarketing); // قسم Marketing

        // طباعة جميع الأقسام
        printf("\nTum Birimler:\n");
        tumBirimleriYazdir(birimler, birimSayisi);

        // حساب متوسط الراتب في القسم 101 (Muhasebe)
        printf("Birim: Muhasebe | Ortalama Maas: %.2f\n\n", ortalamaMaasHesapla(&birimler[birimSayisi - 4]));

        // قائمة العاملين الذين يتجاوز راتبهم المتوسط في القسم 101 (Muhasebe)
        printf("Ortalama maasin uzerinde olan calisanlar:\n");
        ustOrtalamayiAlanlariListele(&birimler[birimSayisi - 4]);

        // قائمة أعلى راتب في كل قسم
        printf("Her birimin en yuksek maas alan calisanlari:\n");
        enYuksekMaasAlanlariListele(birimler, birimSayisi);

        // تحديث الرواتب بناءً على الشروط المحددة (الزيادة إلى 6000)
        printf("Maas guncelleme islemi:\n");
        maaslariGuncelle(birimler, birimSayisi, 6000.0);

        // كتابة البيانات إلى الملفات عند إغلاق البرنامج
        verileriDosyayaYaz(birimler, birimSayisi, birimDosyasi, calisanDosyasi);
        printf("\nVeriler dosyalara basariyla yazildi.\n");

        // تحرير الذاكرة المخصصة
        bellekTemizle(birimler, birimSayisi);

        return 0;
            
}
