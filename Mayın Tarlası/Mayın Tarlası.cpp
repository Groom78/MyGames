#include<bits/stdc++.h>
#include<conio.h>

using namespace std;
#define ll long long
#define de cout<<"debuglandınız\n";
#define md 1000000007
#define endl "\n"
#define mp make_pair
#define pb push_back
#define clear system("cls")

void bas();
void olustur(int,int);
void bom(int,int);
void hak();
void mainmenu();
void oyun();
void help();
void lose();
void win();
void renk();
void last();
void reset();
int check(string);
int don(string);

int boyut,boyuts,msum,mmev,x,y,w,l,kk,ac[105][105],grid[105][105],kac[105][105];
bool bomb[105][105];
string s,xs,ys;
char c,qq;
bool flag;

queue<pair<pair<int,int>,bool > >macs;
queue<pair<pair<int,int>,bool > >yed;

void reset(){
	for(int i=1;i<=103;i++){
		for(int j=1;j<=103;j++)ac[i][j]=0;
	}
	for(int i=1;i<=103;i++){
		for(int j=1;j<=103;j++)grid[i][j]=0;
	}
	for(int i=1;i<=103;i++){
		for(int j=1;j<=103;j++)bomb[i][j]=0;
	}
	for(int i=1;i<=103;i++){
		for(int j=1;j<=103;j++)kac[i][j]=0;
	}
}

void last(){
	cout<<"En son oynadigin "<<w+l<<" oyun:\n";
	while(macs.size()){
		int a,b,c;
		a=macs.front().first.first;
		b=macs.front().first.second;
		c=macs.front().second;
		if(a<10)cout<<"  ";
		cout<<a<<"X"<<a<<"  ";
		printf("%3d mayin -> ",b);
		if(c)cout<<"Galibiyet\n";
		else cout<<"Maglubiyet\n";
		macs.pop();
		yed.push(make_pair(make_pair(a,b),c));
	}
	while(yed.size()){
		int a,b,c;
		a=yed.front().first.first;
		b=yed.front().first.second;
		c=yed.front().second;
		yed.pop();
		macs.push(make_pair(make_pair(a,b),c));
	}
	cout<<"\nMenuye donmek icin bir tusa bas\n";
	char i;
	i=getch();
	mainmenu();
}

void renk(){
	clear;
	cout<<"Bir Rakam Giriniz: ";
	char i;
	i=getch();
	if(i<48 or i>57)mainmenu;
	else{
		if(i=='0')system("color 07");
		if(i=='1')system("color 70");
		if(i=='2')system("color 1F");
		if(i=='3')system("color F1");
		if(i=='4')system("color 5F");
		if(i=='5')system("color F5");
		if(i=='6')system("color 3F");
		if(i=='7')system("color 6F");
		if(i=='8')system("color 8F");
		if(i=='9')system("color 0a");
	}
	mainmenu();
}

void lose(){
	l++;
	macs.push(make_pair(make_pair(boyut,msum),0));
	system("title :(");
	system("color 4F");
	flag=1;
	bas();
	cout<<"Kaybettin :((\n";
	cout<<"Menuye donmek icin bir tusa bas\n";
	char i;
	i=getch();
	system("color 07");
	mainmenu();
}

void win(){
	w++;
	macs.push(make_pair(make_pair(boyut,msum),1));
	system("title :)");
	system("color 2F");
	flag=1;
	bas();
	cout<<"Kazandin !!!\n";
	cout<<"Menuye donmek icin bir tusa bas\n";
	char i;
	i=getch();
	system("color 07");
	mainmenu();
}

void bom(int x,int y){
	ac[x][y]=1;
	if(!x or !y or x>boyut or y>boyut or kac[x][y])return;
	if(ac[x-1][y]==0 and bomb[x-1][y]==0)bom(x-1,y);
	if(ac[x+1][y]==0 and bomb[x+1][y]==0)bom(x+1,y);
	if(ac[x][y-1]==0 and bomb[x][y-1]==0)bom(x,y-1);
	if(ac[x][y+1]==0 and bomb[x][y+1]==0)bom(x,y+1);
	if(ac[x+1][y+1]==0 and bomb[x+1][y+1]==0)bom(x+1,y+1);
	if(ac[x-1][y+1]==0 and bomb[x-1][y+1]==0)bom(x-1,y+1);
	if(ac[x+1][y-1]==0 and bomb[x+1][y-1]==0)bom(x+1,y-1);
	if(ac[x-1][y-1]==0 and bomb[x-1][y-1]==0)bom(x-1,y-1);
}

