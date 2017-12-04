#include<iostream>
#include<list>
#include"rekreativac.h"

using namespace std;

void ispis(){
 list<Rekreativac*> pomL=Rekreativac::sviRekreativci();
 list<Rekreativac*>::iterator si;
 for(si=pomL.begin();si!=pomL.end();si++) cout<<(**si).ime()<<" "<<(*si)->pozicija()<<" "<<(*si)->energija()<<endl; 
}


void ispis( Rekreativac& a){cout<<a.ime()<<" "<<a.pozicija()<<" "<<a.energija()<<endl; }


int main(){
	Biciklist mate("mate", 800 );Biciklist branko("branko"); Roler goran("goran",1200);Rekreativac ana("ana");
        
	{Roler jana("jana");
         }

ispis();
//ana 0 1000
//branko 0 1000
//goran 0 1200
//mate 0 800
return 0;
}
