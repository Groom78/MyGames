#include<bits/stdc++.h>
#include<random>
using namespace std;
#define int long long int
#define pb push_back
#define ff first
#define ss second
#define nl '\n'
#define waitfor junk=getchar();

char junk;
bool easter_egg = 0, easter_arda = 0;
vector<double> prev_bet(37,0);
int prev_bet_val,initial_budget,temp,a,b,renkarda_cnt=0,kpcnt=0,kpmax=1,ucnt=0;
string renkof[37];
vector<pair<pair<int,string>,int> >lasts;
int wh[37]={0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26};

void son_gelenler(){
    if(lasts.size()==0){
        cout << "Henuz hic oyun oynanmadi" << nl;
        waitfor;
        return;
    }
    if(renkarda_cnt>0 and easter_arda){
        cout << renkarda_cnt << " defa RENK ARDA yapıldı" << nl;
        cout << ucnt << " defa ULTRA MEGA RENK ARDA yapıldı" << nl;
        
    }
    if(lasts.size()>20){
        cout << "Oynanan " << lasts.size() << " adet oyundan son 20 tanesinin sonuclari:" << nl;
        for(int i=lasts.size()-1;i>lasts.size()-21;i--){
            cout << i+1 << ". " << lasts[i].ff.ff << " " << lasts[i].ff.ss << " " <<lasts[i].ss<<"$ Bakiye" << nl;
        }
    }
    else{
        cout << "Oynanan " << lasts.size() << " adet oyunun sonuclari:" << nl;
        for(int i=lasts.size()-1;i>=0;i--){
            cout << i+1 << ". " << lasts[i].ff.ff << " " << lasts[i].ff.ss << " " <<lasts[i].ss<<"$ Bakiye" << nl;
        }
    }
    waitfor;
    return;
}

void prec(){
    renkof[0] = "yesil";
    for(int i=1;i<=36;i+=2){
        renkof[wh[i]]="kirmizi";
    }
    for(int i=2;i<=36;i+=2){
        renkof[wh[i]]="siyah";
    }
}

void kp(int& budget){
    if(budget){
        cout << "Daha batmadin aq" << nl;
        waitfor;
        return;
    }
    if(kpcnt>=kpmax){
        cout << "Kayip bonusu zaten alindi" << nl;
        waitfor;
        return;
    }
    kpcnt++;
    if(kpcnt == 2 and ucnt>0){
        cout <<"ULTRA MEGA RENK ARDA!!! Tek seferlik fazladan %100 bonus hakkiniz bulundu" << nl;
        budget += initial_budget;
    }
    else if(kpcnt==2){
        cout <<"Renk Ardanin hatrina tek seferlik fazladan %50 bonus hakkiniz bulundu" << nl;
        budget += initial_budget/2;
    }
    else budget += initial_budget/4;
    cout << "Kayip bonusu basarili" << nl;
    cout << "Yeni bakiye: " << "$" << budget << nl;
    waitfor;
    return;
}

int rs(){
    std::mt19937 mt(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, 36);
    int random_number = distribution(mt);
    return random_number;
}

void short_guide();
void guide();

