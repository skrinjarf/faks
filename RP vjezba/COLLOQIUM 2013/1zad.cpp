#include <iostream>
#include <cmath>

using namespace std;

class Cplx
{
public:

    double re,im;
    static double eps;

    //konstruktori
    Cplx(double r, double i):re(r),im(i){}
    Cplx(char i):re(0),im(1.0){}
    Cplx():re(0),im(0){}
    Cplx(double r):re(r),im(0){}

    Cplx* operator->(){
        return this;
    }

    operator double(){
        return sqrt(re*re + im*im);
    }
    Cplx& operator~(){
        im= -im;
        return *this;
    }




};

Cplx operator+(Cplx a, Cplx b)
{
    return Cplx(a.re+b.re,a.im+b.im);
}
Cplx operator+(Cplx a, double b){
    return Cplx(a.re+b,a.im);
}
Cplx operator-(Cplx a, Cplx b){
    return Cplx(a.re-b.re,a.im-b.im);
}

Cplx operator*(Cplx a, Cplx b){
    return Cplx(a.re*b.re-a.im*b.im,a.im*b.re+a.re*b.im);
}
Cplx operator*(Cplx a, double b){
    return Cplx(a.re*b,a.im);
}

Cplx operator/(Cplx a, Cplx b){
     if(b.re==0 && b.im==0){
         cout<<"div0!"; return Cplx();
     }
     Cplx temp= a* (~b);
     temp.re*=(1/(double)b); temp.im*=(1/(double)b);
     return temp;
}

bool operator == (Cplx a, Cplx b){
    return ((double)(a-b) < Cplx::eps);
}

ostream& operator<<(ostream& f, Cplx a){
    if(a.im>0) f<<a.re<<'+'<<a.im<<'i';
    if(a.im<0) f<<a.re<<'-'<<a.im<<'i';
    if(a.im==0) f<<a.re;
    return f;
}

double Cplx::eps=0.0000001;


int main()
{
  Cplx a(3.0),b(10,2),c(8,5);
  cout<<a<<" "<<b<<" "<<c<<endl;
  Cplx d=b*c;
  cout<<d<<d->re<<d->im<<endl;
  d->re = 1000;
  cout<<d->re<<endl;
  Cplx e;
  cout << d/e<<endl;
  cout<< b+(double)2;

}
