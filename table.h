#ifndef TABLE_H
#define TABLE_H

#include <iostream>

class Table{
public:
    // Defaultni konstruktor konstruira praznu tabelu
    Table() : N(0u), M(0u), data(nullptr) {}
    Table(unsigned int n, unsigned int m);

    int & operator()(unsigned int i, unsigned int j);
    const int & operator()(unsigned int i, unsigned int j) const;

    Table(Table const &);
    Table & operator=(Table const &);
    ~Table(){ delete  [] data; }

    void resize(unsigned int n, unsigned int m);

    unsigned int nRows() const {return N; }
    unsigned int nCols() const {return M; }

    void print(std::ostream & out);
private:
    unsigned int N,M;
    int ** data;
};

#endif // TABLE_H_INCLUDED
