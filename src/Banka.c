#include <math.h>

#include "Banka.h"

Banka BankaOlustur(int uzunlukPortfoy,int uzunlukHisse,int uzunlukEmir,int uzunlukBanka)
{
	Banka this;
	this = (Banka)malloc(sizeof(struct BANKA));
	
	this->super=EmirOlustur(uzunlukEmir);
	this->super2=HisseOlustur(uzunlukHisse);
	this->super3=PortfoyOlustur(uzunlukPortfoy);
	
	this->uzunlukBanka=uzunlukBanka;
	
	this->satisIndex=0;
		
	int h;
	
	this->sembolSatis=malloc(sizeof(char*)*uzunlukBanka);
	for(h=0;h<uzunlukBanka;h++){
		this->sembolSatis[h] = malloc(sizeof(char)*15);
	}
	
	this->satisUcret=malloc(sizeof(double)*uzunlukBanka);
	this->satisMaliyet=malloc(sizeof(double)*uzunlukBanka);
	
	this->verileriKaydetPortfoy=&VerileriKaydetPortfoy;
	this->verileriKaydetHisse=&VerileriKaydetHisse;
	this->verileriKaydetEmir=&VerileriKaydetEmir;
	this->hesapla=&Hesapla;
	this->portfoyIndexBul=&PortfoyIndexBul;
	this->hisseIndexBul=&HisseIndexBul;
	
	this->yazdir=&Yazdir;
	this->yoket=&Yoket;
	
	return this;
}

void VerileriKaydetPortfoy(const Banka this,char* dosya)
{
	this->super3->portfoyVeriParcalaKaydet(this->super3,dosya);
}

void VerileriKaydetHisse(const Banka this,char* dosya)
{
	this->super2->hisseVeriParcalaKaydet(this->super2,dosya);
}

void VerileriKaydetEmir(const Banka this,char* dosya)
{
	this->super->emirVeriParcalaKaydet(this->super,dosya);
}

void Hesapla(const Banka this)
{
	int s;
	
	char *sembol = malloc(sizeof(char)*15);
	char *islem = malloc(sizeof(char)*10);
	int adet;
	
	int portfoyIndex;
	int hisseIndex;
	
	int yeniAdet;
	double alisFiyat;
	double yeniMaliyet;
	
	for(s=0;s<this->uzunlukBanka;s++){//uzunlukBanka aslinda emirler dosyasindaki verilerin sayisi kadardir cunku emirleri gerceklestirecegim icin emirlerin verisi kadar donen bir dongu ile gerekli alis satis islemleri yapiyorum
	
		memset(sembol,0,strlen(sembol));//hata olmamasi icin dizinin icini temizledim
		memset(islem,0,strlen(islem));
		//emirlerdeki verileri buradaki degiskenlerin icine attim kontrol yaparken kolayca yapabileyim diye
		strcpy(sembol, this->super->sembol[s]);
		strcpy(islem, this->super->islem[s]);
		adet=this->super->adet[s];
			
		portfoyIndex=this->portfoyIndexBul(this,sembol);//-1 donerse demek ki portfoyda boyle bir sembol yokmus 
		hisseIndex=this->hisseIndexBul(this,sembol);//-1 donerse demek ki hisselerde boyle bir sembol yokmus
		
		//super=Emir  super2=Hisse super3=Portfoy
		if(hisseIndex==-1){
			printf("\nBankamizda Kayitli (%s) Isimli Bir Hisse Yoktur Bu Hisse Icin Islem Gerceklestirilememistir\n",sembol);
		}
		
		if(portfoyIndex!=-1&&hisseIndex!=-1){//emirlerdeki sembol hisse ve portfoyda bulunuyorsa artik islem yapabiliriz yani satis ve alis islemleri
			if(strcmp(islem,"SATIS")==0){//satis islemi 
				if(adet>this->super3->adet[portfoyIndex]&&this->super3->adet[portfoyIndex]>0){//ilk olarak emirlerdeki adet portfodaki adetten fazla ise satma islemini portfoydaki adet sayisina gore yapilir
					printf("\nEmirlerdeki Adet Sayisi Portfoydaki Adet Sayisindan Fazladir Bu Yuzden Portfoyunuzdaki (%s) \nIcin Emirlerdeki %d Adet Yerine Portfoydaki %d Adet Kadar Hisseniz Satilmistir\n\n",sembol,adet,this->super3->adet[portfoyIndex]);
					strcpy(this->sembolSatis[this->satisIndex],sembol);
					this->satisUcret[this->satisIndex]=this->super2->fiyat[hisseIndex]*this->super3->adet[portfoyIndex];
					this->satisMaliyet[this->satisIndex]=this->super3->maliyet[portfoyIndex]*this->super3->adet[portfoyIndex];
					this->super3->adet[portfoyIndex]=0;//portfodaki adet guncellendi
					this->satisIndex++;
				}
				if(adet<=this->super3->adet[portfoyIndex]&&this->super3->adet[portfoyIndex]>0){//emirlerdeki adet sayisi portfoydaki adet sayinsindan kucuk veye esit olabilir o zaman ona gore kar zarar hesabi yapilir
					strcpy(this->sembolSatis[this->satisIndex],sembol);
					this->satisUcret[this->satisIndex]=this->super2->fiyat[hisseIndex]*adet;
					this->satisMaliyet[this->satisIndex]=this->super3->maliyet[portfoyIndex]*adet;
					this->super3->adet[portfoyIndex]=this->super3->adet[portfoyIndex]-adet;//portfodaki adet guncellendi
					this->satisIndex++;
				}
			}
			else if(strcmp(islem,"ALIS")==0){//alis icin islem
				alisFiyat=adet*this->super2->fiyat[hisseIndex];
				yeniAdet=adet+this->super3->adet[portfoyIndex];
				yeniMaliyet=(alisFiyat+(this->super3->maliyet[portfoyIndex]*this->super3->adet[portfoyIndex]))/yeniAdet;
				//yeni maliyeti ve adeti portfoya kaydet
				this->super3->maliyet[portfoyIndex]=yeniMaliyet;
				this->super3->adet[portfoyIndex]=yeniAdet;	
			}
		}
		//eger yukaridaki iflere girmezse  asagidaki iflere kesin girer
		if(portfoyIndex==-1&&hisseIndex!=-1&&strcmp(islem,"ALIS")==0)//satis isleminde hisse portfoyda zaten bulunur fakat alis isleminde alinacak hisse emirlerde bulunabilirken portfoyda bulunmayabilir onun kontrolunu burada yapacagim
		{
			char *id = malloc(sizeof(char)*30);
			memset(id,0,strlen(id));
			strcpy(id,this->super->id[s]);
			double maliyet=this->super2->fiyat[hisseIndex];
			//burada portfoydaki dizileri genisletip emirlerdeki almis oldugum hisseyi portfoya kaydetmem gerekiyor cunku portfoy dizilerini portfoy dosyasindaki verilerin bulunduğu satir sayisi kadar olusturdum fakat emirlerden yeni hisse alinirsa portfoya kaydetmek icin portfoyun dizilerinin boyutunu arttirmaliyim
			if(this->super3->uzunlukPortfoy==this->super3->kapasitePortfoy){//dizinin uzunlugu dizinin kapasitesine esit oldugunda artik eski dizilerin verilerini yeni genislettigim diziye kaydedip yeni dizi ile islem yapacagim
				this->super3->portfoyGenislet(this->super3);
			}
			this->super3->uzunlukPortfoy++;//dizinin uzungulunu arttirip islem yapmam gerekiyor
			this->super3->adet[this->super3->uzunlukPortfoy-1]=adet;
			strcpy(this->super3->sembol[this->super3->uzunlukPortfoy-1],sembol);
			strcpy(this->super3->id[this->super3->uzunlukPortfoy-1],id);
			this->super3->maliyet[this->super3->uzunlukPortfoy-1]=maliyet;
		
			free(id);
		}
		
		if(portfoyIndex==-1&&hisseIndex!=-1&&strcmp(islem,"SATIS")==0){//emirlerde satis islemi olan hisse portfoyda yoksa ama hisselerde varsa o zaman islem gerceklestirilemeyecek bunu ekrana yazdirarak belirttim
			printf("\nEmirlerdeki Satmak Istediginiz (%s) Adli Hisse Portfoyunuzda Bulunmadigi Icin Satma Isleminiz Gerceklesememistir\n",sembol);
		}			
	}	
	free(sembol);
	free(islem);
}

