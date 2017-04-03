#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
// #include <SFML/OpenGL.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "opengl", sf::Style::Default);


    sf::VertexArray VA(sf::LinesStrip, 100);
    VA.setPrimitiveType(sf::LinesStrip);

    for(auto i = 0; i<100; i++)
    {
        VA.append(sf::Vertex(sf::Vector2f(i,i)));
    }
    sf::Vertex vertex1(sf::Vector2f(10,50));
    vertex1.position = sf::Vector2f(10, 50);
    vertex1.texCoords = sf::Vector2f(100, 100);

    sf::Vertex vertex2(sf::Vector2f(15, 55), sf::Vector2f(100, 100));

    //VA.append(vertex1);
    //VA.append(vertex2);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::Resized)
            {
                
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    auto x = sf::Mouse::getPosition(window).x;
                    auto y = sf::Mouse::getPosition(window).y;
                    std::cout << x << " " << y << std::endl;


                }
            }
        }
        window.clear();
        
        window.draw(VA);
        
        window.display();
    }

    // release opengl resources

    return 0;
}
