#pragma once 

#include <SFML/Graphics.hpp>

class Text
{
    private:
        sf::Text mText;

    public:
        Text(const std::string& _text, const sf::Vector2f& _pos, const sf::Font& _font);
        void draw(sf::RenderWindow& window);

};
