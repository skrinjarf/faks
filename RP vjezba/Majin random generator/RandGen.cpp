#include <iostream>
#include <stdlib.h>
#include <list>
#include <string>
#include <time.h>

using namespace std;


void NapuniListu(list<string>& ljudi)
{
    cout<<"enter names and surnames from which you want to generate random people. "<<endl;
    cout<<"press enter after each person."<<endl;
    cout<<"type 'stop' and press enter to end of input"<<endl;

    string ime,prezime;
    while(1)
    {
        cin>>ime;
        if(ime=="stop") return;
        cin>>prezime;
        if(prezime=="stop") return;
        ime+=" ";
        ime+=prezime;
        ljudi.push_front(ime);
    }

}


int main()
{
    cout<<"_____Welcome to RandomGenerator by Skrinjar_____"<<endl;

    list<string> ljudi,odabrani;
    srand(time(NULL));
    NapuniListu(ljudi);
do{
      int pozicija= rand() % ljudi.size();
      list<string>::iterator i=ljudi.begin();

      for(int j=0;j!=pozicija ; ++i,++j);
      cout<<"And the winner is..: "<<(*i)<<"!"<<endl<<endl<<endl;
      ljudi.erase(i);
      cout<<endl<<endl<<"to select another winner press 1, to end press 0"<<endl;
      int odluka;
      cin>>odluka;
      cout<<endl;
      if(!odluka) break;
      if(ljudi.begin()== ljudi.end())
      {
        cout<<"you have selected every person, exiting program...";
        break;
      }
}while(1);

   return 0;
}
