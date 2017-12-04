#include "funkcije.h"
#include <string>
#include <list>
#include <map>
#include <set>
using namespace std;

list<string> evolve(list<string> e)
{
    if(e.empty()) return e;
    int suma=0;
    list<string>::iterator i;
    for(i=e.begin();i!=e.end();++i)
    {
        suma+= i->size();
    }
    double prosjek=suma/e.size() ;

    for(i=e.begin();i!= e.end();)
    {
        if( i->size() < prosjek)
        {
            list<string>::iterator temp=i;
            ++temp; e.erase(i);  i=temp;
        }else ++i;
    }

    for(i=e.begin();i!=e.end();)
    {
        string temp=*i;
        ++i;
        while(temp.size()!=0)
        {
            temp.erase(0,1);
            e.insert(i,temp);   //treba vidjet da li se j pomakne u naprijed kod dodavanja ili pokazuje na el na koji dodaje
        }
    }
return e;
}

list<char> rlen(list<char> l )
{
    list<char>::iterator i,j,k;

    char c;
    i=l.begin();
    while(i!=l.end())
    {
       int brojac=0;
       for(c=(*i);(i!=l.end()) && ((*i)==c) && (brojac<9);++i,++brojac) ;
       if((brojac>=4)&&(c!='*'))
       {
          k=j=i;
          for(int temp=0;temp<brojac-1;temp++) --j;
          l.erase(j,i);
          l.insert(k,'*');
          l.insert(k,brojac + '0' );
          i=k;
       }
       if((brojac>=1)&&(brojac<=9)&&(c=='*'))
       {
           k=j=i;
           for(int temp=0;temp<brojac-1;temp++) --j;
           l.erase(j,i);
           l.insert(k,'*');
           l.insert(k,brojac + '0');
           i=k;
       }
   }
  return l;
}

set<char> globalni;
set<char> reach(map<char, set<char> > g, char s)
{
        set<char> lokalni;
        set<char>::iterator i;
        if(g.find(s)==g.end()) return lokalni;        //slucaj kada s nije u grafu vraca prazan skup
        if(globalni.find(s) != globalni.end()) return globalni;    //ako je s vec u globalnom tada sam u petlji ili ciklusu
        globalni.insert(s);                               //s ne postoji u globalnom setu, nije petlja

        set<char> susjedi= g[s];
        for(i=susjedi.begin();i!=susjedi.end();++i) reach(g,*i);

        return globalni;
}

