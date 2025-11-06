#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
int kullanicino,sifre,bakiye;
int adminno,adminSifre,adminSecim;
int silinecekNo;
int secim;
int yeniKullanicino;
int yeniKullanicisifre;
char cAdi[50];
int a=0;
int g=0;
int k=0;
int f=0;
int y=0;
int p=0;
int yeniPersonelno,yeniPersonelsifre;
int kayitSayisi;
int girisSecim;
int miktar;
int denetim;
int sirketBakiyesi;
int gunlukLimit;
int aktarimMiktar;
int perMiktar;
bool bitme;
int eklenecekSecim;
int cikarilacakSecim;
int odemeKismi;
/*
-- DENEME KULLANICILAR --
ADMIN
Kullanici No: 1111 Sifre: 9999

MUHASEBE CALISANLAR
Kullanıcı No: 1169 Sifre: 8520 

PERSONEL
Kullanıcı No: 1111 Sifre: 1234 
*/
int admingiris(int adminno,int adminSifre){
    FILE *administrator;
    int yetkiliNo;
    int yetkiliSifre;
    administrator=fopen("administrator.txt","r");
    while(fscanf(administrator,"%d %d",&yetkiliNo,&yetkiliSifre)==2){
        if(yetkiliNo == adminno && yetkiliSifre == adminSifre){
            fclose(administrator);
            return 1;
        }
    }
    fclose(administrator);
    return 0;
}
int giris(int kullanicino,int sifre,int girisSecim){
    FILE *kullanici,*personel;
    int kayitlikullanici;
    int kayitlisifre;
    int kayitliPersonel;
    int personelSifre;
        switch(girisSecim){
    case 2:
            kullanici=fopen("kullanici.txt","r");
            while(fscanf(kullanici,"%d %d %*s",&kayitlikullanici,&kayitlisifre)==2){
                if(kayitlikullanici == kullanicino && kayitlisifre == sifre){
                fclose(kullanici);            
                return 1;
            }
        }
        fclose(kullanici);
        return 0;
    case 3:

            personel=fopen("personel.txt","r");
            while(fscanf(personel,"%d %d %*s",&kayitliPersonel,&personelSifre)==2){
                if(kayitliPersonel == kullanicino && personelSifre== sifre){
                    fclose(personel);
                    return 1;
                }
            }
            fclose(personel);
            return 0;
        }
    }
int yeniKullanici(int yenikullanicino,int yenikullanicisifre,const char *cAdi,int eklenecekSecim){
    FILE *kullanici,*personel;
    int kayitlikullanici;
    int kayitlisifre;
    char CalisanAd[50];
    switch(eklenecekSecim){
case 1:
    kullanici=fopen("kullanici.txt","a+");
//    rewind(kullanici);
    while(fscanf(kullanici,"%d %d %s",&kayitlikullanici,&kayitlisifre,CalisanAd)!=EOF){
        if(yenikullanicino==kayitlikullanici){
            fclose(kullanici);
            return 0;
        }
    }
    fprintf(kullanici,"%d %d %s\n",yenikullanicino,yenikullanicisifre,cAdi);
    fclose(kullanici);
    return 1;

case 2:
    personel=fopen("personel.txt","a+");
//    rewind(kullanici);
    while(fscanf(personel,"%d %d %s",&kayitlikullanici,&kayitlisifre,CalisanAd)!=EOF){
        if(yenikullanicino==kayitlikullanici){
            fclose(personel);
            return 0;
        }
    }
    fprintf(personel,"%d %d %s\n",yenikullanicino,yenikullanicisifre,cAdi);
    fclose(personel);
    return 1;
}
    return 0;
    }


