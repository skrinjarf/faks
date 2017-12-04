#include "vn.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>  ///za atoi mi treba stdlib iz C-a u Statistics::send
#include <cmath>   ///za sinus

using namespace std;

void BusController::insert(Instrument * p)
{
    mDevices.push_back(p);
    p->setPort(mDevices.size()-1);  ///1 element ima index 0
    cout<<"izvršeno je ubacivanje instrumenta "<<p->deviceName()<<endl;
}

void BusController::send(unsigned int adress, string cmd)
{
    if(adress>=mDevices.size()) throw runtime_error("ne postoji instrument na danoj adresi!"); /// da lie > ili >= ?
    mDevices[adress]->send(cmd);
}

float BusController::receive(unsigned int adress)
{
    if(adress>=mDevices.size()) throw runtime_error("ne postoji instrument na danoj adresi!"); /// da lie > ili >= ?
    return mDevices[adress]->receive();
}

DataFast::DataFast(BusController & bus):mCntrl(bus),mMode(0)
{
    bus.insert(this);   ///to postavlja port
    mStartTime= chrono::system_clock::now();
}

void DataFast::setMode(int mod){mMode=mod;}

float DataFast::receive()   ///vraca vremensku razliku;
{
    chrono::duration<double> trajanje = chrono::duration_cast<chrono::microseconds>( chrono::system_clock::now() - mStartTime );
    if(mMode == 0)
    {
        return sin(0.175 * trajanje.count());
    }else if (mMode == 1)
    {
        return sin(2*0.175 * trajanje.count());
    }
    return 0;
}
void DataFast::send(string s){}; ///ne radi nista

Statistics::Statistics(BusController & bus):mCntrl(bus),arSredina(0)
{
    bus.insert(this);
}

void Statistics::send(string ulaz)
{
    if(ulaz[0]=='R' && ulaz[1]=='E' && ulaz[2]=='A' && ulaz[3]=='D')
    {
     int port= atoi(ulaz.substr(5).c_str());   ///atoi je konverzija strng u int, 4 pozicija u stringu je praznina, za atoi treba c string
     for(int i=0; i<mNoReads ; ++i)
     {
         arSredina+=mCntrl.receive(port);
         cout<<"port: "<<port<<" povratna vrijednost: "<<mCntrl.receive(port)<<" poziv : "<<i+1<<endl;
     }
     arSredina/=mNoReads;
    }else throw runtime_error("komanda nije valjana!");
}
