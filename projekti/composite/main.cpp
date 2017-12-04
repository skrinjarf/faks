
 #include <SFML/Graphics.hpp>
#include <iostream>
#include "composite.h"

using namespace std;
int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "Composite DP");

    Component scene;
    auto pc1 = new Circle(50);
    pc1->move(10,10);
    scene.addComponent(unique_ptr<Component>(pc1));

    auto pr1 = new Rectangle(100,20);
    pr1->move(120,10);
    scene.addComponent(unique_ptr<Component>(pr1));

    sf::Vector2f p1(0,0);
    sf::Vector2f p2(30,40);
    sf::Vector2f p3(70,0);

    auto pt1 = new Triangle(p1,p2,p3);
    pt1->move(120,70);
    scene.addComponent(unique_ptr<Component>(pt1));

     bool moving = false;
     sf::Vector2f oldPos(0.f,0.f);
	// Start the game loop
    while (app.isOpen())
    {

        sf::Vector2f delta(0.f,0.f);
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            else if(event.type == sf::Event::MouseButtonPressed){
                moving = true;
                oldPos = app.mapPixelToCoords( sf::Vector2i(event.mouseButton.x, event.mouseButton.y) );
            }
            else if(event.type == sf::Event::MouseButtonReleased){
                moving = false;
            }
            else if(event.type == sf::Event::MouseMoved)
            {
              if(moving){
                sf::Vector2f newPos = app.mapPixelToCoords( sf::Vector2i(event.mouseMove.x, event.mouseMove.y) );
                delta = (newPos - oldPos);
                delta /= 100.f;
              }
            }
        }

        // Clear screen
        app.clear();

        scene.move(delta);
        app.draw(scene);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
