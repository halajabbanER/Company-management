/**
 * @file Proje1.h
 * @description Bolumler ve calisanlarin yonetimi icin yapilarin tanimlari ve fonksiyon bildirimlerini icerir.
 * @assignment Lab Dersi 1. Odev
 * @date 10.12.2024 -22.12.2024
 * @author Hala Jabban 2121221350
 */

#ifndef PROJE1_H
#define PROJE1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Calisan yapisinin tanimi
typedef struct
{
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

// Birim yapisinin tanimi
typedef struct
{
    char *birimAdi;
    unsigned short int birimKodu;
    Calisan *birimCalisanlar;
    int calisanSayisi; // Birimdeki calisan sayisini takip etmek icin
} Birim;

// Fonksiyon bildirimleri

// 1. Yeni bir Birim yapisi olusturur
Birim yeniBirimOlustur(const char *birimAdi, unsigned short int birimKodu);

// 2. Yeni bir Calisan yapisi olusturur
Calisan yeniCalisanOlustur(const char *adi, const char *soyadi, unsigned short int birimKodu, float maas, int girisYili);

// 3. Birim dizisine Birim ekler
void birimEkle(Birim **birimler, int *birimSayisi, Birim yeniBirim);

// 4. Belirli bir Birim'e Calisan ekler
void calisanEkle(Birim *birim, Calisan calisan);

// 5. Calisan bilgilerini yazdirir
void calisanBilgileriniYazdir(const Calisan *calisan);

// 6. Birim bilgilerini yazdirir
void birimBilgileriniYazdir(const Birim *birim);

// 7. Tum Birim bilgilerini yazdirir
void tumBirimleriYazdir(const Birim *birimler, int birimSayisi);

// 8. Birimdeki ortalama maasi hesaplar
float ortalamaMaasHesapla(const Birim *birim);

// 9. Ortalamanin uzerinde maas alan calisanlari listeler
void ustOrtalamayiAlanlariListele(const Birim *birim);

// 10. Her Birim'deki en yuksek maas alanlari listeler
void enYuksekMaasAlanlariListele(const Birim *birimler, int birimSayisi);

// 11. Maaslari belirli kosullara gore gunceller
void maaslariGuncelle(Birim *birimler, int birimSayisi, float belirliMaas);

// 12. Verileri dosyalara yazar
void verileriDosyayaYaz(const Birim *birimler, int birimSayisi, const char *birimDosyasi, const char *calisanDosyasi);

// 13. Verileri dosyalardan okur
void verileriDosyadanOku(Birim **birimler, int *birimSayisi, const char *birimDosyasi, const char *calisanDosyasi);

// 14. Tahsis edilen bellegi temizler
void bellekTemizle(Birim *birimler, int birimSayisi);

#endif
