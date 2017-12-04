#include<string>
#include<vector>
#include<iostream>

using namespace std;

int main()
{
    string s;
    cin>>s;
    long int brojac=0;
    if(s.size()<4){ cout<<0;return 0;}

    for(int a=0;a<s.size();a++)
    {
        for(int b=a+1;b<s.size();b++)
        {
            for(int c=b+1;c<s.size();c++)
            {

                if(s[b] != s[c]) continue;
                for(int d=c+1;d<s.size();d++)
                {
                    if(s[a]==s[d] && s[c]==s[b]) brojac=(brojac + 1)%1000000007 ;
                }
            }
        }
    }
    cout<<brojac;
    return 0;
}


//presporo nadi brzi kod online
