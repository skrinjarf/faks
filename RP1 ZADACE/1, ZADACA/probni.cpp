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

cout << p.dodaj_emisiju(emisija("prvi film", 9, 30, 10, 30, "film","htv1")); // 1
cout << p.dodaj_emisiju(emisija("prvi film", 11, 30, 11, 35, "film","htv1")); // 1

}