int PortfoyIndexBul(const Banka this,char *sembol){
	int e;
	int varMi;
	for(e=0;e<this->super3->uzunlukPortfoy;e++)
	{
		varMi=strcmp(sembol,this->super3->sembol[e]);
		if(varMi==0) return e;
	}
	return -1;
}

int HisseIndexBul(const Banka this,char *sembol){
	int f;
	int varMi;
	for(f=0;f<this->super2->uzunlukHisse;f++){
		varMi=strcmp(sembol,this->super2->sembol[f]);
		if(varMi==0) return f;
	}
	return -1;
}

void Yazdir(const Banka this){
	printf("\n\n");
	double toplamkarzarar=0;
	int a;
	int b;
	double karzarar;
	for(a=0;a<this->satisIndex;a++){
		printf("%s",this->sembolSatis[a]);
		printf(" icin kar/zarar hesabi\n");
		printf("---------------------------\n");
		printf("Satis Ucreti :%f TL\n",this->satisUcret[a]);
		printf("Maliyet :%f TL\n",this->satisMaliyet[a]);
		karzarar=(this->satisUcret[a])-(this->satisMaliyet[a]);
		toplamkarzarar=toplamkarzarar+karzarar;
		if(karzarar>0) printf("%s satisindan %f TL kar yapilmistir\n\n",this->sembolSatis[a],fabs(karzarar));
		if(karzarar==0) printf("%s satisindan ne kar ne zarar yapilmistir\n\n",this->sembolSatis[a]);
		if(karzarar<0) printf("%s satisindan %f TL zarar yapilmistir\n\n",this->sembolSatis[a],fabs(karzarar));
	}
	printf("\nToplam Kar/Zarar :");
	if(toplamkarzarar<0) printf(" - %f TL\n\n",fabs(toplamkarzarar));
	if(toplamkarzarar>0) printf(" + %f TL\n\n",fabs(toplamkarzarar));
	
	printf("\nGuncel Portfoy\n");
	this->super3->portfoyYazdir(this->super3);
	
	 //bunlara gelerek olmadigindan kapattim tum verileri ekrana yazdirmak icin bunu kullanabilirsiniz ama portfoyda idyi yazdirmadim onu da portfoy.c nin portfoyYazdir metotundan acabilirsiniz
	/*printf("\n\n");
	this->super->emirYazdir(this->super);
	printf("\n\n");
	this->super2->hisseYazdir(this->super2);
	*/
}


void Yoket(Banka this)//tum olusturulan nesneleri yok ettim
{
	if(this==NULL) return;
	
	this->super->emirYoket(this->super);
	this->super2->hisseYoket(this->super2);
	this->super3->portfoyYoket(this->super3);
	
	free(this->sembolSatis);
	free(this->satisUcret);
	free(this->satisMaliyet);
	
	free(this);
}
