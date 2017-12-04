#include <iostream>
#include <string>
using namespace std;

template<class Type> struct karta
{
   Type vrijednost;
   string boja;
};

template <class Type> struct hand
{
    karta<Type> niz[50];
    int vrh;
    hand(Type x, string b)
    {
       niz[0].vrijednost=x;niz[0].boja=b;vrh=0;
    }
    ~hand()
    {
        for(int i=0;i<vrh;++i) cout<<niz[i].vrijednost<<niz[i].boja<<endl;
    }
    int nova (Type x, string b)
    {
        if(vrh== 49)return 0;
        int iste=0;
        for(int i=0; i<vrh;++i)if (niz[i].vrijednost==x) iste++;
        if(iste==4) return 0;
        niz[++vrh].vrijednost=x;niz[vrh].boja=b;return 1;
    }
    int odbaci(Type x, string b )
    {
        int i;
        bool nasao=false;
        for(i=0; i<vrh;++i) if(niz[i].vrijednost==x && niz[i].boja==b) {nasao=true; break;}
        if(nasao)
        {
            for(int j=i+1;j<vrh;j++) niz[j-1]=niz[j];
            vrh--;
            return 1;
        }
        return 0;
    }
    Type najjaca(string b)
    {
         Type max;
         bool prvi=true;
         for(int i=0;i<vrh;++i) if(niz[i].boja==b)
         {
             if(prvi || niz[i].vrijednost>max) max=niz[i].vrijednost;

         }
        return max;
    }

};

int main()
{

}
