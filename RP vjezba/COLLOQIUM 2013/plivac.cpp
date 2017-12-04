#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;


class Plivac
{
  public:
    static vector<Plivac*> data;
    int pos,time;
    string name;
    int broj_utrke,broj_plivaca;

    friend void SimulirajUtrku(double sati,int brojUtrke);
    friend void rezultatUtrke(int brojUtrke);



    Plivac():pos(0),time(0),name(""){}



   virtual  string ime()=0;
   virtual  int polozaj()=0;
   virtual  int vrijeme()=0;
};

class Sipa:public Plivac
{
    int speed;
public:
    Sipa():Plivac(),speed(20){}
    Sipa(int broj_ribe, int broj_trke):Plivac(),speed(20){
        string s("sipa");
        broj_utrke=broj_trke; broj_plivaca=broj_ribe;
    }
       string ime(){return this->name;}
       int polozaj(){return this->pos;}
       int vrijeme(){return this->time;}
};

class Tuna:public Plivac
{
    int speed;
public:
    Tuna():Plivac(),speed(30){}
    Tuna(int broj_ribe, int broj_trke):Plivac(),speed(30){
        string s("tuna");
        broj_utrke=broj_trke; broj_plivaca=broj_ribe;

    }
    string ime(){return this->name;}
    int polozaj(){return this->pos;}
    int vrijeme(){return this->time;}
};

void SimulirajUtrku(double sati,int brojUtrke)
{
    double pocetni_sati=0;
    int redni_broj=1;
    for(pocetni_sati=0;pocetni_sati<=sati;pocetni_sati+=0.5,redni_broj++)
    {
        Plivac::data.push_back(new Sipa(redni_broj,brojUtrke)); Plivac::data.push_back( new Tuna(redni_broj,brojUtrke));
        for(int i=0;i<Plivac::data.size();i++)//povecanje ostalih riba
        {
            if (Plivac::data[i].broj_utrke==brojUtrke)
            {
                Plivac::data[i].pos+=(Plivac::data[i].speed/2);
                if(pocetni_sati%1==0)Plivac::data[i].time+=1;
            }
        }
    }
}

void rezultatUtrke(int brojUtrke)
{
 for(int i=0;i<data.size();i++);
}

vector<Plivac*> Plivac::data;


int main()
{

}
