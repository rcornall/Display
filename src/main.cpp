#include "Explosion.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
// #include <SFML/OpenGL.hpp>
// void newExplosion(const int& x, const int& y)
// {
//     
// }

unsigned updateFps(sf::Clock& clock)
{
    static unsigned frames = 0;
    if(clock.getElapsedTime().asSeconds() >= 1.f)
    {
        clock.restart();
        unsigned ret{frames};
        frames = 0;
        return ret;
    }
    ++frames;
    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "opengl", sf::Style::Default);
    window.setVerticalSyncEnabled(false);

    std::vector<sf::VertexArray> explosions;

    sf::VertexArray VA(sf::LinesStrip);
    VA.setPrimitiveType(sf::LinesStrip);

    for(auto i = 90; i<100; i++)
    {
        VA.append(sf::Vertex(sf::Vector2f(i,i)));
    }
    sf::Vertex vertex1(sf::Vector2f(10,50));
    vertex1.position = sf::Vector2f(10, 50);
    vertex1.texCoords = sf::Vector2f(100, 100);

    sf::Vertex vertex2(sf::Vector2f(15, 55), sf::Vector2f(100, 100));

    sf::Clock clock;
    sf::Text fpsText;
    unsigned fps = 0;
    sf::Font font;
    font.loadFromFile("/home/rob/Downloads/muzkaw/consola.ttf");
    fpsText.setPosition(sf::Vector2f(10,10));
    fpsText.setFont(font);
    fpsText.setColor(sf::Color::White);
    fpsText.setCharacterSize(9);
    fpsText.setString("fps: 0");


    //VA.append(vertex1);
    //VA.append(vertex2);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        const auto x = sf::Mouse::getPosition(window).x;
                        const auto y = sf::Mouse::getPosition(window).y;
                        std::cout << x << " " << y << std::endl;

                        // newExplosion(x,y);
                        explosions.push_back(sf::VertexArray(sf::LinesStrip));
                        explosions.back().append(sf::Vertex(sf::Vector2f(x,y)));
                        explosions.back().append(sf::Vertex(sf::Vector2f(x+1,y+1)));
                        // auto* tmp = &explosions.back();
                        // for(auto i=0; i<11; i+=10)
                        // {
                        //     tmp->append(sf::Vertex(sf::Vector2f(x-i,y-i)));
                        // } }    
                    }}
                    break;
                default:
                    break;
            }
        }
        window.clear();
        
        window.draw(VA);
        for(const auto& it : explosions)
        {
            // std::cout << it.getVertexCount() << std::endl;
            window.draw(it);
        }
        fps = updateFps(clock);
        if(fps)
        {
            // std::cout << std::to_string(fps) << std::endl;
            fpsText.setString("fps: " + std::to_string(fps));
        }
        window.draw(fpsText);
        window.display();
    }
    
    return 0;
}
