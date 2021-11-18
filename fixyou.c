#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void user();
void mimin();
void login();
void menu();
void pesan();
void kotakmasuk();
void fiturmimin();
void stiker();
void header();
void timeline();
void hpstimeline();
void transfer();
char idlogin[100],passlogin[100];
struct{
	char id[100],timeline[100];
}t;
struct{
	char id[100],pass[100];
}p;
struct{
	char message[100],id[100],pengirim[100];
}q;
struct{
	char id[100];
	int pulsa;
}r;
main(){
	system("cls");
	int menu;
	header();
	printf("1. User\n");
	printf("2. Admin\n");
	printf("3. Exit\n");
	printf("Inputkan Jenis Pengguna (1/2/3) : ");scanf("%i",&menu);
	fflush(stdin);
	switch (menu){
		case 1:{
			system("cls");
			header();
			user();
			break;
		}
		case 2:{
			mimin();
			break;
		}
		case 3:{
			return 0;
			break;
		}
		default :{
			printf("Pilihan Tidak Tersedia\n");
			system("pause");
			main();
			break;
		}
	}
}
void user(){
	int jenis;
	FILE *pesan;
	FILE *saldo;
	printf("1. Belum Memiliki Akun? Daftar Sekarang!\n");
	printf("2. Login\n");
	printf("Input 1 Untuk Mendaftar, Input 2 Untuk Login : ");scanf("%i",&jenis);
	fflush(stdin);
	if(jenis==1){
		system("cls");
		header();
		saldo=fopen("saldo.dat","ab");
		pesan=fopen("pesan.dat","ab");
		printf("Menu Registrasi\n");
		printf("Username : ");gets(p.id);
		printf("Password : ");gets(p.pass);
		printf("Saldo Awal Pulsa : ");scanf("%i",&r.pulsa);fflush(stdin);
		fwrite(&p,sizeof(p),1,pesan);
		strcpy(r.id,p.id);
		fwrite(&r,sizeof(r),1,saldo);
		fclose(pesan);
		fclose(saldo);
		login();
	}
	else if(jenis==2){
		login();
	}
	else{
		printf("Pilihan Tidak Tersedia!\n");
		system("pause");
		main();
	}
}
void mimin(){
	system("cls");
	header();
	char passmimin[100];
	int i=1,asdf,bagi;
	printf("Mencoba Masuk Sebagai Admin\nInputkan Password : ");gets(passmimin);
	if(strcmp(passmimin,"admin")==0){
		system("cls");
		fituradmin();
	}
	else{
		printf("Gagal Masuk Sebagai Admin!\n");
		system("pause");
	}
	main();
}
void login(){
	system("cls");
	header();
	int stop;
	FILE *pesan;
	pesan=fopen("pesan.dat","rb");
	printf("Menu Login\n");
	printf("Username : ");gets(idlogin);
	printf("Password : ");gets(passlogin);
	while(fread(&p,sizeof(p),1,pesan)==1){
			if(strcmp(p.id,idlogin)==0 && strcmp(p.pass,passlogin)==0){
				fclose(pesan);
				system("cls");
				menu();
				stop=1;
			}
	}
	if(stop!=1){
		printf("Login Gagal! Silakan Coba Lagi!\nInput 'main' Sebagai Username atau Password pada Menu Login Untuk Kembali ke Menu Utama\n");
		fclose(pesan);
		system("pause");
		if(strcmp(idlogin,"main")==0 || strcmp(passlogin,"main")==0){
			main();
		}
		else{
			login();
		}
	}
}
void pesan(){
	int i,cari,tarif,total,sisa,c;
	i=1;
	FILE *saldo;
	FILE *temp;
	FILE *pesan;
	FILE *timeline;
	FILE *message;
	printf("1. Kirim ke User\n");
	printf("2. Update Status\n");
	printf("Pilih Opsi (1/2) : ");scanf("%i",&c);fflush(stdin);
	if(c==1){
		system("cls");
		header();
		pesan=fopen("pesan.dat","rb");
		printf("Daftar Pengguna :\n");
		while(fread(&p,sizeof(p),1,pesan)==1){
			printf("%i. %s\n",i,p.id);
			i++;
		}
		fclose(pesan);
		message=fopen("message.dat","ab");
		printf("User Penerima Pesan : ");
		gets(q.id);
		system("cls");
		header();
		printf("Input 'stiker' Untuk Mengirimkan Stiker Keren!\n");
		printf("Masukkan Pesan Untuk %s : ",q.id);gets(q.message);
		strcpy(q.pengirim,idlogin);
		tarif=strlen(q.message)*50;
		saldo=fopen("saldo.dat","rb");
		while(fread(&r,sizeof(r),1,saldo)==1){
			if(strcmp(idlogin,r.id)==0){
				printf("Pulsa : %i\n",r.pulsa);
			}
		}
		fclose(saldo);
		printf("Tarif Pengiriman Pesan : %i\n",tarif);
		saldo=fopen("saldo.dat","rb");
		temp=fopen("temp.dat","ab");
		while(fread(&r,sizeof(r),1,saldo)==1){
			if(strcmp(idlogin,r.id)!=0){
				fwrite(&r,sizeof(r),1,temp);
			}
			else{
				if(r.pulsa>=tarif){
					sisa=r.pulsa;
					total=sisa-tarif;
					r.pulsa=total;
					fwrite(&r,sizeof(r),1,temp);
					fwrite(&q,sizeof(q),1,message);
				}
				else{
					printf("Pulsa Tidak Cukup!\n");
					fwrite(&r,sizeof(r),1,temp);
				}
			}
		}
		fclose(message);
		fclose(saldo);
		fclose(temp);
		remove("saldo.dat");
		rename("temp.dat","saldo.dat");
		saldo=fopen("saldo.dat","rb");
		while(fread(&r,sizeof(r),1,saldo)==1){
			if(strcmp(idlogin,r.id)==0){
				printf("Sisa Pulsa : %i\n",r.pulsa);
			}
		}
		fclose(saldo);
	}
	else if(c==2){
		system("cls");
		header();
		timeline=fopen("timeline.dat","ab");
		printf("Apa yang Sedang Anda Pikirkan : ");gets(t.timeline);
		strcpy(t.id,idlogin);
		fwrite(&t,sizeof(t),1,timeline);
		fclose(timeline);
		printf("Status Anda Telah Terkirim!\n");
	}
}
void kotakmasuk(){
	int nopesan;
	FILE *pesan;
	FILE *message;
	pesan=fopen("pesan.dat","rb");
	message=fopen("message.dat","rb");
	while(fread(&q,sizeof(q),1,message)==1){
		if(strcmp(idlogin,p.id)==0 && strcmp(q.id,p.id)==0){
			printf("Pesan Dari %s :\n",q.pengirim,q.message);
			if(strcmp(q.message,"stiker")==0){
				stiker();
			}
			else{
				printf("%s\n",q.message);
			}
			nopesan=1;
		}
	}
	if(nopesan!=1){
		printf("Tidak Ada Pesan Masuk\n");
	}
	fclose(pesan);
	fclose(message);
	system("pause");
	system("cls");
}
void menu(){
	header();
	printf("Login Sebagai : %s\n",idlogin);
	int a,i,nominal,total,hold,x,m;
	char isi,kosong;
	printf("1. Lihat Timeline\n");
	printf("2. Kirim Pesan\n");
	printf("3. Kotak Masuk\n");
	printf("4. Cek Pulsa\n");
	printf("5. Transfer Pulsa\n");
	printf("6. Kosongkan Kotak Masuk\n");
	printf("7. Logout\n");
	printf("Pilih Menu (1/2/3/4/5) : ");
	scanf("%i",&a);fflush(stdin);
	switch(a){
		case 1: {
			timeline();
			break;
		}
		case 2: {
			system("cls");
			header();
			pesan();
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 3: {
			system("cls");
			header();
			kotakmasuk();
			system("cls");
			menu();
			break;
		}
		case 4: {
			system("cls");
			header();
			FILE *saldo;
			FILE *temp;
			saldo=fopen("saldo.dat","rb");
			while(fread(&r,sizeof(r),1,saldo)==1){
				if(strcmp(idlogin,r.id)==0){
					printf("Pulsa : %i\n",r.pulsa);
				}
			}
			fclose(saldo);
			saldo=fopen("saldo.dat","rb");
			temp=fopen("temp.dat","ab");
			printf("Ingin Melakukan Isi Ulang Pulsa? (y/n) : ");
			scanf("%c",&isi);fflush(stdin);
			if(isi=='y'){
				m=1;
				printf("Masukkan Nominal Pengisian Pulsa : ");scanf("%i",&hold);fflush(stdin);
				while(fread(&r,sizeof(r),1,saldo)==1){
					if(strcmp(idlogin,r.id)!=0){
						fwrite(&r,sizeof(r),1,temp);
					}
					else{
						nominal=r.pulsa;
						total=nominal+hold;
						r.pulsa=total;
						fwrite(&r,sizeof(r),1,temp);
					}
				}
			}
			else{
				while(fread(&r,sizeof(r),1,saldo)==1){
					fwrite(&r,sizeof(r),1,temp);
				}
			}
			fclose(saldo);
			fclose(temp);
			remove("saldo.dat");
			rename("temp.dat","saldo.dat");
			if(m==1){
				saldo=fopen("saldo.dat","rb");
				while(fread(&r,sizeof(r),1,saldo)==1){
					if(strcmp(idlogin,r.id)==0){
						printf("Pulsa Setelah Isi Ulang : %i\n",r.pulsa);
					}
				}
			fclose(saldo);
			}
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 5: {
			transfer();
			break;
		}
		case 6: {
			FILE *message;
			FILE *newmessage;
			message=fopen("message.dat","rb");
			newmessage=fopen("newmessage.dat","wb");
			system("cls");
			header();
			printf("Ingin Mengosongkan Kotak Masuk? (y/n) : ");scanf("%c",&kosong);
			if(kosong=='y'){
				while(fread(&q,sizeof(q),1,message)==1){
					if(strcmp(idlogin,q.id)!=0){
						fwrite(&q,sizeof(q),1,newmessage);
					}
				}
				x=1;
			}
			else{
				while(fread(&q,sizeof(q),1,message)==1){
					fwrite(&q,sizeof(q),1,newmessage);
				}
			}
			if(x==1){
				printf("Kotak Masuk Berhasil Dikosongkan!\n");
			}
			fclose(message);
			fclose(newmessage);
			remove("message.dat");
			rename("newmessage.dat","message.dat");
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 7: {
			main();
			break;
		} 
	}
}
void fituradmin(){
	header();
	printf("Telah Masuk Sebagai Admin!\n");
	char passmimin[100],hapus[100];
	int asdf,bagi,total,sementara,s,j,k;
	int i=1,del=0;
	FILE *message;
	FILE *newmessage;
	FILE *pesan;
	FILE *newpesan;
	FILE *saldo;
	FILE *temp;
	printf("1. Hapus User\n");
	printf("2. Tampilkan Seluruh User\n");
	printf("3. Bagi Bagi Pulsa\n");
	printf("4. Hapus Status\n");
	printf("5. Format Seluruh User\n");
	printf("6. Logout\n");
	printf("Pilih Menu (1/2/3/4/5) : ");scanf("%i",&asdf);fflush(stdin);
	if(asdf==1){
		system("cls");
		header();
		pesan=fopen("pesan.dat","rb");
		while(fread(&p,sizeof(p),1,pesan)==1){
			printf("%i. %s\n",i,p.id);
			i++;
		}
		fclose(pesan);
		if(i!=1){
			printf("Inputkan User yang Akan Dihapus : ");
			gets(hapus);
			pesan=fopen("pesan.dat","rb");
			newpesan=fopen("newpesan.dat","wb");
			saldo=fopen("saldo.dat","rb");
			temp=fopen("temp.dat","wb");
			message=fopen("message.dat","rb");
			newmessage=fopen("newmessage.dat","wb");
			while(fread(&p,sizeof(p),1,pesan)==1){
				if(strcmp(hapus,p.id)!=0){
					fwrite(&p,sizeof(p),1,newpesan);
					del=1;
				}
			}
			while(fread(&r,sizeof(r),1,saldo)==1){
				if(strcmp(hapus,r.id)!=0){
					fwrite(&r,sizeof(r),1,temp);
					del=1;
				}
			}
			while(fread(&q,sizeof(q),1,message)==1){
				if(strcmp(hapus,q.id)!=0){
					fwrite(&q,sizeof(q),1,newmessage);
					del=1;
				}
			}
			fclose(pesan);
			fclose(newpesan);
			remove("pesan.dat");
			rename("newpesan.dat","pesan.dat");
			fclose(saldo);
			fclose(temp);
			remove("saldo.dat");
			rename("temp.dat","saldo.dat");
			fclose(message);
			fclose(newmessage);
			remove("message.dat");
			rename("newmessage.dat","message.dat");
			if(del!=0){
				printf("Akun %s Telah Dihapus\n",hapus);
			}
		}
		else{
			printf("Belum Ada User yang Mendaftar\n");
		}
		system("pause");
		system("cls");
		fituradmin();
	}
	else if(asdf==2){
		system("cls");
		header();
		char sort[100][100],hold[100][100];
		printf("Tampilkan User Berdasarkan :\n");
		printf("1. Waktu Pendaftaran\n");
		printf("2. Abjad\n");
		printf("Pilih Opsi (1/2) : ");scanf("%i",&s);
		system("cls");
		header();
		printf("Menampilkan Seluruh User :\n");
		pesan=fopen("pesan.dat","rb");
		if(s==1){
			while(fread(&p,sizeof(p),1,pesan)==1){
				printf("%i. %s\n",i,p.id);
				i++;
			}
		}
		else if(s==2){
			int n=1,o=1;
			while(fread(&p,sizeof(p),1,pesan)==1){
				strcpy(sort[o],p.id);
				i++;
				n++;
				o++;
			}
			for (j=1;j<n;j++){
				for(k=1;k<n-1;k++){
					if(strcmp(sort[j],sort[k])<0){
						strcpy(hold,sort[j]);
						strcpy(sort[j],sort[k]);
						strcpy(sort[k],hold);
					}
				}
			}
			for(j=1;j<n;j++){
				printf("%i. %s\n",j,sort[j]);
			}
		}
		if(i==1){
			printf("Tidak Ada User\n");
		}
		fclose(pesan);
		system("pause");
		system("cls");
		fituradmin();
	}
	else if(asdf==3){
		system("cls");
		header();
		printf("Masukkan Nominal Pulsa yang Akan Dibagikan : ");scanf("%i",&bagi);
		saldo=fopen("saldo.dat","rb");
		temp=fopen("temp.dat","ab");
		while(fread(&r,sizeof(r),1,saldo)==1){
			sementara=r.pulsa;
			total=sementara+bagi;
			r.pulsa=total;
			fwrite(&r,sizeof(r),1,temp);
		}
		fclose(saldo);
		fclose(temp);
		remove("saldo.dat");
		rename("temp.dat","saldo.dat");
		printf("Pulsa Sejumlah %i Telah Dibagikan!\n",bagi);
		system("pause");
		system("cls");
		fituradmin();
	}
	else if(asdf==4){
		hpstimeline();
	}
	else if(asdf==5){
		remove("saldo.dat");
		remove("message.dat");
		remove("pesan.dat");
		system("cls");
		header();
		printf("Format Berhasil!\n");
		system("pause");
		system("cls");
		fituradmin();
	}	
}
void stiker(){
	int i,j;
	for(i=1;i<=11;i++){
		printf("\n");
		for(j=1;j<=11;j++){
			if(j==6){
				printf("  *");
			}
			else if(i==6){
				printf("  *");
			}
			else if(i==1 && j>6){
				printf("  *");
			}
			else if(i==11 && j<6){
				printf("  *");
			}
			else if(j==1 && i<6){
				printf("  *");
			}
			else if(j==11 && i>6){
				printf("  *");
			}
			else{
				printf("   ");
			}
		}
	}
	printf("\n\tH A I L  H Y D R A !\n\n");
}
void header(){
	printf("    D A S K O M\n\tM E S S E N G E R\n");
	printf("-----------------------------\n");
}
void timeline(){
	int z;
	FILE *timeline;
	timeline=fopen("timeline.dat","rb");
	system("cls");
	header();
	printf("Timeline :\n");
	while(fread(&t,sizeof(t),1,timeline)==1){
		printf("%s :\n",t.id);
		printf("%s\n",t.timeline);
		printf("-----------------------------\n");
		z=1;
	}
	fclose(timeline);
	if(z!=1){
		printf("Timeline Kosong, Belum Ada User yang Update Status\n");
	}
	system("pause");
	system("cls");
	menu();
}
void hpstimeline(){
	system("cls");
	header();
	int f=1,g=1;
	char xxx[100];
	FILE *hapus;
	FILE *timeline;
	timeline=fopen("timeline.dat","rb");
	while(fread(&t,sizeof(t),1,timeline)==1){
		printf("%i. %s\n",f,t.id);
		f++;
	}
	fclose(timeline);
	if(f!=1){
		printf("User yang Akan Dihapus Statusnya : ");gets(xxx);
		timeline=fopen("timeline.dat","rb");
		hapus=fopen("hapus.dat","wb");
		while(fread(&t,sizeof(t),1,timeline)==1){
			if(strcmp(xxx,t.id)!=0){
				fwrite(&t,sizeof(t),1,hapus);
				g++;
			}
		}
		fclose(timeline);
		fclose(hapus);
		remove("timeline.dat");
		rename("hapus.dat","timeline.dat");
	}
	if(f==1 && g==1){
		system("cls");
		header();
		printf("Belum Ada User yang Mengirim Status\n");
	}
	system("pause");
	system("cls");
	fituradmin();
}
void transfer(){
	system("cls");
	header();
	char tujuan[100];
	int jumlah,i=1,sisa,total,awal,trf;
	FILE *saldo;
	FILE *temp;
	saldo=fopen("saldo.dat","rb");
	while(fread(&r,sizeof(r),1,saldo)==1){
		printf("%i. %s\n",i,r.id);
		i++;
	}
	fclose(saldo);
	saldo=fopen("saldo.dat","rb");
	temp=fopen("temp.dat","wb");
	printf("User Tujuan : ");gets(tujuan);
	printf("Nominal Pulsa yang Akan di Transfer : ");scanf("%i",&jumlah);
	while(fread(&r,sizeof(r),1,saldo)==1){
		if(strcmp(idlogin,r.id)==0){
			if(r.pulsa>=jumlah){
				awal=r.pulsa;
				total=awal-jumlah;
				r.pulsa=total;
				fwrite(&r,sizeof(r),1,temp);
			}
			else{
				fwrite(&r,sizeof(r),1,temp);
				trf=1;
			}	
		}	
		else if(strcmp(tujuan,r.id)==0){
			if(trf!=1){
				awal=r.pulsa;
				total=awal+jumlah;
				r.pulsa=total;
				fwrite(&r,sizeof(r),1,temp);
			}
			else{
				fwrite(&r,sizeof(r),1,temp);
			}	
		}
		else if(strcmp(tujuan,r.id)!=0 || strcmp(idlogin,r.id)!=0){
			fwrite(&r,sizeof(r),1,temp);
		}
	}
	if(trf==1){
		printf("Pulsa Tidak Mencukupi Untuk Transfer\n");
	}
	else{
		printf("Transfer Berhasil\n");
	}
	fclose(saldo);
	fclose(temp);
	remove("saldo.dat");
	rename("temp.dat","saldo.dat");
	system("pause");
	system("cls");
	menu();
}
