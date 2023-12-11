#ifndef BANKA_H
#define BANKA_H

#include "Hisse.h"
#include "Emir.h"
#include "Portfoy.h"

struct BANKA{
	
	Emir super;
	Hisse super2;
	Portfoy super3;
	
	int uzunlukBanka;
	
	//satis icin
	char **sembolSatis;
	double *satisUcret;
	double *satisMaliyet;
	
	int satisIndex;
	
	void (*verileriKaydetPortfoy)(struct BANKA*,char*);
	void (*verileriKaydetHisse)(struct BANKA*,char*);
	void (*verileriKaydetEmir)(struct BANKA*,char*);
	void (*hesapla)(struct BANKA*);
	int (*portfoyIndexBul)(struct BANKA*,char*);
	int (*hisseIndexBul)(struct BANKA*,char*);

	void (*yazdir)(struct BANKA*);
	void (*yoket)(struct BANKA*);	
};
typedef struct BANKA* Banka;

Banka BankaOlustur(int,int,int,int);
void VerileriKaydetPortfoy(const Banka,char*);
void VerileriKaydetHisse(const Banka,char*);
void VerileriKaydetEmir(const Banka,char*);
void Hesapla(const Banka);
int PortfoyIndexBul(const Banka,char*);
int HisseIndexBul(const Banka,char*);

void Yazdir(const Banka);
void Yoket(Banka);

#endif