void bas(){
	cout<<"   ";
	for(int i=1;i<=boyut;i++){
		printf("%2d  ",i);
	}
	cout<<endl;
	if(flag){
		for(int i=1;i<=boyut;i++){
		printf("%2d ",i);
		for(int j=1;j<=boyut;j++){
			if(bomb[i][j]==1)printf(" %c  ",-49);
			else{
				if(kac[i][j])printf("%2d  ",kac[i][j]);
				else printf("    ");
			}	
		}
		cout<<endl<<endl;
		}
		flag=0;
		return;
	}
	for(int i=1;i<=boyut;i++){
		printf("%2d ",i);
		for(int j=1;j<=boyut;j++){
			if(grid[i][j]==1)printf(" %c  ",-67);
			else{
				if(ac[i][j]==0)printf("%c%c  ",-37,-37);
				else{
					if(kac[i][j])printf("%2d  ",kac[i][j]);
					else printf("    ");
				}
			}
		}
		cout<<endl<<endl;
	}
	cout<<endl;
	cout<<"Kalan Mayin Sayisi: "<<mmev<<endl<<endl;
}

void olustur(int x,int y){
	reset();
	ac[x][y]=1;
	int kb=msum,xx,yy;
	while(kb){
		xx=(rand()%boyut)+1;
		yy=(rand()%boyut)+1;
		if(bomb[xx][yy]==0 and ac[xx][yy]==0){
			bomb[xx][yy]=1;
			kb--;
		}
	}
	for(xx=1;xx<=boyut;xx++){
		for(yy=1;yy<=boyut;yy++){
			kac[xx][yy]+=bomb[xx-1][yy-1];
			kac[xx][yy]+=bomb[xx][yy-1];
			kac[xx][yy]+=bomb[xx+1][yy-1];
			kac[xx][yy]+=bomb[xx-1][yy];
			kac[xx][yy]+=bomb[xx+1][yy];
			kac[xx][yy]+=bomb[xx-1][yy+1];
			kac[xx][yy]+=bomb[xx][yy+1];
			kac[xx][yy]+=bomb[xx+1][yy+1];
		}
	}
	bom(x,y);
	kk=0;
	for(int i=1;i<=boyut;i++){
		for(int j=1;j<=boyut;j++){
			kk+=!(ac[i][j]);
		}
	}
	if(boyuts/12 > kk){
		olustur(x,y);
		return;
	}
	clear;
}

int check(string s){
	for(int i=0;i<s.length();i++){
		if(s[i]<48 or s[i]>57)return 1;
	}
	return 0;
}

int don(string s){
	int a=0,i=0;
	for(i=0;i<s.length();i++){
		a+=int(s[i]-48)*(pow(10,s.length()-i-1));
	}
	return a;
}

void hakk(){
	clear;
	cout<<"Author: Enes CAKIL - 08.04.2020\n\nThanks to Altay KILIC\n\n";
	cout<<"Menuye donmek icin bir tusa basiniz...\n";
	char i;
	i=getch();
	mainmenu();
}

void help(){
	clear;
	cout<<"Oyun yalnizca klavye kullanilarak oynanir.\n\n";
	cout<<"Oyunun basinda oyun alaninin boyutunu secmelisiniz.\n";
	cout<<"Alan, kare ve en az 5X5, en fazla 50X50 boyutunda olabilir.\n";
	cout<<"Sonrasinda kac tane mayin olmasini istediginizi secmelisiniz.\n";
	cout<<"Mayin sayisi tarladaki kare sayisinin en fazla %50 si,\n";
	cout<<"En az %10 u olabilir.\n";
	cout<<"Daha sonra ilk hangi kutuyu acacaginizi secmelisiniz.\n";
	cout<<"Sonraki hamlelerde eger kutu acacaksaniz 1,\n";
	cout<<"Bayrak koyacaksaniz 2 tusuna basmali,\n";
	cout<<"Ardindan kutunun yerini yazmalisiniz.\n";
	cout<<"Eger kutuda bayrak varsa acabilmek icin once onu kaldirmalisiniz.\n";
	cout<<"Bomba olan bir kutuyu sectiginizde ya da\n";
	cout<<"Bomba olmayan tum kutular acildiginda oyun biter.\n";
	cout<<"Oyunda deger girmek haric ENTER tusuna basmaniza gerek yok.\n";
	cout<<"Bir konum yazarken once kacinci satir,\n";
	cout<<"Sonra kacinci sutun oldugunu yazmalisiniz.\n";
	cout<<"Buyuk tarlalar icin mumkunse tam ekran modunda oynamaniz tavsiye edilir.\n";
	cout<<"Iyi eglencelerr...\n\n\n";
	cout<<"Menuye donmek icin bir tusa basiniz...\n";
	char i;
	i=getch();
	mainmenu();
}

