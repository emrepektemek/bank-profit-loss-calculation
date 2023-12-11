#include "Portfoy.h"

Portfoy PortfoyOlustur(int uzunluk)
{	
	Portfoy this;
	
	this=(Portfoy)malloc(sizeof(struct PORTFOY));
	
	this->super=MetotOlustur();
	
	this->uzunlukPortfoy=uzunluk;
	this->kapasitePortfoy=uzunluk;
	
	this->adet = malloc(sizeof(int)*uzunluk);
	this->maliyet = malloc(sizeof(double)*uzunluk);
	int h;
	int l;
	
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
	
	this->portfoyVeriParcalaKaydet=&PortfoyVeriParcalaKaydet;
	this->portfoyGenislet=&PortfoyGenislet;
	this->portfoyYazdir=&PortfoyYazdir;
	this->portfoyYoket=&PortfoyYoket;
	
	return this;
}

void PortfoyVeriParcalaKaydet(const Portfoy this,char* dosya)
{	
	int ilkIndex=0;
	int ikinciIndex=0;
	
	this->super->removespaces(this->super,dosya);//parametre olarak gelen portfoy.json dosyasindaki verileri icindeki bosluklari sildim
	//printf("%s\n",dosya);
	
	int k;
	int i;
	int j;
	for(k=0;k<this->uzunlukPortfoy;k++){//dosyada bos olmayan satir sayisi kadar donen bir dongu
		ikinciIndex=this->super->length(this->super,dosya);//dosyanin uzunlugunu ikinciIndex icine kaydettim cunku dosyayi parcayip verilere ulasacgim
		//printf("%s\n",dosya);
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
		dosya=this->super->substring(this->super,dosya,ilkIndex+1,ikinciIndex);
		//printf("%s\n",dosya);
		
		ilkIndex=this->super->indexOf(this->super,dosya,',');
		kayit=this->super->substring(this->super,dosya,0,ilkIndex);
		//printf("%s\n",kayit);

		this->maliyet[k] = this->super->toDouble(this->super,kayit);
		
		//printf("maliyet :%f\n",this->maliyet[k]);
		
		//printf("%s\n",dosya);
		
		ilkIndex=this->super->indexOf(this->super,dosya,':');
		ikinciIndex=this->super->length(this->super,dosya);
		dosya=this->super->substring(this->super,dosya,ilkIndex+1,ikinciIndex);
		//printf("%s\n",dosya);
		
		ilkIndex=this->super->indexOf(this->super,dosya,'}');
		
		kayit=this->super->substring(this->super,dosya,0,ilkIndex);
		//printf("%s\n",kayit);
		
		this->adet[k] = atoi(kayit);
		//printf("adet :%d\n",this->adet[k]); 
		
		ikinciIndex=this->super->length(this->super,dosya);
		
		dosya=this->super->substring(this->super,dosya,ilkIndex+2,ikinciIndex);
		
		//printf("%s\n",dosya);
				
		free(kayit);
	}	
	
}

void PortfoyGenislet(const Portfoy this){//diziyi genisletip eski verileri yeni diziye aktaracagim bunu portfoyda bulunmayan ama emirlerde satin alinan hisse icin yapiyorum
			this->kapasitePortfoy=this->uzunlukPortfoy*2;
			//printf("\n%d\n",this->kapasitePortfoy);
			char **id2;
			char **sembol2;
			double *maliyet2;
			int *adet2;
			int h;
			int l;
			
			adet2 = malloc(sizeof(int)*this->kapasitePortfoy);
			maliyet2 = malloc(sizeof(double)*this->kapasitePortfoy);
			
			id2 = malloc(sizeof(char*)*this->kapasitePortfoy);
			for(h=0;h<this->kapasitePortfoy;h++)
			{
				id2[h] = malloc(sizeof(char)*30);
			}
	
			sembol2=malloc(sizeof(char*)*this->kapasitePortfoy);
			for(h=0;h<this->kapasitePortfoy;h++)
			{
				sembol2[h] = malloc(sizeof(char)*15);
			}
			
			//burada eski dizinin verilerini yeni dizilere aktardim
			//printf("\n%d\n",this->uzunlukPortfoy);
			
			for(h=0;h<this->uzunlukPortfoy;h++){//bu dogru
				adet2[h]=this->adet[h];
			}
			
			for(l=0;l<this->uzunlukPortfoy;l++){//bu da dogru
				maliyet2[l]=this->maliyet[l];
			}
			
			for(h=0;h<this->uzunlukPortfoy;h++){	//bu dogru 2 boyutlu diziyi olustururken yanlis olusturmusum
				for(l=0;l<30;l++){
					id2[h][l]=this->id[h][l];
				}
			}
			
			
			for(h=0;h<this->uzunlukPortfoy;h++){	
				for(l=0;l<15;l++){
					sembol2[h][l]=this->sembol[h][l];
				}
			}
			
			//eski dizileri serbest biraktim
			free(this->id);
			free(this->sembol);
			free(this->adet);
			free(this->maliyet);
		
			//yeni dizileri gosterttim
			this->id=id2;
			this->sembol=sembol2;
			this->maliyet=maliyet2;
			this->adet=adet2;	
}

void PortfoyYazdir(const Portfoy this)
{
	//printf("Portfoy");
	//printf("\n"); 
	int g;
	for(g=0;g<this->uzunlukPortfoy;g++){
		if(this->adet[g]>0){
			printf("------------------------------\n");
			//printf("\nId :%s\n",this->id[g]);
			printf("Sembol :%s\n",this->sembol[g]);
			printf("Adet :%d\n",this->adet[g]); 
			printf("Maliyet :%f TL\n",this->maliyet[g]);
		}	
	}
}

void PortfoyYoket(Portfoy this)
{
	if(this==NULL) return;
	
	this->super->metotYoket(this->super);
	
	free(this->id);
	free(this->sembol);
	free(this->maliyet);
	free(this->adet);
	free(this);
}
