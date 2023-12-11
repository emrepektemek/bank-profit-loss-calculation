#ifndef EMIR_H
#define EMIR_H

#include "Metot.h"

struct EMIR{//emir yapisi ile dosyadan parcaladigim verileri bu dizilere kaydedip ustunde islem yapabilirim
	
	Metot super;
	int uzunlukEmir;
	char **id;
	char **sembol;
	char **islem;
	int *adet;
	
	void (*emirVeriParcalaKaydet)(struct EMIR*,char*);
	void (*emirYazdir)(struct EMIR*);
	void (*emirYoket)(struct EMIR*);
	
};
typedef struct EMIR* Emir;

Emir EmirOlustur(int);

void EmirVeriParcalaKaydet(const Emir,char*);
void EmirYazdir(const Emir);
void EmirYoket(Emir);

#endif