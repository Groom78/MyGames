#include<bits/stdc++.h>
#include<Windows.h>
#include<conio.h>

using namespace std;
#define ll long long 

const int maxx=50,maxy=25;
int yer,xer,enes,w,timer,kalma[maxx][maxy],pre;
int collor,zorluk,ec;
queue<pair<int,int> >en[maxx][maxy];
queue<pair<int,int> >yeden[maxx][maxy];
queue<pair<int,int> >g;
queue<pair<int,int> >ged;
char sahne[maxx][maxy],presahne[maxx][maxy],tuslar[256];
bool bars[maxx][maxy];

void setcursor(int,int);
void input(int);
void tusoku();
void clear(bool);
void invis(bool);
void dplay();
void bound();
void dene();
void ilerle();
void aktar();
void uzat();
void ciz();
void win();
void afk();
void oyun();
void help();
void hakk();
void galan();
void dus();
void renk();
void setting();
void mainmenu();

void setcursor(int x, int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	
}

void input(char tuslar[]){
	for(int x=0;x<256;x++){
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
	}
}

void tusoku(){
	input(tuslar);
	if(tuslar[int('%')] or tuslar[int('A')])xer--;//sol
	if(tuslar[39] or tuslar[int('D')])xer++;//sag
	if(tuslar[int('&')] or tuslar[int('W')])yer--;//ust
	if(tuslar[int('(')] or tuslar[int('S')])yer++;//alt
	if(yer>=maxy-1)yer=maxy-2;
	else if(yer<=0)yer=1;
	if(xer>=maxx-1)xer=maxx-2;
	else if(xer<=0)xer=1;
}

void clear(bool a){	
	if(!a){
		timer=enes=xer=yer=w=0;
		for(int i=0;i<maxx;i++){
			for(int j=0;j<maxy;j++){
				presahne[i][j]='x';
				kalma[i][j]=0;
				while(en[i][j].size())en[i][j].pop();
			}
		}	
	}
	for(int i=0;i<maxx;i++){
		for(int j=0;j<maxy;j++){
			sahne[i][j]=' ';
			bars[i][j]=0;
		}
	}	
}

void invis(bool a){
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO    cursorInfo;
	GetConsoleCursorInfo(out,&cursorInfo);
	if(a)cursorInfo.bVisible = true ;
	else cursorInfo.bVisible = false ;
	SetConsoleCursorInfo(out,&cursorInfo);
} 

void dplay(){
	for(int y=0;y<maxy;y++){
		for(int x=0;x<maxx;x++){
			if(sahne[x][y]!=presahne[x][y]){
				setcursor(2*x,y);
				printf("%c",sahne[x][y]);
				printf("%c",sahne[x][y]);
				presahne[x][y]=sahne[x][y];
			}
		}
	}
	setcursor(0,maxy+1);
	return;
}

void display(){
	for(int y=0;y<maxy;y++){
		for(int x=0;x<maxx;x++){
			printf("%c",sahne[x][y]);
			printf("%c",sahne[x][y]);
			presahne[x][y]=sahne[x][y];
		}
		printf("\n");
	}
	setcursor(0,maxy+1);
	return;
}

void bound(){
	for(int i=0;i<maxy;i++){
		sahne[0][i]=219;
		sahne[maxx-1][i]=219;
	}
	for(int i=0;i<maxx;i++){
		sahne[i][0]=219;
		sahne[i][maxy-1]=219;
	}
}

void dene(){
	int olurmu;
	if(zorluk==0)olurmu=rand()%30;
	if(zorluk==1)olurmu=rand()%25+5;
	if(zorluk==2)olurmu=rand()%20+10;
	if(zorluk==3)olurmu=rand()%15+15;
	if(zorluk==4)olurmu=rand()%13+15;
	if(olurmu==26){
		int yon,uzunluk,konum;
		yon=rand()%4+1;
		uzunluk=rand()%18+5;
		if(yon==1 or yon==3)konum=rand()%(maxy-2)+1;
		else konum=rand()%(maxx-2)+1;
		if(yon==1){
			en[0][konum].push(make_pair(yon,uzunluk));
		}
		if(yon==2){
			en[konum][0].push(make_pair(yon,uzunluk));
		}
		if(yon==3){
			en[maxx-1][konum].push(make_pair(yon,uzunluk));
		}
		if(yon==4){
			en[konum][maxy-1].push(make_pair(yon,uzunluk));
		}
		enes++;
	}
}

