#include <string>
#include <set>
#include <map>

#include "funkcije.h"
#include <iostream>
using namespace std;

template<class T>
void ispisi(T kont){
    typename T::iterator i;
    for(i=kont.begin();i!=kont.end();++i)
        cout<<'['<<*i<<']';
    cout<<endl;
}
template<class T>
void into(T& kont,string s){
    T svi(s.begin(),s.end());
    kont=svi;
}

int main(){
    map<char,set<char> > g;
    into(g['3'],"8t");
    into(g['5'],"e");
    into(g['7'],"e8");
    into(g['8'],"9");
    into(g['e'],"29t");
    into(g['r'],"hz");
    ispisi(reach(g,'2'));
    ispisi(reach(g,'3'));
    ispisi(reach(g,'5'));
    ispisi(reach(g,'7'));
    ispisi(reach(g,'8'));
    ispisi(reach(g,'9'));
    ispisi(reach(g,'t'));
    ispisi(reach(g,'e'));
    ispisi(reach(g,'r'));
    return 0;
}
