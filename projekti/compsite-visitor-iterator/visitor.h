#ifndef VISITOR_H
#define VISITOR_H

#include <vector>
#include <stack>
#include "memento.h"

class Title; class Chapter; class Paragraph; class Component;  ///forward declaration



class Iterator{
public:
    virtual bool isDone()=0;
    virtual void first()=0;
    virtual void next()=0;

};



class componentIterator: public Iterator
{


    std::vector<Component *> items;
    int it;
    int kraj;


    public:


    std::stack<Memento> stog;   ///ako je private ne radi push u visitComponent

    virtual bool isDone(){return it>kraj;};  ///ako je it >= kraj onda smo presli sve elemente
    virtual void first() {it=0;};
    virtual void next(){it++;};
    virtual Component* currentItem(){return items[it];};

    componentIterator()=default;
    componentIterator(Component*);

  ///  static void punjenjeItema(Component*, std::vector<Component*>&);


};

class Visitor{
public:
   virtual void visitTitle(Title*)=0;
   virtual void visitChapter(Chapter*) =0;
   virtual void visitParagraph(Paragraph*) =0;
   virtual void visitComponent(Component *) =0;
};

class Visitable{
    public:
    virtual void accept(Visitor*)=0;
};

class HTMLVisitor: public Visitor
{
    std::string htmltekst;
    public:
   HTMLVisitor():htmltekst(""){};
   virtual void visitTitle(Title*);
   virtual void visitChapter(Chapter*);
   virtual void visitParagraph(Paragraph*);
   virtual void visitComponent(Component *);
   void visitChildren(componentIterator *);

};


#endif /// VISITOR_H



