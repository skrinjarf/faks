#include<string>
#include<vector>
#include<iostream>

using namespace std;

int main()
{
    vector<int> cijene;
    int n=0;


    cin>>n;

    for(int i=0;i<n;i++)
    {

        int temp=1;   //prvo slovo se uvjek treba dodat
        string s,p;
        cin>>s;
        if(s.size()==0){
            cijene.push_back(0); continue;
        }
        p+=s[0];     //prvo se uvjek dodaje, brojac je vec povecan

        for(int j=1; j<s.size();j++)
        {
          bool flag=false;
          char c=s[j];
          for(int k=0;k<p.size();k++)         //treba vidjet dal se moze u string ljepit char sa +=
          {
             if(p[k]==c){ p+=c; flag=true; break;}
          }

          if(!flag){
              p+=c; temp++;
          }

        }

        //prosao sam kroz cijeli string i nasao cjenu u temp;

        cijene.push_back(temp);

    }
    //sve cijene su u vektoru, ISPIS!!

    for(int i;i<cijene.size();i++) cout<<cijene[i]<<endl;

return 0;
}
