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
 	list<Rekreativac*> pomL=Rekreativac::sviRekreativci();
		  list<Rekreativac*>::iterator si;
		  for(si=pomL.begin();si!=pomL.end();si++) (*si)->odmor(200).voznja().voznja(200);
        ispis();



//ana 201 1180
//branko 210 1148
//goran 205 1359
//jana 205 1159
//mate 210 948
 }
return 0;
}
