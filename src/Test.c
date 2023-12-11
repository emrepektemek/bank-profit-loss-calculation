#include<locale.h> 

#include "Banka.h"

int main()
{
	setlocale(LC_ALL, "Turkish"); 
	
	FILE * dosyaOku;
	int result;
	char *okunan=malloc(450*sizeof(char));
	
	int kontrol=0;
	int oncekiBoslukHisse=0;
	int oncekiBoslukEmir=0;
	int oncekiBoslukPortfoy=0;
	
	int portfoySatirSayisi=0;//bos olmayan satirlarin sayisi
	
	dosyaOku=fopen("./doc/portfoy.json","r");
	memset(okunan,0,strlen(okunan));
	while(!feof(dosyaOku))//bosluksuz satir sayisini bulduk
	{
		fgets(okunan,450,dosyaOku);
		result=isspace(okunan[0]);
	    if(result==0)
		{	
			portfoySatirSayisi++;
			kontrol=1;
		}
		if(kontrol==0){
			oncekiBoslukPortfoy++;
		}
	}
	
	fclose(dosyaOku);
	
	int emirSatirSayisi=0;//NULL olmayan satirlarin sayisi
	kontrol=0;
	dosyaOku=fopen("./doc/emirler.json","r");
	memset(okunan,0,strlen(okunan));
	while(!feof(dosyaOku))//bosluksuz satir sayisini bulduk
	{
		fgets(okunan,450,dosyaOku);
		result=isspace(okunan[0]);
	    if(result==0)
		{	
			emirSatirSayisi++;
			kontrol=1;
		}
		if(kontrol==0){
			oncekiBoslukEmir++;
		}
	}

	fclose(dosyaOku);
	
	int hisseSatirSayisi=0;
	
	dosyaOku=fopen("./doc/hisseler.json","r");
	
	kontrol=0;
	memset(okunan,0,strlen(okunan));
	while(!feof(dosyaOku))//bosluksuz satir sayisini bulduk
	{
		fgets(okunan,450,dosyaOku);
		result=isspace(okunan[0]);
	    if(result==0)
		{	
			hisseSatirSayisi++;
			kontrol=1;
		}
		if(kontrol==0){
			oncekiBoslukHisse++;
		}
	}
	fclose(dosyaOku);
	
	free(okunan);
	
	//printf("emirler satir sayisi : %d\n",emirSatirSayisi);
	
	//printf("portfoy satir sayisi : %d\n",portfoySatirSayisi);
	
	//printf("hisseler satir sayisi : %d\n",hisselerSatirSayisi);
	
	
	Banka banka = BankaOlustur(portfoySatirSayisi-2,hisseSatirSayisi-2,emirSatirSayisi-2,emirSatirSayisi-2);
	int i;

	char *veriler = malloc(sizeof(char)*70000);
	char *veriler2 = malloc(sizeof(char)*70000);
	char *veriler3 = malloc(sizeof(char)*70000);
	char *kaydet=malloc(450*sizeof(char));
	char *kaydet2=malloc(450*sizeof(char));
	char *kaydet3=malloc(450*sizeof(char));
	
	//hata olmamasi icin bu dizilerin icini temizledim veriler icin hata olmaz cunku parcalama isleminden dolayi belirli bir algoritmasi var
	memset(kaydet,0,strlen(kaydet));
	memset(kaydet2,0,strlen(kaydet2));
	memset(kaydet3,0,strlen(kaydet3));
	
	dosyaOku=fopen("./doc/portfoy.json","r");
	for(i=0;i<portfoySatirSayisi+oncekiBoslukPortfoy;i++)//bosluksuz satirlari bir stringe atadim
	{
		fgets(kaydet,450,dosyaOku);
		if(i>oncekiBoslukPortfoy&&i<portfoySatirSayisi+oncekiBoslukPortfoy-1)
		{
			veriler=strcat(veriler,kaydet);
		}	
	}
	fclose(dosyaOku);
	
	banka->verileriKaydetPortfoy(banka,veriler);
	
	free(veriler);
	free(kaydet);
	
	//rewind(dosyaOku);
	
	dosyaOku=fopen("./doc/hisseler.json","r");
	for(i=0;i<hisseSatirSayisi+oncekiBoslukHisse;i++)//bosluksuz satirlari bir stringe atadim
	{
		fgets(kaydet2,450,dosyaOku);
		if(i>oncekiBoslukHisse&&i<hisseSatirSayisi+oncekiBoslukHisse-1)
		{		
			veriler2=strcat(veriler2,kaydet2);	
		}
		
	}
	fclose(dosyaOku);
	
	banka->verileriKaydetHisse(banka,veriler2);
	
	free(veriler2);
	free(kaydet2);
	
	dosyaOku=fopen("./doc/emirler.json","r");
	for(i=0;i<emirSatirSayisi+oncekiBoslukEmir;i++)//bosluksuz satirlari bir stringe atadim
	{
		fgets(kaydet3,450,dosyaOku);
		if(i>oncekiBoslukEmir&&i<emirSatirSayisi+oncekiBoslukEmir-1)
		{		
			veriler3=strcat(veriler3,kaydet3);	
		}
		
	}
	fclose(dosyaOku);
	
	banka->verileriKaydetEmir(banka,veriler3);
	
	free(veriler3);
	free(kaydet3);
	
	
	banka->hesapla(banka);
	
	banka->yazdir(banka);
	
	banka->yoket(banka);

	return 0;
	
}