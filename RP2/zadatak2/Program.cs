using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zadatak2
{
    class Program
    {
        
        static bool isPrime(int x)
        {
            if (x == 1) return true;
            if (x == 2) return true;
            for (int d = 3; d<= Math.Sqrt(x); ++d)
            {
                if (x % d == 0) return false;
            }
            return true;
        }

        static int findNextPrime( double x)
        {
            int y = Convert.ToInt32(Math.Ceiling(x));

            while (true)
            {
                if (isPrime(y++)) return y;
            }
            
        }

        static void Main(string[] args)
        {

            string s = "asda";
            foreach(char c in s) s += Convert.ToString(c);
            Console.WriteLine(s);
        }
    }
}
