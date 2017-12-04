#include <list>
#include <string>

#include "funkcije.h"
#include <iostream>
#define INTO(V,P) V(P,P+sizeof(P)/sizeof(*P))
using namespace std;

template<class T>
void ispisi(T kont){
    typename T::iterator i;
    for(i=kont.begin();i!=kont.end();++i)
        cout<<'['<<*i<<']';
    cout<<endl;
}

int main(){
    string a[]={"hokus","pokus","","abrakadabra",""};
    INTO(list<string> l1,a);
    ispisi(l1);
    ispisi(evolve(l1));
    string b[]={"hokus","pokus","","abrakadabra"};
    INTO(list<string> l2,b);
    ispisi(l2);
    ispisi(evolve(l2));
    return 0;
}