int kullaniciSil(int silinecekNo,int cikarilacakSecim){
    FILE *kopya, *kullanici, *personel, *istenCikarilanlar;
    int noAlma,sifreAlma;
    char adiAlma[50];
    kopya=fopen("tmp.txt","w+");
    switch(cikarilacakSecim){
case 1:
    kullanici=fopen("kullanici.txt","r+");
    while(fscanf(kullanici,"%d %d %s",&noAlma,&sifreAlma,adiAlma)!=EOF){
        if(noAlma!=silinecekNo){
          fprintf(kopya,"%d %d %s\n",noAlma,sifreAlma,adiAlma);
        }
        else{
            p++;
            istenCikarilanlar=fopen("istenCikarilanlar.txt","a+");
            fprintf(istenCikarilanlar,"\n%d %d %s",noAlma,sifreAlma,adiAlma);
            fclose(istenCikarilanlar);
        }
    }
    fclose(kopya);
    fclose(kullanici);
    remove("kullanici.txt");
    rename("tmp.txt","kullanici.txt");
    if(p==0){
        system("cls");
        printf("%d nolu bir calisan yok\n",silinecekNo);
        return 0;
    }
    p=0;
    return 1;/*basarili*/
case 2:
    personel=fopen("personel.txt","r+");
    while(fscanf(personel,"%d %d %s",&noAlma,&sifreAlma,adiAlma)!=EOF){
        if(noAlma!=silinecekNo){
          fprintf(kopya,"%d %d %s\n",noAlma,sifreAlma,adiAlma);
        }
        else{
            p++;
            istenCikarilanlar=fopen("istenCikarilanlar.txt","a+");
            fprintf(istenCikarilanlar,"\n%d %d %s",noAlma,sifreAlma,adiAlma);
            fclose(istenCikarilanlar);
        }
    }
    fclose(kopya);
    fclose(personel);
    remove("personel.txt");
    rename("tmp.txt","personel.txt");
    if(p==0){
        system("cls");
        printf("%d nolu bir calisan yok\n",silinecekNo);
        return 0;
    }
    p=0;
    return 1;/*basarili*/
}

}

int bilgi(int kullanicino){
    FILE *bakiyesi;
    int bakiye;
    int kullaniciKontrol;
    bakiyesi=fopen("bakiyesi.txt","r+");
    while(fscanf(bakiyesi,"%d %d",&kullaniciKontrol,&bakiye)==2){
        if(kullanicino==kullaniciKontrol){
            fclose(bakiyesi);
            return bakiye;
        }
    }
    fclose(bakiyesi);
    return 0;
}

int paraYukle(int miktar, int kullanicino, int sirketBakiyesi,int odemeKismi) {
    FILE *bakiyesi, *sirketBakiye, *tempBakiye;
    sirketBakiye = fopen("sirketBakiye.txt", "r+");
    int kullaniciKontrol;
    int kullaniciBakiye;
    int miktarKopya = miktar;

    bakiyesi = fopen("bakiyesi.txt", "r+");
    tempBakiye = fopen("bakiyesi_temp.txt", "w");

    while (fscanf(bakiyesi, "%d %d", &kullaniciKontrol, &kullaniciBakiye) == 2) {
        if (kullaniciKontrol == kullanicino) {
            miktar += kullaniciBakiye;
            fprintf(tempBakiye, "%d %d\n", kullanicino, miktar);

            sirketBakiyesi -= miktarKopya;
            fseek(sirketBakiye, -1 * sizeof(int), SEEK_CUR);
            fprintf(sirketBakiye, "%d", sirketBakiyesi);
            fclose(sirketBakiye);
        } else {
            fprintf(tempBakiye, "%d %d\n", kullaniciKontrol, kullaniciBakiye);
        }
    }
    fclose(bakiyesi);
    fclose(tempBakiye);
    remove("bakiyesi.txt");
    rename("bakiyesi_temp.txt", "bakiyesi.txt");
    return sirketBakiyesi;
}
int sirketeParaGirisi(int paraGirisMiktari){
FILE *sirketBakiye;
int eskiSirketBakiye;
sirketBakiye=fopen("sirketBakiye.txt","r");
if(sirketBakiye==NULL){
    return 0;
}
fscanf(sirketBakiye,"%d",&eskiSirketBakiye);
fclose(sirketBakiye);
sirketBakiye=fopen("sirketBakiye.txt","w");
paraGirisMiktari+=eskiSirketBakiye;
fprintf(sirketBakiye,"%d",paraGirisMiktari);
fclose(sirketBakiye);
return 1;
}
int sirketBakiyesiGoruntule(){
    FILE *sirketBakiye;
    int bakiyeOku;
    sirketBakiye=fopen("sirketBakiye.txt","r");
    if(sirketBakiye == NULL){
        printf("Dosya Acma hatasi");
        return 0;
    }
    fscanf(sirketBakiye,"%d",&bakiyeOku);
    fclose(sirketBakiye);
    return bakiyeOku;
}

