using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vjezbe2Zadatak1
{
    public class Razlomak
    {
        private int brojnik;
        private int nazivnik;

        public int Brojnik
        {
            get { return brojnik; }
            set {
                brojnik = value;
                SkratiMe();
            }
        }
        public int Nazivnik
        {
            get { return nazivnik; }
            set {
                nazivnik = value;
                SkratiMe();
            }
        }

        static int gcd (int a, int b)
        {
            while (b>0)
            {
                int t = b; b = a % b; a = t;
            }
            return a;
        }

        private void SkratiMe()
        {
            int t = gcd(brojnik, nazivnik);
            brojnik /= t; nazivnik /= t;      
        }

        public override string ToString()
        {
            return Brojnik.ToString() + "/" + Nazivnik.ToString();
        }

        public Razlomak(int a, int b)
        {
            brojnik = a; nazivnik = b; SkratiMe();
        }

        //eksplicitni cast u double
        public static explicit operator double (Razlomak r)
        {
            return (double)r.Brojnik / r.Nazivnik;
        }

        //implicitni cast u float
        public static implicit operator float (Razlomak r)
        {
            return (float)r.Brojnik / r.Nazivnik;
        }
    }


    public class Osoba
    {
        public static int BrojacOsoba;
        public string Ime;
        public string Prezime;
        static List<Osoba> lo = new List<Osoba>();

        private DateTime VrijemeInstanciranja = DateTime.Now;

        static Osoba() //on se koristi prije kreiranja rijeci osoba
        {
            BrojacOsoba = 0;
        }
        public Osoba( string ime, string prezime)
        {
            Ime = ime;
            Prezime = prezime;
            BrojacOsoba++;
            lo.Add(this);
            Console.WriteLine("Kreirana osoba {0}", BrojacOsoba);
        }
        ~Osoba()
        {
            --BrojacOsoba;
        }

        public static void IspisiSve()
        {
            foreach (Osoba o in lo) Console.WriteLine(o.Ime + " " + o.Prezime + "\n");
        }

        public override string ToString()
        {
            return (Ime + Prezime);
        }
        public void IspisiDetalje()
        {
            Console.WriteLine("Objekt klase Osoba - detalji:");
            Console.WriteLine(
                "Ime: " + Ime + "\n" +
                "Prezime: " + Prezime + "\n" +
                "Vrijeme Instanciranja: " + VrijemeInstanciranja.ToLongTimeString() + "\n");
        }
    }

    class BrojN
    {

    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(Osoba.BrojacOsoba);
            Osoba s1 = new Osoba("fico", "skrico");
            Osoba s2 = new Osoba("fico2", "skrico2");
            Osoba s3 = new Osoba("fico3", "skrico3");
            Osoba s4 = new Osoba("fico4", "skrico4");
            s4.IspisiDetalje();
            Console.WriteLine(s1);

            Osoba.IspisiSve();


            //2. zadatak

            Razlomak r1 = new Razlomak(5, 10);
            Console.WriteLine(r1); //ispis preko overridane funkcije toString()
            r1.Brojnik = 4; // pristupamo svojstvu klase a ne privatnoj varijabli
            Console.WriteLine(r1);

        }
    }
}
