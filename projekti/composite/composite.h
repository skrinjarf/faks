#include <SFML/Graphics.hpp>
#include<iostream>
#include <memory>


class Component : public sf::Drawable, public sf::Transformable{
public:


    using Ptr = std::unique_ptr<Component>;

    Component() : mParent(nullptr) {}

    // Dodaj komponentu (dijete) i preuzmi vlasništvo nad njom.
    // Izbacuje izuzetak ako komponenta već postoji.
    void addComponent(Ptr);
    // Eliminiraj komponentu iz liste djece (odricanje od vlasništva nad komponentom).
    // Izbacuje izuzetak ako komponenta ne postoji.
    Ptr removeComponent(const Component *);
private:
    // Iscrtaj komponentu i njenu djecu.
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // iscrtaj samo komponentu, bez djece.
    virtual void drawYourself(sf::RenderTarget& target, sf::RenderStates states) const
    {
     // prazno --
    }

    std::vector<Ptr> mChildren;
    Component * mParent;
};




class Circle :  public Component{
public:
    Circle(float radius) : mCircle(radius) {}
private:
    virtual void drawYourself(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mCircle, states);
    }

    sf::CircleShape mCircle;
};



class Rectangle :  public Component{
public:
    Rectangle(float dimx, float dimy) : mRectangle(sf::Vector2f(dimx,dimy)) {}

private:
    virtual void drawYourself(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mRectangle, states);
    }

    sf::RectangleShape mRectangle;
};




class Triangle :  public Component{
public:
    Triangle(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3){
        mTriangle.setPointCount(3);
        mTriangle.setPoint(0,p1);
        mTriangle.setPoint(1,p2);
        mTriangle.setPoint(2,p3);
    }

private:
    virtual void drawYourself(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(mTriangle, states);
    }

    sf::ConvexShape mTriangle;
};