void play(int& budget){
    if(budget==0 and kpcnt>=kpmax){
        return;
    }
    bool cancel=0,renkarda;
    int x,y,curbet=0;
    double z;
    vector<double>bet(37,0);
    cout << "Bakiyeniz: " << budget << "$" << nl;
    cout << "Bahsinizi giriniz:" << nl;
    while(1){
        cin >> x;
        if(x==-5){
            return;
        }
        if(x==-4){
            short_guide();
            play(budget);
            return;
        }
        if(x==-3){
            kp(budget);
            play(budget);
            return;
        }
        if(x==-2){
            son_gelenler();
            play(budget);
            return;
        }
        if(x==-1){
            break;
        }
        if(x==1){
            cin >> y >> z;
            if(z==0){
                z=budget - curbet;
            }
            bet[y]+=z;
            curbet+=z;
        }
        if(x==2){
            cin >> y >> z;
            if(z==0){
                z=budget - curbet;
            }
            if(y==1){
                for(int i=1;i<=36;i+=2){
                    bet[wh[i]]+= (z/((double)18));
                }
            }
            if(y==2){
                for(int i=2;i<=36;i+=2){
                    bet[wh[i]]+= (z/((double)18));
                }
            }
            curbet+=z;
        }
        if(x==3){
            cin >> y >> z;
            if(z==0){
                z=budget - curbet;
            }
            if(y==1){
                for(int i=1;i<=36;i+=3){
                    bet[i] += (z/((double)12));
                }
            }
            if(y==2){
                for(int i=2;i<=36;i+=3){
                    bet[i] += (z/((double)12));
                }
            }
            if(y==3){
                for(int i=3;i<=36;i+=3){
                    bet[i] += (z/((double)12));
                }
            }
            curbet+=z;
        }
        if(x==4){
            cin >> a >> b >> z;
            if(z==0){
                z=(budget - curbet)/(2*b+1);
            }
            if(b<=0 or b>18){
                cout << "Gecersiz aralik girdiniz" << nl;
                break;
            }
            for(int i=a-b;i<=a+b;i++){
                temp = (i+37)%37;
                bet[temp]+= z;
            }
            curbet+=(z*(b*2+1));
        }
        if(x==5){
            cin >> y >> z;
            if(z==0){
                z=budget - curbet;
            }
            if(y==1){
                for(int i=1;i<=18;i++){
                    bet[i]+= (z/((double)18));
                }
            }
            if(y==2){
                for(int i=19;i<=36;i++){
                    bet[i]+= (z/((double)18));
                }
            }
            curbet+=z;
        }
        if(x==6){
            cin >> y >> z;
            if(z==0){
                z=budget - curbet;
            }
            if(y==1){
                for(int i=1;i<=36;i+=2){
                    bet[i]+= (z/((double)18));
                }
            }
            if(y==2){
                for(int i=2;i<=36;i+=2){
                    bet[i]+= (z/((double)18));
                }
            }
            curbet+=z;
        }
        if(x==7){
            cin >> z;
            if(z==0){
                z=budget - curbet;
            }
            bet[1]+= double(z/((double)12));
            bet[2]+= double(z/((double)12));
            bet[3]+= double(z/((double)12));
            bet[5]+= double(z/((double)12));
            bet[7]+= double(z/((double)12));
            bet[11]+= double(z/((double)12));
            bet[13]+= double(z/((double)12));
            bet[17]+= double(z/((double)12));
            bet[19]+= double(z/((double)12));
            bet[23]+= double(z/((double)12));
            bet[29]+= double(z/((double)12));
            bet[31]+= double(z/((double)12));
            curbet += z;
        }
        if(x==8){
            cin >> z;
            if(z==0){
                z=budget - curbet;
            }
            bet[1]+= double(z/((double)6));
            bet[4]+= double(z/((double)6));
            bet[9]+= double(z/((double)6));
            bet[16]+= double(z/((double)6));
            bet[25]+= double(z/((double)6));
            bet[36]+= double(z/((double)6));
            curbet += z;
        }
        if(x==9){
            for(int i=0;i<=36;i++){
                bet[i]+=prev_bet[i];
            }
            curbet+=prev_bet_val;
        }
        if(x==10){
            cin >> z;
            for(int i=0;i<=36;i++){
                bet[i] = bet[i]*((double)z);
            }
            curbet*=z;
        }
        if(x==-18){
            if(easter_arda==0){
                cout << "Demek biliyosun, RENK ARDA easter egg aktif xd" << nl;
                easter_arda=1;
            }
            else if(easter_arda==1){
                cout << "RENK ARDA easter egg inaktif :(" << nl;
                easter_arda=0;
            }
        }
        if(x==-19){
            if(easter_egg==0){
                cout << "Demek biliyosun, Ceylin easter egg aktif xd" << nl;
                easter_egg=1;
            }
            else if(easter_egg==1){
                cout << "Ceylin easter egg inaktif :(" << nl;
                easter_egg=0;
            }
        }
        if(x==-23){
            cout << "Kendimi sizin kadar sevmediğim için bende easter egg yok :(" << nl;
        }
    }
    for(int i=0;i<=36;i++){
        if(bet[i] < 0){
            cout << "Gecersiz giris !" << nl;
            cout << i << " sayisinda negatif bahsiniz var." << nl;
            play(budget);
            return;
        }
    }
    if(curbet>budget){
        cout << "Parandan daha fazla bahis oynama aw mal misin" << nl;
        play(budget);
        return;
    }
    if(curbet == budget and curbet){
        cout << "REST !!!" << nl;
    }
    cout << "Bahisler kabul edildi" << nl;
    cout << "Bahis: " << curbet << "$" << nl;
    cout << "Sonucu gormek icin ENTERa basiniz" << nl;
    waitfor;
    waitfor;
    int sayi = rs();
    cout << "Gelen sayi: " << sayi <<" ";
    cout << renkof[sayi];
    if(sayi==15)cout << " (Cagatay)";
    if(sayi==18)cout << " (Arda)";
    if(sayi==19)cout << " (Ceylin <3)";
    if(sayi==23)cout << " (Enes)";
    cout<< nl;
    if(curbet==0){
        cout << "Eli bos gectiniz" << nl;
    }
    else if(bet[sayi]*((double)36)==0){
        cout << "Kaybettiniz" << nl;
    }
    else if(bet[sayi]*((double)36) > 3*curbet){
        cout << "Buyuk oynadiniz ve " << bet[sayi]*((double)36) << "$ kazandiniz !!!" << nl;
    }
    else cout << bet[sayi]*((double)36) << "$ kazandiniz" << nl;
    if(sayi == 19 and bet[19]==0 and easter_egg){
        cout << "Neden 19 basmadin mal" << nl;
    }
    else if(sayi == 19 and bet[19] and easter_egg){
        cout << "Ceylin Easter egg sayesinde fazladan " << bet[sayi]*((double)36) <<"$ kazandiniz wp" << nl;
        budget += bet[sayi]*((double)36);
    }
    renkarda=1;
    if(sayi>0 and curbet>0){
        for(int i=0;i<=36;i++){
            if(renkof[i]==renkof[sayi] and bet[i]!=bet[sayi])renkarda=0;
            else if(renkof[i]!=renkof[sayi] and bet[i]>0)renkarda=0;
        }
    }
    else{
        renkarda=0;
    }
    if(renkarda and curbet*2>=(budget) and easter_arda){
        renkarda_cnt++;
        if(sayi==18){
            renkarda_cnt--;
            cout << "ULTRA MEGA ";
            ucnt++;
        }
        if(renkarda_cnt>=3 or ucnt){
            kpmax=2;
        }
        cout << "RENK ARDAAA" << nl;
    }
    
    for(int i=0;i<=36;i++)prev_bet[i]=bet[i];
    prev_bet_val=curbet;
    budget-=curbet;
    budget += bet[sayi]*((double)36);
    lasts.pb({{sayi,renkof[sayi]},budget});
    play(budget);
}

