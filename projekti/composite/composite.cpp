#include"composite.h"
#include <stdexcept>

using namespace std;

void Component::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawYourself(target, states);
    for(auto const & pt : mChildren) pt->draw(target, states);
}


void Component::addComponent(Ptr p){

    for(int i=0;i< mChildren.size();i++)
    {
      if(mChildren[i]==p){
      throw runtime_error("Componenta vec postoji");
      return ;
      }
    }

            p->mParent= this;
            mChildren.push_back(p);

}

Component::Ptr Component::removeComponent(const Component * p){

    int j=0;
    for( vector<Ptr>::iterator i=mChildren.begin() ;  i!= mChildren.end();i++,j++)
    {
      if( (*i).get()==p )
      {
                Ptr temp = move(mChildren[j]);


                (*i)->mParent=nullptr;
                mChildren.erase(i);
        return temp;

      }
    }
     throw runtime_error("Componenta ne postoji");
     return;


}
