#include "Hisse.h"

Hisse HisseOlustur(int uzunluk)
{
	Hisse this;
	
	this = (Hisse)malloc(sizeof(struct HISSE));
	
	this->super=MetotOlustur();
	
	this->uzunlukHisse=uzunluk;
	
	this->fiyat = malloc(sizeof(double)*uzunluk);
	
	int h;
	this->ad = malloc(sizeof(char*)*uzunluk);
	for(h=0;h<uzunluk;h++)
	{
		this->ad[h] = malloc(sizeof(char)*30);
	}
	
	this->id = malloc(sizeof(char*)*uzunluk);
	for(h=0;h<uzunluk;h++)
	{
		this->id[h] = malloc(sizeof(char)*30);
	}
	
	this->sembol=malloc(sizeof(char*)*uzunluk);
	for(h=0;h<uzunluk;h++)
	{
		this->sembol[h]=malloc(sizeof(char)*15);
	}
	
	
	this->hisseVeriParcalaKaydet=&HisseVeriParcalaKaydet;
	this->hisseYazdir=&HisseYazdir;
	this->hisseYoket=&HisseYoket;
	return this;
}

void HisseVeriParcalaKaydet(const Hisse this,char* dosya)
{	
	int ilkIndex=0;
	int ikinciIndex=0;
	
	this->super->removespaces(this->super,dosya);
	//printf("%s\n",dosya);
	
	int k;
	int i;
	int j;
	for(k=0;k<this->uzunlukHisse;k++){//dosyada bos olmayan satir sayisi kadar donen bir dongu
	
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
			this->ad[k][j]=kayit[j];			
		}	
		
		for(j=donusMiktari;j<30;j++){
			this->ad[k][j]='\0';
		}
	
		//printf("ad :%s\n",this->ad[k]);	
		
		ilkIndex=this->super->indexOf(this->super,dosya,':');
		
		dosya=this->super->substring(this->super,dosya,ilkIndex+1,ikinciIndex);
		//printf("%s\n",dosya);
		
		ilkIndex=this->super->indexOf(this->super,dosya,'}');
		kayit=this->super->substring(this->super,dosya,0,ilkIndex);
		//printf("%s\n",kayit);

		this->fiyat[k] = this->super->toDouble(this->super,kayit);
		
		//printf("fiyat :%f\n",this->fiyat[k]);
		
		//printf("%s\n",dosya);
		
		ikinciIndex=this->super->length(this->super,dosya);
		dosya=this->super->substring(this->super,dosya,ilkIndex+2,ikinciIndex);
		//printf("%s\n",dosya);
		free(kayit);
	}		
}

void HisseYazdir(const Hisse this)
{
	printf("Hisseler");
	printf("\n"); 
	int g;
	for(g=0;g<this->uzunlukHisse;g++){
		printf("------------------------------"); 
		printf("\nId :%s\n",this->id[g]);
		printf("Sembol :%s\n",this->sembol[g]);
		printf("ad :%s\n",this->ad[g]);
		printf("fiyat :%f\n",this->fiyat[g]); 
	}
}

void HisseYoket(Hisse this)
{
	if(this==NULL) return;
	this->super->metotYoket(this->super);
	free(this->id);
	free(this->sembol);
	free(this->ad);
	free(this->fiyat);
	free(this);
}
