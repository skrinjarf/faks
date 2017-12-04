#include "cvi.h"
#include "visitor.h"
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <stdexcept>


using namespace std;


void Title::addComponent(Component * cp)
{
   if((typeid(*cp)!= typeid(Chapter)) && (typeid(*cp) != typeid(Paragraph))) throw runtime_error("komponenta nije odgovarajuceg tipa!(paragraf niti chapter)");
   Djete.push_back(cp);
}


void Chapter::addComponent(Component * cp)
{
   if(typeid(*cp) != typeid(Paragraph)) throw runtime_error("komponenta nije odgovarajuceg tipa(paragraf)!");
   Djete.push_back(cp);
}

void Title::removeComponent(const Component * cp)
{
    if(typeid(*cp)!= typeid(Chapter) && typeid(*cp) != typeid(Paragraph)) throw runtime_error("komponenta nije odgovarajuceg tipa!(paragraf niti chapter)");   ///dopdaj typeid od chaptera itd
   for( vector<Component *>::iterator i=Djete.begin() ;  i!= Djete.end();i++) if(*i == cp) Djete.erase(i);


}

void Chapter::removeComponent(const Component * cp)
{
    if(typeid(*cp) != typeid(Paragraph)) throw runtime_error("komponenta nije odgovarajuceg tipa(paragraf)!");
    for( vector<Component *>::iterator i=Djete.begin() ;  i!= Djete.end();i++) if( *i == cp) Djete.erase(i);
}

void Component::read(ifstream& infile)
{
  string s;
  Component * glavniTitle=nullptr;
  Component * zadnjiChapter=nullptr;
  while(getline(infile,s))
  {
      if(s[0]=='=' && s[1]==' '){  ///TITLE
            string temp= s.substr(2);
            Title NoviNaslov(temp);
            glavniTitle= &NoviNaslov;        ///pazi da ne postane nullptr nakon iteracije whilea kad se obrise varijabla NoviNaslov
      }
      else if (s[0]=='=' && s[1]=='=' && s[2]==' '){ ///CHAPTER
            string temp= s.substr(3);
            Chapter * cp=new Chapter(temp);
            glavniTitle->addComponent(cp);
            zadnjiChapter=cp;
      }
      else { ///PARAGRAPH

            string cijeli=s;            ///u cijeli dodaj prvi red
            while(getline(infile,s))
            {
                if(s=="\n"){   ///ako si u rupi, sve akumulirano u s strpaj u paragrap
                        Paragraph * pp = new Paragraph(cijeli);
                        zadnjiChapter->addComponent(pp);
                        while(getline(infile,s)) if(s=="\n") continue; ///preskoci sve daljnje praznine do iduce komponente
            }else {cijeli += " " ; cijeli += s;}
           }
  }


 }
 glavniNaslov=glavniTitle;
}

/**
void componentIterator::punjenjeItema(Component * cp, std::vector<Component*>& vec)
{
     for(Component* x: cp->Djete)
        {
            if(typeid(x)==typeid(Paragraph)){vec.push_back(x); continue;} ///paragraph nema djece;
            vec.push_back(x); punjenjeItema(x,vec); ///ubaci korjen i rjesi djecu
        }
    return;
}
**/

componentIterator::componentIterator(Component * cp){
        it=0;
        items.push_back(cp);
        kraj=cp->Djete.size();
        for(auto x: cp->Djete) items.push_back(x);   ///u items ubacujem komponentu na koju je pozvano i njezinu djecu
       /// punjenjeItema(cp,items);
}

void HTMLVisitor::visitTitle(Title* tp)
{
    string temp="<h1>";
    temp+=tp->tekst;
    temp+="</h1>";
    temp+="\n";     ///nakon naslova prelazim u novi red
    htmltekst+=temp;
}

void HTMLVisitor::visitChapter(Chapter* cp)
{
    string temp=" <h2>";
    temp+=cp->tekst;
    temp+="</h2>";
    temp+="\n";       ///nakon h2 prelazim u novi red
    htmltekst+=temp;
}

void HTMLVisitor::visitParagraph(Paragraph* pp)     ///razmisli kako napravit da su paragrafi uvucen sa tabom "\t"
{
    bool prvaZvjezda=false;
    bool prvaCrta=false;
    string temp;
    for(char c : pp->tekst) {
        if(c=='*' && prvaZvjezda){
            htmltekst+="<b>";
            htmltekst+=temp;
            htmltekst+="</b";
            prvaZvjezda=false;
            continue;
        }
        if(c=='*' && !prvaZvjezda){
            prvaZvjezda=true;
            htmltekst+=temp;  ///dodaj dosadasnji tekst prije bolda i trazi kraj boldanja
            temp.clear();
            continue;
        }
        if(c=='_' && prvaCrta){
            htmltekst+="<i>";
            htmltekst+=temp;
            htmltekst+="</i";
            prvaCrta=false;
            continue;
        }
         if(c=='_' && !prvaCrta){
            prvaCrta=true;
            htmltekst+=temp;  ///dodaj dosadasnji tekst prije bolda i trazi kraj boldanja
            temp.clear();
            continue;
         }
          temp+=c;

    }
    temp+="\n\n";  ///kad zavrsi paragraf radim jednu prazninu
}

void HTMLVisitor::visitChildren(componentIterator * iterp)
{
    iterp->currentItem()->accept(this);                     ///radi accept na samom elementu a for prolazi kroj njegovu djecu
    for(iterp->next();!iterp->isDone();iterp->next())     ///kreni od njegove djece
       {
           if(typeid(*(iterp->currentItem())) == typeid(Paragraph)){
                    iterp->currentItem()->accept(this);
            }else{
                Memento stari(iterp);                                     ///ako nije paragraf obidi podstablo
                iterp->stog.push(stari);
                iterp= new componentIterator(iterp->currentItem());            ///uhvati novi iterator za current item konstruktor od componentIteratora nebi smjeo mjenjat stog mementa
                visitChildren(iterp);  ///nakon odrade visitChildren iterator se vraca u stanje prije ulaska u else
            }
       }
      /// kada si prosao sve clanove na razini, vrati iterp u prethodno stanje
      iterp= iterp->stog.top().iter;
      return;
}

void HTMLVisitor::visitComponent(Component* cp)
{
       componentIterator* iterp= cp->glavniNaslov->createIterator();  ///kad zoven na obicnu komp radi iter od glavnog naslova i onda obilazim na dalje
       visitChildren(iterp);
       cout<<htmltekst;

}


