#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

int main()
{
    int p;
    cin>>p;
    for(int j=0;j<p;j++)
    {
        int m,n;
        cin>>m>>n;
        long int brojac=1;
        vector<int> niz;
        int i;
        for(i=0;i<m-n;i++) niz.push_back(1); //iznimku dodaj ako bi i isao u negativno. da nije besk petlja
        for(int j=1;i<m;i++,j++)niz.push_back(j);  //nakon jedinica dodaj rastuci podniz

        //niz je napunjen u vektor, vrtit brojeve i brojanje



    }
}
