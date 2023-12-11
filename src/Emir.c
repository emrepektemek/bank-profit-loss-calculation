#include "Emir.h"

Emir EmirOlustur(int uzunlukEmir)
{
	Emir this;
	this = (Emir)malloc(sizeof(struct EMIR));
	
	this->super=MetotOlustur();
	
	this->uzunlukEmir=uzunlukEmir;
	
	this->adet = malloc(sizeof(int)*uzunlukEmir);
	
	int h;
	this->id = malloc(sizeof(char*)*uzunlukEmir);
	for(h=0;h<uzunlukEmir;h++)
	{
		this->id[h] = malloc(sizeof(char)*30);
	}
	
	this->sembol=malloc(sizeof(char*)*uzunlukEmir);
	for(h=0;h<uzunlukEmir;h++)
	{
		this->sembol[h]=malloc(sizeof(char)*15);
	}
	
	this->islem=malloc(sizeof(char*)*uzunlukEmir);
	for(h=0;h<uzunlukEmir;h++)
	{
		this->islem[h]=malloc(sizeof(char)*10);
	}
	
	this->emirVeriParcalaKaydet=&EmirVeriParcalaKaydet;
	this->emirYazdir=&EmirYazdir;
	this->emirYoket=&EmirYoket;
	
	return this;
}

void EmirVeriParcalaKaydet(const Emir this,char* dosya)
{
	//printf("%s\n",dosya);
	
	int ilkIndex=0;
	int ikinciIndex=0;
	
	this->super->removespaces(this->super,dosya);
	//printf("%s\n",dosya);
	
	int k=0;
	int i;
	int j;
	for(k=0;k<this->uzunlukEmir;k++){//dosyada bos olmayan satir sayisi kadar donen bir dongu
	
		ikinciIndex=this->super->length(this->super,dosya);//dosyanin uzunlugunu ikinciIndex icine kaydettim cunku dosyayi parcayip verilere ulasacgim
		
		char *kayit = malloc(30*sizeof(char));
		
		ilkIndex=this->super->indexOf(this->super,dosya,':');
		dosya=this->super->substring(this->super,dosya,ilkIndex+2,ikinciIndex);
		//printf("%s\n",dosya);
		
		ilkIndex=this->super->indexOf(this->super,dosya,'"');
		kayit=this->super->substring(this->super,dosya,0,ilkIndex);
		
		//printf("%s\n",kayit);
		
		int donusMiktari=this->super->length(this->super,kayit);
		
		for(j=0;j<donusMiktari;j++){
			this->id[k][j]=kayit[j];			
		}
		
		for(j=donusMiktari;j<30;j++){
			this->id[k][j]='\0';
		}
		
		//printf("id :%s\n",this->id[k]);
		
		ilkIndex=this->super->indexOf(this->super,dosya,':');
		ikinciIndex=this->super->length(this->super,dosya);
		dosya=this->super->substring(this->super,dosya,ilkIndex+2,ikinciIndex);
		//printf("%s\n",dosya);
		
		ilkIndex=this->super->indexOf(this->super,dosya,'"');
		ikinciIndex=this->super->length(this->super,dosya);
		kayit=this->super->substring(this->super,dosya,0,ilkIndex);
		
		//printf("%s\n",kayit);
		
		donusMiktari=this->super->length(this->super,kayit);
		
		for(j=0;j<donusMiktari;j++){
			this->sembol[k][j]=kayit[j];			
		}	
		
		for(j=donusMiktari;j<15;j++){
			this->sembol[k][j]='\0';
		}
	
		//printf("sembol :%s\n",this->sembol[k]);	
		
		
		ilkIndex=this->super->indexOf(this->super,dosya,':');
		dosya=this->super->substring(this->super,dosya,ilkIndex+2,ikinciIndex);
		//printf("%s\n",dosya);
		
		
		ilkIndex=this->super->indexOf(this->super,dosya,'"');
		ikinciIndex=this->super->length(this->super,dosya);
		kayit=this->super->substring(this->super,dosya,0,ilkIndex);
		
		//printf("%s\n",kayit);
		
		donusMiktari=this->super->length(this->super,kayit);
		
		for(j=0;j<donusMiktari;j++){
			this->islem[k][j]=kayit[j];			
		}	
		
		for(j=donusMiktari;j<10;j++){
			this->islem[k][j]='\0';
		}
	
		//printf("islem :%s\n",this->islem[k]);	
		
		ilkIndex=this->super->indexOf(this->super,dosya,':');
		
		dosya=this->super->substring(this->super,dosya,ilkIndex+1,ikinciIndex);
		//printf("%s\n",dosya);
		
		ilkIndex=this->super->indexOf(this->super,dosya,'}');
		kayit=this->super->substring(this->super,dosya,0,ilkIndex);
		//printf("%s\n",kayit);
		
		this->adet[k] = atoi(kayit);
		
		//printf("adet :%d\n",this->adet[k]);
		
		//printf("%s\n",dosya);
		
		ikinciIndex=this->super->length(this->super,dosya);
		dosya=this->super->substring(this->super,dosya,ilkIndex+2,ikinciIndex);
		//printf("%s\n",dosya);
		free(kayit);
	}		
	
}

void EmirYazdir(const Emir this){
	printf("Emirler");
	printf("\n"); 
	int g;
	for(g=0;g<this->uzunlukEmir;g++){
		printf("------------------------------"); 
		printf("\nId :%s\n",this->id[g]);
		printf("Sembol :%s\n",this->sembol[g]);
		printf("Islem :%s\n",this->islem[g]);
		printf("Adet :%d\n",this->adet[g]); 
	}
}

void EmirYoket(Emir this)
{
	if(this==NULL) return;
	this->super->metotYoket(this->super);
	free(this->id);
	free(this->adet);
	free(this->sembol);
	free(this->islem);
	free(this);
}