void solve(){
    prec();
    guide();
    int budget;
    cout << "Bakiye Giriniz($): ";
    cin >> budget;
    if(budget<=0){
        cout << "Aynen mq keli bi akıllı sensin" << nl;
        waitfor;
        return;
    }
    if(budget == 1){
        cout << "Expert mod acik" << nl;
    }
    initial_budget = budget;
    play(budget);
    
    if(budget){
        if(budget > initial_budget){
            cout << fixed << setprecision(3) << "Tebrikler, paranizi " << double(budget)/double(initial_budget) <<" katina katladiniz." << nl;
            cout << fixed << setprecision(3) << "Bunu basarma ihtimaliniz yalnizca %" << 100*double(initial_budget)/double(budget)<<" idi." << nl;
            cout << "(Eger yesil 0 ve kayip bonusu hesaba dahil edilmezse)" << nl;
        }
        cout << nl << budget <<"$ ile oyundan ayrildiniz." << nl;
        cout <<"Gule gule gotunuze sokun." << nl;
        cout <<"Makineciler hicbir seyi hak etmiyor bu arada..." << nl; 
    }
    else{
        cout << nl <<"Battiniz efendim xd" << nl;
        cout << "Her zaman kumari oynatan kazanir Kilic" << nl;
    }
    waitfor;
    return;
}

int32_t main(){
    solve();
    return 0;
}

void short_guide(){
    cout << "Masadaki sayilar sirasiyla: " << nl;
    cout << "0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26" << nl << nl;
    cout << "1 a x (a sayisina x oynar)" << nl;
    cout << "2 1 x (kirmizi), 2 2 x (siyah)" << nl;
    cout << "3 1 x (Sol), 3 2 x (Orta), 3 3 x (Sag)" << nl;
    cout << "4 a b x (a sayisinin b sagi ve b soluna x$ oynar)" << nl;
    cout << "5 1 x (1-18 arasi), 5 2 x (19-36 arasi)" << nl;
    cout << "6 1 x (Tek), 6 2 x (Cift)" << nl;
    cout << "7 x (Asal)" << nl;
    cout << "8 x (Tam Kare)" << nl;
    cout << "9 (Onceki bahsi ekler)" << nl;
    cout << "10 k (Tüm bahsinizi k ile çarpar)" << nl;
    cout << "-1 (Bahis bitir)" << nl;
    cout << "-2 (Son elleri goruntule)" << nl;
    cout << "-3 (Kayip bonusu al)" << nl;
    cout << "-4 (Bu rehberi ac)" << nl;
    cout << "-5 (Oyundan cik)" << nl;
    cout << "Devam etmek için ENTERa basınız" << nl << nl;
    waitfor;
    return;
}

