#include "program.h"
#include <iostream>
using namespace std;
void ispisi_program (program p) {
for (int i = 0; i < p.get_broj_emisija(); ++i) {
emisija e = p.get_emisija(i);
cout << e.get_pocetak_s() << ":" << e.get_pocetak_m() << "-" <<
e.get_kraj_s() << ":" << e.get_kraj_m() << " ";
cout << e.get_ime() << ", " << e.get_zanr() << " (" <<
e.get_kanal() << ")" << endl;
}
cout << endl;
}
int main() {
program p;
cout << p.dodaj_emisiju(emisija("prvi film", 10, 30, 11, 30, "film","htv1")); // 1
cout << p.dodaj_emisiju(emisija("reklama", 10, 29, 10, 30, "reklama","htv1")); // 1 ... kraj je tocno na pocetku filma
cout << p.dodaj_emisiju(emisija("reklama", 11, 29, 11, 31, "reklama","htv1")); // 0 ... kraj filma se preklapa s pocetkom reklame
cout << p.dodaj_emisiju(emisija("reklama", 11, 29, 11, 31, "reklama","htv2")); // 1 ... na drugom kanalu moze
cout << p.dodaj_emisiju(emisija("reklama", 11, 30, 11, 31, "reklama","htv1")); // 1
cout << p.dodaj_emisiju(emisija("liga prvaka", 20, 30, 22, 30,"sport", "htv2")); // 1
cout << p.dodaj_emisiju(emisija("lp sazeci", 22, 45, 23, 30, "sport","htv2")); // 1
cout << endl;
cout <<"prvi ispis"<<endl;
ispisi_program(p);
/*
10:30-11:30 prvi film, film (htv1)
10:29-10:30 reklama, reklama (htv1)
11:29-11:31
 reklama, reklama (htv2)
11:30-11:31
 reklama, reklama (htv1)
20:30-22:30
 liga prvaka, sport (htv2)
22:45-23:30
 lp sazeci, sport (htv2)
*/
cout << p.dodaj_emisiju(emisija("reklama", 22, 35, 22, 40, "reklama","htv2")) << endl; // 1

cout <<"drugi ispis"<<endl;
ispisi_program(p.daj_kanal("htv2"));
/*
11:29-11:31 reklama, reklama (htv2)
20:30-22:30 liga prvaka, sport (htv2)
22:45-23:30 lp sazeci, sport (htv2)
22:35-22:40 reklama, reklama (htv2)
*/

cout <<"treci ispis"<<endl;
ispisi_program(p.daj_kanal("htv3")); // nista

cout <<"cetvrti ispis"<<endl;
ispisi_program(p.daj_zanr("dokumentarac")); // nista

cout <<"peti ispis"<<endl;
ispisi_program(p.daj_zanr("reklama"));
/*
10:29-10:30 reklama, reklama (htv1)
11:29-11:31 reklama, reklama (htv2)
11:30-11:31 reklama, reklama (htv1)
22:35-22:40 reklama, reklama (htv2)
*/

cout <<"sesti ispis"<<endl;
ispisi_program(p.daj_raspon(11,30,22,45));
/*
11:29-11:31 reklama, reklama (htv2)
11:30-11:31 reklama, reklama (htv1)
20:30-22:30 liga prvaka, sport (htv2)
22:35-22:40 reklama, reklama (htv2)
*/
return 0;
}
