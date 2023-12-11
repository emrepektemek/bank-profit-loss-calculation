#ifndef PORTFOY_H
#define PORTFOY_H

#include "Metot.h"

struct PORTFOY{//portfoy yapisi ile dosyadan parcaladigim verileri bu dizilere kaydedip ustunde islem yapabilirim
	
	Metot super;
	
	int uzunlukPortfoy;//dizilerin boyutlari icin yani icinde bilge olan satir sayisidir
	int kapasitePortfoy;
	char **id;
	char **sembol;
	double *maliyet;
	int *adet;
	
	void (*portfoyVeriParcalaKaydet)(struct PORTFOY*,char*);
	void (*portfoyGenislet)(struct PORTFOY*);
	void (*portfoyYazdir)(struct PORTFOY*);
	void (*portfoyYoket)(struct PORTFOY*);
	
};
typedef struct PORTFOY* Portfoy;

Portfoy PortfoyOlustur(int);
void PortfoyVeriParcalaKaydet(const Portfoy,char*);
void PortfoyGenislet(const Portfoy);
void PortfoyYazdir(const Portfoy);
void PortfoyYoket(Portfoy);

#endif