void guide(){
    cout << "Her bahsin bir kodu vardır, Basa o kodu yazmalisiniz" << nl;
    cout << nl << "Masadaki sayilar sirasiyla: " << nl;
    cout << "0,32,15,19,4,21,2,25,17,34,6,27,13,36,11,30,8,23,10,5,24,16,33,1,20,14,31,9,22,18,29,7,28,12,35,3,26" << nl << nl;
    cout << "Sayi basmak istiyorsaniz: " << nl;
    cout << "1 19 23 (19'a 23$ oynar (Ceylin <3 Enes))" << nl;
    cout << "Bundan sonraki satirlarda 'x' degeri bahsinizi temsil etmektedir." << nl;
    cout << "Renk basmak istiyorsaniz:" << nl;
    cout << "2 1 x (kirmizi), 2 2 x (siyah)" << nl;
    cout << "Sutun basmak istiyorsaniz: " << nl;
    cout << "3 1 x (Sol), 3 2 x (Orta), 3 3 x (Sag)" << nl;
    cout << "(Sol Sag basarsaniz her zaman orta gelecegi kurali gecerli degildir)" << nl;
    cout << "Bolge basmak istiyorsaniz:" << nl;
    cout << "4 a b x (a sayisinin b sagi ve b soluna kadar hepsine ayri ayri x$ oynar)" << nl;
    cout << "Aralik basmak istiyorsaniz :" << nl;
    cout << "5 1 x (1-18 arasi), 5 2 x (19-36 arasi)" << nl;
    cout << "(1-12 13-24 25-36 araliklari usenmem sebebiyle eklenmemistir)" << nl;
    cout << "Tek Cift basmak istiyorsaniz:" << nl;
    cout << "6 1 x (Tek), 6 2 x (Cift)" << nl;
    cout << "Asal sayilara basmak istiyorsaniz:" << nl;
    cout << "7 x (1 sayisi asaldir, bilmiyorsaniz arastirin)" << nl;
    cout << "Tam kare sayilara basmak istiyorsaniz:" << nl;
    cout << "8 x" << nl;
    cout << "Onceki eldeki bahsinizi eklemek istiyorsaniz" << nl;
    cout << "9" << nl;
    cout << "Bahsinizi bir k sayisi ile carpmak istiyorsaniz" << nl;
    cout << "10 k" << nl;
    cout << "Rest atmak için bahis yerine (x yerine) 0 yaziniz" << nl;
    cout << "Bahis icin negatif sayilar yazarsaniz bi sayidaki bahsinizin o kadarini geri cekersiniz" << nl;
    cout << "Hem kirmizi, hem siyaha basmak gibi normalde kabul edilmeyen bahisler serbesttir, sonucta rulet daima kaybettirir" << nl;
    cout << "Tum bahisleri ayrı satırlara yazip, son satıra yalnızca -1 yazmalisiniz" << nl;
    cout << "Eli bos gecmek istiyorsaniz sadece -1 yazabilirsiniz. Mal olmayin." << nl;
    cout << "Son elleri goruntulemek icin -2 yaziniz" << nl;
    cout << "Kayip bonusu icin -3 yaziniz :(" << nl;
    cout << "Bu yazilarin kisa ozeti için -4 yaziniz" << nl;
    cout << "Oyundan cikmak icin -5 yaziniz" << nl;
    cout << "Oyun kisa surede yazildigindan gecersiz girdiler girmeyi denemeyiniz" << nl;
    cout << "Zaten elinize bu oyunu bozunca hicbir sey gecmicek aq" << nl;
    cout << "Oyunun tek amaci Arda'ya ruletin asla kazandirmadigini gostermektir xd" << nl;
    cout << "Dede elini bi kaldırsa offfff" << nl;
    cout << "Oyunda 2 adet easter egg bulunmaktadir, bunlari, yapimcidan ogrenebilirsiniz" << nl;
    cout << "Saatlerce ugrasip 500 satira yakin kod yazdim. Emegimin karsiligi icin bu oyunu bol bol oynayiniz :)" << nl;
    cout << nl << "Devam etmek için ENTERa basınız" << nl;
    waitfor;
    return;
}
