#ifndef CVI
#define CVI

#include <string>
#include <typeinfo>
#include <vector>
#include <iostream>
#include <istream>
#include <stdexcept>

#include "visitor.h"
#include "memento.h"

class Component: public Visitable
{
    friend class componentIterator;
    friend class Memento;



    protected:
    std::vector<Component *> Djete;


    public:
     Component()=default;
    Component(std::string s): tekst(s) {};

     std::string tekst;
     Component * glavniNaslov=nullptr; ///pokazivac na glavni naslov koje je korjen stabla composite strukture

    virtual void addComponent (Component *) {throw std::runtime_error("nedozvoljena operacija sa baznom klasom");} ;
    virtual void removeComponent (const Component *){throw std::runtime_error("nedozvoljena operacija sa baznom klasom");};
    virtual Component * getChild(int) {throw std::runtime_error("nedozvoljena operacija sa baznom klasom");};

    void read(std::ifstream &);                                     ///T

    virtual void accept(Visitor * v){ v->visitComponent(this);};

    componentIterator* createIterator(){ return new componentIterator(this);};


};

class Title : public Component
{
    public:
    Title()=default;
    Title(std::string s):Component(s){};

    virtual void addComponent (Component *);                        ///T
    virtual void removeComponent (const Component *);               ///T
    virtual Component * getChild(int i) {return Djete[i];};         ///T

    virtual void accept(Visitor * v){ v->visitTitle(this);};


};

class Chapter : public Component
{
    public:
    Chapter()=default;
    Chapter(std::string s):Component(s){};

    virtual void addComponent (Component *);                        ///T
    virtual void removeComponent (const Component *);               ///T
    virtual Component * getChild(int i) {return Djete[i];};         ///T

    virtual void accept(Visitor * v){ v->visitChapter(this);};
};

class Paragraph : public Component
{   public:;
         Paragraph()=default;
         Paragraph(std::string s): Component(s){};
         virtual void addComponent (Component *){throw std::runtime_error("Paragraph nema podrzan rad sa djecom!");};                        ///T
         virtual void removeComponent (const Component *){throw std::runtime_error("Paragraph nema podrzan rad sa djecom!");};              ///T          ///potrebne su mi za kreiranje objekta tipa paragraph
         virtual Component * getChild(int i){throw std::runtime_error("Paragraph nema podrzan rad sa djecom!");};                          ///T

         virtual void accept(Visitor * v){ v->visitParagraph(this);};
};





#endif
