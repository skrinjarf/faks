#include <string>
#include <list>
#include <iostream>
#include "funkcije.h"

using namespace std;

int main()
{
   list<char> l,k;
   list<char>::iterator i=l.end();
   l.insert(i,'a');
   l.insert(i,'a');
   l.insert(i,'a');
   l.insert(i,'a');
   l.insert(i,'a');

   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');

   l.insert(i,'*');


   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'b');
   l.insert(i,'*');
   l.insert(i,'*');
   l.insert(i,'*');
   l.insert(i,'*');
   l.insert(i,'*');
   l.insert(i,'*');
   l.insert(i,'*');
   l.insert(i,'*');


   l.insert(i,'8');
   l.insert(i,'8');
   l.insert(i,'8');
   l.insert(i,'8');

   l=rlen(l);
   cout<<endl<<k.size()<<" l:"<<l.size()<<endl;
   for(i=l.begin();i!=l.end();++i) cout<<*i<<" ";
return 0;
}
