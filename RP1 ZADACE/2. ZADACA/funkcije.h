#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#include <list>
#include <string>
#include <set>
#include <map>

using namespace std;

list<string> evolve (list<string> e);
list<char> rlen(list<char> l);
set<char> reach(map<char,set<char> > g, char s);

#endif // FUNKCIJE_H
