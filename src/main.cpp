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
    sf::RenderWindow window(sf::VideoMode(600, 800), "opengl", sf::Style::Default);
    window.setVerticalSyncEnabled(false);

    std::vector<Explosion> explosions;
    // std::vector<Text>      texts;

    // fps display
    sf::Clock clock, dtClock;
    unsigned fps = 0;

    sf::Font font;
    font.loadFromFile("/home/rob/Downloads/muzkaw/consola.ttf");
    const unsigned SIZE = 10;

    sf::Text fpsText("fps: 0", font, SIZE);
    fpsText.setPosition(sf::Vector2f(10,10));
    fpsText.setFillColor(sf::Color::White);

    sf::Text explosionCount("Objects: 0", font, SIZE);
    explosionCount.setPosition(sf::Vector2f(10,20));
    explosionCount.setFillColor(sf::Color::White);



    float dt = 0.1f;
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
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        const auto x = sf::Mouse::getPosition(window).x;
                        const auto y = sf::Mouse::getPosition(window).y;
                        std::cout << x << " " << y << std::endl;

                        explosions.push_back(Explosion(sf::Vector2f(x,y)));
                    }
                    break;
                default:
                    break;
            }
        }

        // update positions
        for(auto& it : explosions)
        {
            it.updatePosition(dt);
        }
        explosions.erase(   /* erase if explosion is recyclable */
                std::remove_if(explosions.begin(), explosions.end(),
                    [](Explosion it) -> bool { return it.recyclable(); }),
                explosions.end()
        );
        explosionCount.setString("explosions: " + std::to_string(explosions.size()));
        // update fps
        fps = updateFps(clock);
        if(fps)
        {
            fpsText.setString("fps: " + std::to_string(fps));
        }

        // clear and start drawing
        window.clear();
        
        for(auto& it : explosions)
        {
            // std::cout << it.getVertexCount() << std::endl;
            it.draw(window);
        }
        
        window.draw(fpsText);
        window.draw(explosionCount);
        window.display();

        dt = dtClock.restart().asSeconds();
    }
    
    return 0;
}
