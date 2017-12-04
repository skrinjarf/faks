#include<string>
#include<iostream>

using namespace std;

int main()
{
    string s;
    cin>>s;

    int count=0;
    int velicina=s.size();

    if(velicina!=0){
            count=1;
             for(int i=0;i<velicina;i++)
             {
                 if( ((int)s[i])>=65 && ((int)s[i])<=90 )count++;  //po asciiu su velika slova izmedu 65 i 90
             }
     }
    cout<<count;


}
