#ifndef HISSE_H
#define HISSE_H

#include "Metot.h"

struct HISSE{//hisse yapisi ile dosyadan parcaladigim verileri bu dizilere kaydedip ustunde islem yapabilirim
	
	Metot super;
	
	int uzunlukHisse;//dizilerin boyutlari icin yani icinde bilge olan satir sayisidir
	char **id;
	char **sembol;
	char **ad;
	double *fiyat;
	
	void (*hisseVeriParcalaKaydet)(struct HISSE*,char*);
	void (*hisseYazdir)(struct HISSE*);
	void (*hisseYoket)(struct HISSE*);
	
};
typedef struct HISSE* Hisse;

Hisse HisseOlustur(int);
void HisseVeriParcalaKaydet(const Hisse,char*);
void HisseYazdir(const Hisse);
void HisseYoket(Hisse);

#endif