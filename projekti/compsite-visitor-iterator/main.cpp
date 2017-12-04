  #include <iostream>
  #include <istream>
  #include <fstream>

  #include "cvi.h"

using namespace std;
    int main()
{
    Component document;

    ofstream out;
    out.open("test_output.txt");
    if(!out) throw runtime_error("nije otvoren file");

    ifstream in("..\tekst.txt");



    if(!in) throw std::runtime_error("Canot open file proba.txt.\n");

   /// document.read(in);

    in.close();

    HTMLVisitor html;

///    document.accept(&html);

    return 0;
}

