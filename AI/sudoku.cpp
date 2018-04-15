#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <string>

using namespace std;


int main()
{
	int ulaz[9][9]; //matrica sa 0 i 1 gdje 1 stoji na poziciji na kojoj je ulazni broj koji nesmije mijenjati poziciju
	int stanje[9][9]; // aktualna matrica sudokua
	int cijena[9][9]; // matrica cijena za stanje
	int tempStanje[9][9]; // privremeno stanje, koristi se u MCMC
	int tempCijena[9][9]; // privremena cijena, koristi se u MCMC
	int novoStanje[9][9]; // matrica novog stanja za iducu iteraciju u MCMC
	int novaCijena[9][9]; // matrica cijena za novoStanje
	int faliBrojeva[9] // brojaci koliko je kojih brojeva na ulazu, broj i se sprema na index i-1
	
	//postavljanje pocetnih nizova u pocetno stanje
	for(int i=0;i<9;++i) faliBrojeva[i]=9;		//fali 9 instanci svakog broja na pocetku		
	for(int i=0;i<9;++i) for(int j=0;j<9;++j) { ulaz[i][j]=0; stanje[i][j]=-1 ;} //-1 oznacava da je polje prazno 
	
	//ucitavanje sudoku tablice iz ulaza i postavljanje odg vrijednosti
	ifstream in("sudokuUlaz.txt");
	if(in.is_open())
	{
		for(int i=0; i<9 ; ++i){
			string linija;
			getLine(in,linija);
			for(int j=0; j<9; ++j){
				if(linija[j] != '.'){		//ako polje na ulazu nije prazno postavi odg pozicije u pocetnim matricama
				int broj= linija[j];		//konverzija char u int
				stanje[i][j]= broj;
				ulaz[i][j]= 1
				faliBrojeva[broj-1]--;      //netreba nista ako je . jer je vec ostavljeno u pocetno prije
				}											
			}
		}
	}else{ cout<<"nije se uspio otvorit sudokuUlaz.txt"<<endl; exit(-1); }
	
	for(int i=0; i<9; ++i) { for(int j=0;j<9;++j) cout<<stanje[i][j]<<" "; }cout<<endl; cout<<endl;
	for(int i=0; i<9; ++i) { for(int j=0;j<9;++j) cout<<ulaz[i][j]<<" "; }cout<<endl; cout<<endl;
	for(int i=0;i<9;++i) cout<<i+1<<":"<<faliBrojeva[i];
	return 0;
	};
