#include "program.h"
#include <iostream>
#include <string.h>

using namespace std;

emisija::emisija(){}

emisija::emisija(char *_ime, int poc_s, int poc_m, int kraj_s, int kraj_m, char *_zanr, char *_kanal)
{
    strcpy(ime, _ime);
    strcpy(zanr, _zanr);
    strcpy(kanal, _kanal);
    emisija::poc_m=poc_m;
    emisija::poc_s=poc_s;
    emisija::kraj_m=kraj_m;
    emisija::kraj_s=kraj_s;
}

char* emisija::get_ime()
{
    return ime;
}
char* emisija::get_kanal()
{
    return kanal;
}
char* emisija::get_zanr()
{
    return zanr;
}
int emisija::get_kraj_m()
{
    return kraj_m;
}
int emisija::get_kraj_s()
{
    return kraj_s;
}
int emisija::get_pocetak_m()
{
    return poc_m;
}
int emisija::get_pocetak_s()
{
    return poc_s;
}


program::program()
{
   zadnji=-1;

}

int program::get_broj_emisija()
{
    return zadnji+1;
}
emisija program::get_emisija(int index)
{
    return data[index];
}

program program::daj_kanal(char *kanal)
{
    program temp;
    int j=0;
    for(int i=0; i<=program::zadnji; ++i)
    {
        emisija tempE=program::data[i];
        if(!strcmp(tempE.kanal, kanal))
        {
            strcpy(temp.data[j].ime, tempE.get_ime());
            strcpy(temp.data[j].kanal, tempE.get_kanal());
            strcpy(temp.data[j].zanr, tempE.get_zanr());
            temp.data[j].kraj_m=tempE.get_kraj_m();
            temp.data[j].kraj_s=tempE.get_kraj_s();
            temp.data[j].poc_m=tempE.get_pocetak_m();
            temp.data[j].poc_s=tempE.get_pocetak_s();
            j++;
            temp.zadnji++;
        }
    }
    return temp;
}

program program::daj_zanr(char *zanr)
{
    program temp;
    int j=0;
    for(int i=0; i<=program::zadnji; ++i)
    {
        emisija tempE=program::data[i];
        if(!strcmp(tempE.zanr, zanr))
        {
            strcpy(temp.data[j].ime, tempE.get_ime());
            strcpy(temp.data[j].kanal, tempE.get_kanal());
            strcpy(temp.data[j].zanr, tempE.get_zanr());
            temp.data[j].kraj_m=tempE.get_kraj_m();
            temp.data[j].kraj_s=tempE.get_kraj_s();
            temp.data[j].poc_m=tempE.get_pocetak_m();
            temp.data[j].poc_s=tempE.get_pocetak_s();
            j++;
            temp.zadnji++;
        }
    }
    return temp;
}

bool program::dodaj_emisiju(emisija e)
{
    if (program::zadnji >= 99) return false;
    program temp;
    temp=daj_kanal(e.kanal);
    int moze=1;
    for(int i=0; i<=temp.zadnji; i++)
    {
        int razlika_pocetak=0, razlika_kraj=0; //1 pocinje prije 2 pocinje poslije
        int razlika_poc_kraj=0,razlika_kraj_poc=0;

        if(temp.data[i].get_pocetak_s()-e.get_pocetak_s()>0)
        {
            razlika_pocetak=1;
        }else if((temp.data[i].get_pocetak_s()-e.get_pocetak_s()==0) && (temp.data[i].get_pocetak_m()-e.get_pocetak_m()>0))
        {
            razlika_pocetak=1;
        }else razlika_pocetak=2;

                if(temp.data[i].get_kraj_s()-e.get_kraj_s()>0)
                {
                    razlika_kraj=1;
                }else if((temp.data[i].get_kraj_s()-e.get_kraj_s()==0) && (temp.data[i].get_pocetak_m()-e.get_pocetak_m()>0))
                {
                    razlika_kraj=1;
                }else razlika_kraj=2;
                        if(temp.data[i].get_pocetak_s()-e.get_kraj_s()>0)
                        {
                            razlika_poc_kraj=1;
                        }else if((temp.data[i].get_pocetak_s()-e.get_kraj_s()==0) && (temp.data[i].get_pocetak_m()-e.get_kraj_m()>=0))
                        {
                            razlika_poc_kraj=1;
                        }else razlika_poc_kraj=2;

                               if(temp.data[i].get_kraj_s()-e.get_pocetak_s()>0)
                               {
                                   razlika_kraj_poc=1;
                               }else if((temp.data[i].get_kraj_s()-e.get_pocetak_s()==0) && (temp.data[i].get_kraj_m()-e.get_pocetak_m()>0))
                               {
                                   razlika_kraj_poc=1;
                               }else razlika_kraj_poc=2;


           if((razlika_pocetak==1) && (razlika_poc_kraj==2))
           {
               moze=0; break;
           }
           if((razlika_kraj==2) && (razlika_kraj_poc==1))
           {
               moze=0;break;
           }
           if((razlika_pocetak==2)&&(razlika_kraj==1))
           {
               moze=0;break;
           }

    }
    if(moze)
    {
        program::data[++program::zadnji]=e;
        return true;
    }
    return false;
}

program program::daj_raspon(int poc_s, int poc_m, int kraj_s, int kraj_m)
{
     program zavrsni;
     int pocetak=60 * poc_s + poc_m;
     int kraj=60 * kraj_s + kraj_m;
     int j=0;
     for(int i=0; i<=program::zadnji;i++)
     {
         int temppoc=program::data[i].poc_s * 60 + program::data[i].poc_m;
         int tempkraj=program::data[i].kraj_s * 60 + program::data[i].kraj_m;

         if((pocetak>=temppoc)&&(tempkraj-pocetak>0))
         {
             zavrsni.dodaj_emisiju(program::data[i]);
             continue;
         }
         if((kraj<=tempkraj)&&(kraj - temppoc >0))
         {
             zavrsni.dodaj_emisiju(program::data[i]);
             continue;
         }
         if((pocetak<=temppoc)&&(kraj>=tempkraj))
         {
            zavrsni.dodaj_emisiju(program::data[i]);
            continue;
         }
     }
    return zavrsni;
}