int perBakiyeGoruntule(int kullanicino){
    FILE *bakiyesi;
    int perBakiyeOku;
    int kNo;
    bakiyesi=fopen("bakiyesi.txt","r+");
    while(fscanf(bakiyesi,"%d %d",&kNo,&perBakiyeOku)!=EOF){
        if(kullanicino==kNo){
            fclose(bakiyesi);
            return perBakiyeOku;
        }
    }
    fclose(bakiyesi);
    return 0;
}
int hesabaParaAktarma(int sirketBakiyesi, int aktarimMiktar) {
    FILE *bankaHesabi, *sirketBakiye, *tempFile;
    int kopyadeneme;
    kopyadeneme=aktarimMiktar;
    sirketBakiye = fopen("sirketBakiye.txt", "w");
    int hesapBakiye;
    char hesapNumarasi[6];
    char adminHesapNumara[6];
    bankaHesabi = fopen("bankaHesabi.txt", "r+");
    tempFile = fopen("tempFile.txt", "w");
    printf("Hesap numarasi giriniz: ");
    scanf("%s", adminHesapNumara);
    while (fscanf(bankaHesabi, "%s %d", hesapNumarasi, &hesapBakiye) != EOF) {
        if (strcmp(adminHesapNumara, hesapNumarasi) == 0) {
            hesapBakiye += aktarimMiktar;
        }
        fprintf(tempFile, "%s %d\n", hesapNumarasi, hesapBakiye);
    }
    fclose(bankaHesabi);
    fclose(tempFile);
    remove("bankaHesabi.txt");
    rename("tempFile.txt", "bankaHesabi.txt");
    sirketBakiyesi -= kopyadeneme;
    fseek(sirketBakiye, 0, SEEK_SET);
    fprintf(sirketBakiye, "%d", sirketBakiyesi);
    fclose(sirketBakiye);
    return 1;
}
int personelParaAktarma(int perMiktar, int kullanicino, int bakiye) {
    FILE *bankaHesabi, *tempFile;
    bankaHesabi = fopen("bankaHesabi.txt", "r");
    tempFile = fopen("tempFile.txt", "w");
    int perHesapNumarasi, perBakiye;
    int girHesapNumara;
    printf("Hesap numarasini giriniz: ");
    scanf("%d", &girHesapNumara);
    int t;
    t=0;
    while (fscanf(bankaHesabi, "%d %d", &perHesapNumarasi, &perBakiye) != EOF) {
        if (perHesapNumarasi == girHesapNumara) {
            t++;
            perBakiye += perMiktar;
//            bakiye -= perMiktar;
        }
        fprintf(tempFile, "%d %d\n", perHesapNumarasi, perBakiye);
    }

    fclose(bankaHesabi);
    fclose(tempFile);
    if(t==0){
        system("cls");
        printf("Hesap Numarasi Yanlis\n");
        return 0;
    }
    remove("bankaHesabi.txt");
    rename("tempFile.txt", "bankaHesabi.txt");
    FILE *bakiyeDosyasi = fopen("bakiyesi.txt", "r");
    FILE *tempBakiyeDosyasi = fopen("tempBakiye.txt", "w");
    int kullaniciNo;
    int eskiBakiye;

    while (fscanf(bakiyeDosyasi, "%d %d", &kullaniciNo, &eskiBakiye) != EOF) {
        if (kullaniciNo == kullanicino) {
            eskiBakiye -= perMiktar;
        }
        fprintf(tempBakiyeDosyasi, "%d %d\n", kullaniciNo, eskiBakiye);
    }

    fclose(bakiyeDosyasi);
    fclose(tempBakiyeDosyasi);
    remove("bakiyesi.txt");
    rename("tempBakiye.txt", "bakiyesi.txt");

    return 1;
}