void ilerle(){
	for(int y=0;y<maxy;y++){
		for(int x=0;x<maxx;x++){
			while(en[x][y].size()){
				int yon,uz;
				yon=en[x][y].front().first;
				uz=en[x][y].front().second;
				en[x][y].pop();
				if(!uz)continue;
				if(yon==1){
					if(x==maxx-2){
						yeden[x][y].push(make_pair(1,uz-1));
					}
					else{
						yeden[x+1][y].push(make_pair(1,uz));
					}
				}
				if(yon==2){
					if(y==maxy-2){
						yeden[x][y].push(make_pair(2,uz-1));
					}
					else{
						yeden[x][y+1].push(make_pair(2,uz));
					}
				}
				if(yon==3){
					if(x==0){
						yeden[x][y].push(make_pair(3,uz-1));
					}
					else{
						yeden[x-1][y].push(make_pair(3,uz));
					}
				}
				if(yon==4){
					if(y==0){
						yeden[x][y].push(make_pair(4,uz-1));
					}
					else{
						yeden[x][y-1].push(make_pair(4,uz));
					}
				}
			}
		}
	}
}

void aktar(){
	for(int y=0;y<maxy;y++){
		for(int x=0;x<maxx;x++){
			while(yeden[x][y].size()){
				int yon,uz;
				yon=yeden[x][y].front().first;
				uz=yeden[x][y].front().second;
				yeden[x][y].pop();
				en[x][y].push(make_pair(yon,uz));
			}
		}
	}
}

void uzat(){
	for(int y=0;y<maxy;y++){
		for(int x=0;x<maxx;x++){
			while(en[x][y].size()){
				int yon,uz;
				yon=en[x][y].front().first;
				uz=en[x][y].front().second;
				en[x][y].pop();
				if(yon==1){
					for(int i=x;i>x-uz and i>0;i--){
						bars[i][y]=1;
					}
				}
				if(yon==2){
					for(int i=y;i>y-uz and i>0;i--){
						bars[x][i]=1;
					}
				}
				if(yon==3){
					for(int i=x;i<x+uz and i<maxx-1;i++){
						bars[i][y]=1;
					}
				}
				if(yon==4){
					for(int i=y;i<y+uz and i<maxy-1;i++){
						bars[x][i]=1;
					}
				}
				yeden[x][y].push(make_pair(yon,uz));
			}
		}
	}
}

void ciz(){
	for(int y=0;y<maxy;y++){
		for(int x=0;x<maxx;x++){
			if(bars[x][y]) sahne[x][y]=178;
			else sahne[x][y]=' ';
		}
	}
}

void win(){
	g.push(make_pair(zorluk,enes));
	system("title :)");
	system("color 2F");
	Sleep(1500);
	renk();
	mainmenu();
}

void lose(){
	g.push(make_pair(zorluk,enes));
	system("title :/");
	system("color 4F");
	printf("\a");
	Sleep(1500);
	renk();
	mainmenu();
}

void afk(){
	g.push(make_pair(zorluk,-1));
	system("cls");
	system("title AFK :/");
	system("color 4F");
	printf("\a");
	cout<<"OTURMAYA MI GELDIN ?\n\n";
	cout<<"Bir yerde haddinden fazla bekledigin icin hukmen kaybettin :/\n\n";
	cout<<"Menuye donmek icin bir tusa basiniz...\n";
	while(1){
		input(tuslar);
		for(int i=0;i<256;i++){
			if(tuslar[i]){
				Sleep(100);
				renk();
				mainmenu();
				return;
			}
		}
	}
}

void aha(){
	g.push(make_pair(zorluk,-1));
	system("cls");
	system("title YASAK :/");
	system("color 4F");
	printf("\a");
	cout<<"Yasak seyler yaptigin icin hukmen kaybettin :/";
	Sleep(2500);
	renk();
	mainmenu();
}

