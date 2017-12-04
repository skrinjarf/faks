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
    into(g['3'],"56");
    into(g['1'],"346");
    into(g['8'],"416");
    into(g['7'],"1");
    into(g['9'],"79");
    into(g['2'],"269");
    for(char i='1';i<='9';++i)ispisi(reach(g,i));
    map<char,set<char> > g2;
    into(g2['a'],"b");
    into(g2['b'],"cd");
    into(g2['d'],"ad");
    into(g2['e'],"d");
    into(g2['g'],"");
    for(char c='a';c<'h';c++)ispisi(reach(g2,c));
    return 0;
}