void calisanListeleme(){
FILE *kullanici, *personel;
kullanici=fopen("kullanici.txt","r");
int okucalisan,okusifre;
char adi[10];
printf("MUHASEBE\n");
while(fscanf(kullanici,"%d %d %s",&okucalisan,&okusifre,&adi)!=EOF){
    printf("%d %s\n",okucalisan,adi);
}
fclose(kullanici);
printf("\nPERSONEL\n");
personel=fopen("personel.txt","r");
while(fscanf(personel,"%d %d %s",&okucalisan,&okusifre,&adi)!=EOF){
    printf("%d %s\n",okucalisan,adi);
}
fclose(personel);
}

void eskiCalisanListeleme(){
FILE *istenCikarilanlar;
istenCikarilanlar=fopen("istenCikarilanlar.txt","r");
int okuEskiCalisan,okuexsifre;
char exadi[10];
while(fscanf(istenCikarilanlar,"%d %d %s",&okuEskiCalisan,&okuexsifre,&exadi)!=EOF){
    printf("%d %s\n",okuEskiCalisan,exadi);
}
    fclose(istenCikarilanlar);
}
int main(){
    do{
    printf("------------------------\nYonetici girisi icin 1 \n------------------------\nMuhasebe girisi icin 2\n------------------------\nPersonel girisi icin 3\n\nHatirlatma: Yardim Odemeleri icin Personel kismini kullaniniz\n");
    scanf("%d",&girisSecim);
    switch(girisSecim){
case 1:
    do{
    printf("Admin kullanici no : ");
    scanf("%d",&adminno);
    printf("\nAdmin Parola : ");
    scanf("%d",&adminSifre);
    if(admingiris(adminno,adminSifre)){
        // if(kullanicino==1111&&sifre==9999){
        system("cls");
        printf("*****Giris Basarili***** \n");
        do{
        printf("1-Calisan Ekle \n2-Calisan Cikart \n3-Sirket Bakiye Goruntule \n4-Calisan Listele \n5-Eski Calisanlar \n0-Oturumu sonlandir \n");
        scanf("%d",&secim);
        system("cls");
        switch(secim){
    case 1:
        do{
            printf("1-Muhasebe Calisani \n2-Personel Calisani\n");
            scanf("%d",&eklenecekSecim);
//            if(eklenecekSecim!=1 || eklenecekSecim!=2){
//                system("cls");
//                printf("Gecersiz Secim\n");
//                break;
//            }
            if(eklenecekSecim==1 || eklenecekSecim==2){
            printf("Yeni Kullanici No : ");
            scanf("%d",&yeniKullanicino);
            printf("Parola : ");
            scanf("%d",&yeniKullanicisifre);
            printf("Adi ");
            scanf("%s",cAdi);
            if(yeniKullanici(yeniKullanicino,yeniKullanicisifre,cAdi,eklenecekSecim)){
                system("cls");
                printf("Yeni Kullanici Kaydedildi\n");
                f=0;
            }else{
                printf("!Hata 101!(gecersiz veya kayitli no girdiniz)\n");
                f++;
            }
            }else{
            system("cls"); printf("GECERSIZ SECIM\n");
            }
        }while(f>0);
        break;
    case 2:
            printf("1-Muhasebeden Cikartma\n2-Personelden Cikartma\n");
            scanf("%d",&cikarilacakSecim);
            if(cikarilacakSecim==1 || cikarilacakSecim==2){
            printf("Silinecek Kullanici no :");
            scanf("%d",&silinecekNo);
            if(kullaniciSil(silinecekNo,cikarilacakSecim)){
                system("cls");
                printf("%d Nolu Calisan isten cikarildi\n",silinecekNo);
            }else{
            system("cls");
            printf("Cikartma islemi Basarisiz\n");
            }
            }else{
            system("cls");
            printf("Gecersiz Secim\n");
            break;
            }
    break;
    case 3:
            sirketBakiyesi=sirketBakiyesiGoruntule();
            printf("Sirket Bakiyesi : %d\n",sirketBakiyesi);
            if(sirketBakiyesi<50000) printf("Dikkat Dusuk Bakiye\n");
            printf("1-Hesaba Para Aktar \n2-Sirkete Para Girisi \n3-Ust menuye donme\n");
            int icSecim;
            scanf("%d",&icSecim);
            switch(icSecim){
        case 1:
// gunlukLimit=3;
// if(gunlukLimit>0){
// printf("Gun ici Para cekme Limiti :%d",gunlukLimit);
                do{
                printf("Aktarilacak Miktar :");
                scanf("%d",&aktarimMiktar);
                if(aktarimMiktar<sirketBakiyesi){
                    do{
                    if(hesabaParaAktarma(sirketBakiyesi,aktarimMiktar)){
                        sirketBakiyesi=sirketBakiyesiGoruntule();
                        system("cls");
                        printf("Para Aktarimi Basarili\nKalan Sirket bakiyesi :%d\n",sirketBakiyesi);
                        break;
                    }else{
                        printf("basarisiz\n");
                        bitme=true;
                    }
                    }while(bitme);
                    bitme=false;
                }else{
                system("cls");
                printf("Yetersiz Sirket Bakiyesi\n");
                bitme=true;
                }
                }while(bitme);
            break;
        case 2: printf("Para giris miktari :");
                int paraGirisMiktari;
                scanf("%d",&paraGirisMiktari);
                if(paraGirisMiktari>0 && paraGirisMiktari<10000000){
                if(sirketeParaGirisi(paraGirisMiktari)){
                system("cls");
                printf("Para Girisi basarili\n");

                }else{
                printf("para girisi basarisiz\n");
                }
                }else{
                printf("Lutfen gecerli bir miktar girin\n");
                }
                break;

        case 3: system("cls"); break;

        default: system("cls"); printf("GECERLI SECIMLER YAPMAYA OZEN GOSTERIN\n");
        }//son ekledigim

        break;
    case 4: system("cls");
            calisanListeleme();
            printf("2- ust menu\n");
            scanf("%d",&secim);
            system("cls");
            break;
    case 5: system("cls");
            eskiCalisanListeleme();
            printf("2- ust menu\n");
            scanf("%d",&secim);
            system("cls");
            break;
            }//adminSecim
        }while(secim!=0);
        system("cls");
        printf("***Oturum Sonlandirildi***\n");
        a=0;
        }else{
            system("cls");
            printf("Admin no veya sifre hatali\n");
            a++;

        }
        }while(a>0);
//    }
//    else{
//    printf("Yanlis admin no veya sifre!!!");
//    }
    break;

    case 2:
    do{
    printf("---------------\nCalisan No Giriniz: ");
    scanf("%d",&kullanicino);
    printf("---------------\nSifre giriniz: ");
    scanf("%d",&sifre);
    if(!giris(kullanicino,sifre,girisSecim)){
    system("cls");
    printf("yanlis Calisan adi veya sifre!!!\n");
    g++;
    }else{
    g=0;
    sirketBakiyesi=sirketBakiyesiGoruntule();
    system("cls");
    printf("*******GIRIS BASARILI******");
    do{/* üst menü baslangic*/
    printf("\n Sirket Bakiye :%d\n 1-Odemeler \n 2-Personel ekleme \n 3-Personel cikartma\n 0-Cikis \n ",sirketBakiyesi);
    scanf("%d",&secim);
    switch(secim){

    case 1:
            system("cls");

            printf("1-Maas odemeleri\n2-Ikramiye odemeleri\n3-Yardim odemeleri\n");
            scanf("%d",&secim);
            switch(secim){
                case 1:
                        printf("\nOdenecek Maas Tutari : ");
                        scanf("%d",&miktar);
                        int kopya=sirketBakiyesi;
                        if(miktar<sirketBakiyesi){
                            printf("Maas odenecek personel no : ");
                            scanf("%d",&kullanicino);
                            odemeKismi=1;
                            sirketBakiyesi=paraYukle(miktar,kullanicino,sirketBakiyesi,odemeKismi);
                            if(kopya!=sirketBakiyesi){
                                system("cls");
                            printf("\n%d Nolu Personel maas odemesi basarili\n",kullanicino);
                            break;
                            }else{
                                system("cls");
                            printf("Maas odemesi basarisiz");
                            break;
                            }
                        }else{
                            printf("Yetersiz Bakiye!\n");
                        break;
                        }
                case 2:
                    printf("\nIkramiye Tutar : ");
                        scanf("%d",&miktar);
                        kopya=sirketBakiyesi;
                        if(miktar<sirketBakiyesi){
                            printf("Ikramiye odenecek personel no : ");
                            scanf("%d",&kullanicino);
                            sirketBakiyesi=paraYukle(miktar,kullanicino,sirketBakiyesi,odemeKismi);
                            if(kopya!=sirketBakiyesi){
                                system("cls");
                            printf("\nIkramiye odemesi basarili\n");

                            }else{
                            printf("odeme basarisiz");
                            break;
                            }
                        }else{
                            printf("Yetersiz Bakiye!\n");
                        break;
                        }
                    break;
                                    case 3:
                    printf("\nYardim Tutar : ");
                        scanf("%d",&miktar);
                        kopya=sirketBakiyesi;
                        if(miktar<sirketBakiyesi){
                            printf("Yardim odenecek personel no : ");
                            scanf("%d",&kullanicino);
                            sirketBakiyesi=paraYukle(miktar,kullanicino,sirketBakiyesi,odemeKismi);
                            if(kopya!=sirketBakiyesi){
                                system("cls");
                            printf("\nYardim odemesi basarili\n");

                            }else{
                            printf("odeme basarisiz");
                            break;
                            }
                        }else{
                            printf("Yetersiz Bakiye!\n");
                        break;
                        }
                        break;
            }
            break;

    case 2:
        do{
            printf("Yeni Personel No : ");
            scanf("%d",&yeniPersonelno);
            printf("Parola : ");
            scanf("%d",&yeniPersonelsifre);
            printf("Adi : ");
            scanf("%s",&cAdi);
            eklenecekSecim=2;
            if(yeniKullanici(yeniPersonelno,yeniPersonelsifre,cAdi,eklenecekSecim)){
                    system("cls");
                printf("Yeni Personel Kaydedildi\n");
                y=0;
            }else{
                printf("!Hata 101!(gecersiz veya kayitli no girdiniz)\n");
                y++;
            }
        }while(y>0);
        break;

    case 3: system("cls");
            printf("Silinecek Personel no :");
            scanf("%d",&silinecekNo);
            cikarilacakSecim=2;
            if(kullaniciSil(silinecekNo,cikarilacakSecim)){
                system("cls");
                printf("%d Nolu personel isten cikarilmistir\n",silinecekNo);
            }else{
            printf("Cikartma islemi Basarisiz");
            }
    break;

    default:
        if(secim!=0){
            printf("Gecersiz Secim");
        }
    } // switch blok sonu
    }
    while(secim!=0);
    system("cls");
    printf("\n*** Oturumunuz Sonlandirildi ***\n");
    } // basarili giris
    } // Oturum giris kontrolü
    while(g>0);
    break;// case 2 sonu
    case 3:
        do{
        printf("personel no :");
        scanf("%d",&kullanicino);
        printf("\npersonel sifre :");
        scanf("%d",&sifre);
        if(!giris(kullanicino,sifre,girisSecim)){
            system("cls");
            printf("Personel No veya Sifre Hatali!\n");
            g++;
        }else{
        system("cls");
        printf("giris basarili\n");
        int s=0;
        do{
        bakiye=perBakiyeGoruntule(kullanicino);
        printf("Hesap Bakiyesi :%d\n1-para aktarma\n0-Oturumu Sonlandirma\n", bakiye);
        scanf("%d",&secim);
        switch(secim){
    case 0: system("cls"); printf("*** Oturum Sonlandirildi ***\n"); break;

    case 1:
        printf("Aktarilacak Tutari giriniz :");
        scanf("%d",&perMiktar);
        if(perMiktar>bakiye){
            system("cls");
            printf("Yetersiz Bakiye ");
        }else{

        if(personelParaAktarma(perMiktar,kullanicino,bakiye)){
                system("cls");
            printf("para aktarimi basarili\n");
            s=0;

        break;
        }else{
            printf("Basarisiz");
            s=0;
        }

        }
        }
        }while(s==0 && secim!=0);
        g=0;
        }
        }while(g>0);
    break;
    default : system("cls") ; printf("Gecersiz Secim\n"); break;
}
}
//üst menüye atiyor
while(secim==0);
return 0;
}