void oyun(){
	clear(0);
	srand(time(NULL));
	if(zorluk==0)w=5;
	if(zorluk==1)w=10;
	if(zorluk==2)w=30;
	if(zorluk==3)w=50;
	if(zorluk==4)w=60;
	system("cls");
	invis(0);
	xer=24;
	yer=12;
	pre=0;
	display();
	while(1){
		if(clock()-pre > 200 and pre)aha();
		pre=clock();
		if(zorluk==0)Sleep(50);
		if(zorluk==1)Sleep(37);
		if(zorluk==2)Sleep(25);
		if(zorluk==3)Sleep(15);
		if(zorluk==4)Sleep(10);
		clear(1);
		if(enes<ec and !w)dene();
		else {
			if(!enes)w--;
			else w++;
		}
		ilerle();
		aktar();
		uzat();
		aktar();
		ciz();
		bound();
		sahne[xer][yer]=178;
		tusoku();
		timer++;
		setcursor(0,0);
		dplay();
		kalma[xer][yer]+=12;
		dus();
		if(bars[xer][yer]){
			lose();
			break;
		}
		if(w==70){
			win();
			break;
		}
		if(kalma[xer][yer]==2500 and zorluk>1){
			afk();
			break;
		}
		if(timer%10==1)invis(0);
		else printf("Gelen Toplam Engel: %d",enes);
	}
}

void help(){
	Sleep(100);
	system("title Arayuz_Yardimi");
	system("cls");
	cout<<"Oyun basit bir dodge atma oyunudur.\n";
	cout<<"Amaciniz yon tuslari ya da WASD ile\n";
	cout<<"Uzerinize gelen engellerden kacmak.\n";
	cout<<"Uzerinize gelecek butun engellerden de kacabilirseniz\n";
	cout<<"Oyunu kazanirsiniz.\n";
	cout<<"Ama engellerden biri size isabet ederse\n";
	cout<<"Ya da belli bir yerde haddinden fazla beklerseniz\n";
	cout<<"Oyunu kaybedersiniz.\n";
	cout<<"Iyi eglencelerr...\n\n\n";
	cout<<"Menuye donmek icin bir tusa basiniz...\n";
	while(1){
		input(tuslar);
		for(int i=0;i<256;i++){
			if(tuslar[i]){
				Sleep(100);
				mainmenu();
				return;
			}
		}
	}
}

void hakk(){
	Sleep(100);
	system("title Hakkinda");
	system("cls");
	cout<<"Author: Enes CAKIL - 24.04.2020\n\nThanks to Beste Naz YAVUZ\n\n";
	cout<<"Menuye donmek icin bir tusa basiniz...\n";
	while(1){
		input(tuslar);
		for(int i=0;i<256;i++){
			if(tuslar[i]){
				Sleep(100);
				mainmenu();
				return;
			}
		}
	}
}

void galan(){
	Sleep(100);
	system("title Son_Oyunlar");
	system("cls");
	cout<<"Son Oynadigin "<<g.size()<<" Oyunun Zorluk Seviyesi ve Kactigin Engel Sayisi:\n\n";
	while(g.size()){
		ged.push(make_pair(g.front().first,g.front().second));
		if(g.front().first==0)cout<<" A ";
		else if(g.front().first==1)cout<<" S ";
		else if(g.front().first==2)cout<<" D ";
		else if(g.front().first==3)cout<<" F ";
		else if(g.front().first==4)cout<<" G ";
		if(g.front().second>=0)cout<<g.front().second<<endl;
		else cout<<"Hukmen Yenik..."<<endl;
		g.pop();
	}
	while(ged.size()){
		g.push(make_pair(ged.front().first,ged.front().second));
		ged.pop();
	}
	while(1){
		input(tuslar);
		for(int i=0;i<256;i++){
			if(tuslar[i]){
				Sleep(100);
				mainmenu();
				return;
			}
		}
	}
}

void dus(){
	for(int y=0;y<maxy;y++){
		for(int x=0;x<maxx;x++){
			if(kalma[x][y]){
				kalma[x][y]-=2;
			}
		}
	}
}

void renk(){
	if(collor==0)system("color 07");
	if(collor==1)system("color 70");
	if(collor==2)system("color 1F");
	if(collor==3)system("color F1");
	if(collor==4)system("color 5F");
	if(collor==5)system("color F5");
	if(collor==6)system("color 3F");
	if(collor==7)system("color 6F");
	if(collor==8)system("color 8F");
	if(collor==9)system("color 0a");
	return;
}