void loop(){
	clear;
	kk=0;
	for(int i=1;i<=boyut;i++){
		for(int j=1;j<=boyut;j++){
			kk+=!(ac[i][j]);
		}
	}
	if(kk==msum){
		win();
		return;
	}
	char i;
	bas();
	cout<<"1: Kutu Ac\n2: Bayrak Koy\n";
	while(1){
		i=getch();
		if(i!='1' and i!='2')continue;
		break;
	}
	clear;
	if(i=='2'){
		bas();
		while(1){
			cout<<"Bayrak Koymak Istediginiz Yeri Seciniz: ";
			cin>>xs;
			cin>>ys;
			if(check(xs) or don(xs)>boyut or don(xs)<1 or check(ys) or don(ys)>boyut or don(ys)<1){
				clear;
				bas();
				cout<<"Hatali giris :/\nTekrar deneyiniz..\n\n";
				continue;
			}		
			break;
		}
		y=don(ys);
		x=don(xs);
		if(ac[x][y]){
			loop();
			return;
		}
		if(grid[x][y]){
			grid[x][y]=0;
			mmev++;
		}
		else{
			grid[x][y]=1;
			mmev--;
		}
		loop();
	}
	else{	
		bas();
		while(1){
			cout<<"Acmak Istediginiz Yeri Seciniz: ";
			cin>>xs;
			cin>>ys;
			if(check(xs) or don(xs)>boyut or don(xs)<1 or check(ys) or don(ys)>boyut or don(ys)<1){
				clear;
				bas();
				cout<<"Hatali giris :/\nTekrar deneyiniz..\n\n";
				continue;
			}
			break;
		}
		x=don(xs);
		y=don(ys);
		if(ac[x][y] or grid[x][y])loop();
		else{
			if(bomb[x][y]){
				clear;
				lose();
			}
			else{
				bom(x,y);
				loop();
			}	
		}
	}
}

void mainmenu(){
	system("title Mayin_Tarlasi");
	clear;
	if(w)cout<<"Su anda toplam "<<w+l<<" oyundan "<<w<<" tanesini kazandin!!!\n\n";
	else cout<<"Mayin Tarlasi Oyununa Hosgeldin :)\n\n";
	cout<<"Secenekler:\n";
	if(w) cout<<1<<": Yeni Oyun\n";
	else cout<<1<<": Oyuna Basla\n";
	cout<<2<<": Arayuz Yardimi\n";
	cout<<3<<": Hakkinda\n";
	cout<<4<<": Renk Sec\n";
	cout<<5<<": Cikis\n";
	if(w)cout<<6<<": Son Oyunlar\n";
	char i;
	i=getch();
	if(i=='1'){
		clear;
		oyun();
	}
	else if(i=='2'){
		help();
	}
	else if(i=='3'){
		hakk();
	}
	else if(i=='4'){
		renk();
	}
	else if(i=='5'){
		clear;
		cout<<"Gorusmek uzere...\n";
		system("exit");
	}
	else if(w and i=='6'){
		clear;
		last();
	}
	else{
		mainmenu();
	}
}

void oyun(){
	string s;
	while(1){
		cout<<"Tarla Boyutunu Giriniz: ";
		cin>>s;
		if(check(s) or don(s)>=51 or don(s)<=4){
			clear;
			cout<<"Hatali giris :/\nTekrar deneyiniz..\n\n";
			continue;
		}
		break;
	}
	boyut=don(s);
	boyuts=boyut*boyut;
	clear;
	while(1){
		cout<<"Tavsiye Edilen Mayin Sayisi: "<<boyut*boyut/8<<"\n";
		cout<<"Mayin Sayisini Giriniz: ";
		cin>>s;
		clear;
		if(check(s) or don(s)>boyuts/2 or don(s)<boyuts/10){
			cout<<"Deger cok kucuk ya da cok buyuk!!\nTekrar deneyiniz..\n\n";
			continue;
		}
		break;
	}
	msum=don(s);
	mmev=msum;
	clear;
	reset();
	bas();
	while(1){
		cout<<"Ilk Acmak Istediginiz Kutuyu Giriniz: ";
		cin>>xs>>ys;
		if(check(xs) or don(xs)>boyut or don(xs)<1 or check(ys) or don(ys)>boyut or don(ys)<1){
			clear;
			bas();
			cout<<"Hatali giris :/\nTekrar deneyiniz..\n\n";
			continue;
		}	
		clear;
		break;
	}
	bas();
	x=don(xs);
	y=don(ys);
	olustur(x,y);
	loop();
	system("PAUSE");
}

int main(){
	srand(time(0));
	mainmenu();	
	return 0;
}