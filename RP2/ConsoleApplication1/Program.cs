using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class K1
    {
        public void pr(int x)
        {
            for (int i = 0; i< x; ++i)
            {
                Console.WriteLine(i);
            }
        }

        public static void pr2(int x)
        {
            for (int i = 0; i < x; ++i)
            {
                Console.WriteLine(i);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {

            Console.WriteLine("dobar dan!");

            K1 k = new K1();
            //prvi primjer sa nestatic funkcijom moram kreirat objekt
            for ( var i = 0; i <= 20; ++i)
            {
                k.pr(i);
            }

            //drugi primjer sa static fjom nema kreiranja objekta
            for (var i = 0; i <= 20; ++i)
            {
                K1.pr2(i);
            }

            int x1 = 5;
            double y1 = x1;

            double x2 = 5;
            // int y2 = x2;    gube se podatci pa treba cast (double)

            string s = @"lsdmgd";
            char c = s[4];
            //s[6] = 'g';     //string u c# su nepromjenjivi


        }
    }
}