void setting(){
	Sleep(100);
	system("title Ayarlar");
	system("cls");
	cout<<"Ayarlar kismindan oyunun zorlugunu, uzunlugunu ve rengini degistirebilirsiniz !!\n\n";
	cout<<"Oyun zorlugunu A,S,D,F,G tuslariyla degistirebilirsiniz.\n";
	cout<<"(A en kolay, G en zordur)\n\n";
	cout<<"Oyun uzunlugunu yon tuslariyla degistirebilirsiniz.\n\n";
	cout<<"Oyun rengini herhangi bir rakama basarak degistirebilirsiniz.\n\n";
	cout<<"Menuye donmek icin X tusuna basiniz..\n\n\n";
	cout<<"Su anda\n";
	if(zorluk==0)cout<<"Zorluk: A\n";
	if(zorluk==1)cout<<"Zorluk: S\n";
	if(zorluk==2)cout<<"Zorluk: D\n";
	if(zorluk==3)cout<<"Zorluk: F\n";
	if(zorluk==4)cout<<"Zorluk: G\n";
	cout<<"Uzunluk: "<<ec<<endl;
	cout<<"Renk: "<<collor<<endl;
	while(1){
		input(tuslar);
		for(int i=0;i<256;i++){
			if(tuslar[i]){
				if(tuslar[int('&')]){//ust
					ec++;
					setcursor(9,14);
					if(ec>1000)ec=1000;
					cout<<ec<<"   ";
					Sleep(100);
				}
				else if(tuslar[int('(')]){//alt
					ec--;
					setcursor(9,14);
					if(ec<5)ec=5;
					cout<<ec<<"   ";
					Sleep(100);
				}
				else if(tuslar[39]){//sag
					ec+=100;
					setcursor(9,14);
					if(ec>1000)ec=1000;
					cout<<ec<<"   ";
					Sleep(100);
				}
				else if(tuslar[int('%')]){//sol
					ec-=100;
					setcursor(9,14);
					if(ec<5)ec=5;
					cout<<ec<<"   ";
					Sleep(100);
				}
				else if(tuslar[int('A')]){
					zorluk=0;
					setcursor(8,13);
					cout<<'A';
					Sleep(100);
				}
				else if(tuslar[int('S')]){
					zorluk=1;
					setcursor(8,13);
					cout<<'S';
					Sleep(100);
				}
				else if(tuslar[int('D')]){
					zorluk=2;
					setcursor(8,13);
					cout<<'D';
					Sleep(100);
				}
				else if(tuslar[int('F')]){
					zorluk=3;
					setcursor(8,13);
					cout<<'F';
					Sleep(100);
				}
				else if(tuslar[int('G')]){
					zorluk=4;
					setcursor(8,13);
					cout<<'G';
					Sleep(100);
				}
				else if(tuslar[int('0')] or tuslar[96]){
					collor=0;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('1')] or tuslar[int('a')]){
					collor=1;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('2')] or tuslar[int('b')]){
					collor=2;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('3')] or tuslar[int('c')]){
					collor=3;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('4')] or tuslar[int('d')]){
					collor=4;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('5')] or tuslar[int('e')]){
					collor=5;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('6')] or tuslar[int('f')]){
					collor=6;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('7')] or tuslar[int('g')]){
					collor=7;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('8')] or tuslar[int('h')]){
					collor=8;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('9')] or tuslar[int('i')]){
					collor=9;
					renk();
					setcursor(6,15);
					cout<<collor;
					Sleep(10);
				}
				else if(tuslar[int('X')]){
					Sleep(100);
					mainmenu();
					return;
				}
			}
		}
	}
}

void mainmenu(){
	renk();
	invis(0);
	system("title Grum");
	system("cls");
	cout<<"Grum Oyununa Hosgeldin :)\n\n";
	cout<<"Secenekler:\n";
	cout<<1<<": Yeni Oyun\n";
	cout<<2<<": Arayuz Yardimi\n";
	cout<<3<<": Hakkinda\n";
	cout<<4<<": Ayarlar\n";
	cout<<5<<": Cikis\n";
	if(g.size())cout<<6<<": Son Oyunlar\n";
	while(1){
		input(tuslar);
		if(tuslar[int('1')] or tuslar[int('a')]){
			oyun();
			return;
		}
		if(tuslar[int('2')] or tuslar[int('b')]){
			help();
			return;
		}
		if(tuslar[int('3')] or tuslar[int('c')]){
			hakk();
			return;
		}
		if(tuslar[int('4')] or tuslar[int('d')]){
			setting();
			return;
		}
		if(tuslar[int('5')] or tuslar[int('e')]){
			system("cls");
			system("title Bye");
			cout<<"Gorusmek uzere...\n";
			return;
		}
		if(g.size() and (tuslar[int('6')] or tuslar[int('f')])){
			galan();
			return;
		}
	}
}

int main(){
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),renk1*16+renk2);
	collor=0;
	ec=20;
	zorluk=0;
	mainmenu();
}
