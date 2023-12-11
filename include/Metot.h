#ifndef METOT_H
#define METOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct METOT{//dosya parcalamamda bana yardimci olacak metotlar
	
	char* (*substring)(struct METOT*,char*,int,int);
	int (*indexOf)(struct METOT*,char*,char);
	int (*length)(struct METOT*,char[]);
	void (*removespaces)(struct METOT*,char*);
	double (*toDouble)(struct METOT*,char[]);	
	void (*metotYoket)(struct METOT*);
};
typedef struct METOT* Metot;

Metot MetotOlustur();
char* Substring(const Metot,char*,int,int);
int Indexof(const Metot,char*,char);
int Length(const Metot,char[]);
void Removespaces(const Metot,char*);
double ToDouble(const Metot,char[]);
void MetotYoket(Metot);

#endif