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
 	 cout<<jana.voznja().sudar(mate)<<endl;
	 cout<<goran.voznja().sudar(jana)<<endl;
	 cout<<branko.izguraj(ana)<<endl;
	 cout<<branko.sudar(ana)<<endl;
	 cout<<ana.odmor(10).sudar(branko)<<endl;


//0
//1
//1
//0
//1
 }
return 0;
}
