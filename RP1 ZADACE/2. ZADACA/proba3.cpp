#include "funkcije.h"
#include <string>
#include <list>
#include <map>
#include <set>
#include <iostream>

using namespace std;


int main()
{
 map<char, set<char> > graf;
 set<char> temp,ispis;
         temp.insert('b');
         graf['a']=temp;        //g[a]=b

         temp.erase('b'); temp.insert('c'); temp.insert('d');
         graf['b']=temp;        //g[b]=c,d

         temp.erase('c');temp.insert('a');
         graf['d']=temp;        //g[d]=a,d

         temp.erase('a');
         graf['e']=temp;         //g[e]=d

         temp.erase('d');
         graf['f']=temp;
         graf['c']=temp;         //g[f]=null, g[c]=null ali ima brid koji dolazi u njega;

  ispis=reach(graf,'b');
  set<char>::iterator i;
  for(i=ispis.begin();i!=ispis.end();++i)
      cout<<endl<< (*i)<<" ";

 return 0;
}
