#include "table.h"
#include <iostream>
#include <cassert>

using namespace std ;

Table::Table(unsigned int n, unsigned int m)
{
    Table::data=new int*[n];
    for(unsigned int x=0;x<n;++x){

        data[x]=new int[m];
    }
    for(unsigned int x=0;x<n;++x)
             for(unsigned int y=0;y<m;++y) data[x][y]=0;

}

int & Table::operator()(unsigned int i, unsigned int j)
 {
     assert(((i<=this->nRows()) && (j<=this->nCols())));
     return this->data[i][j]

 }

int main(){return 0;}
