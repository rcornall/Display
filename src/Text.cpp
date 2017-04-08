#include "Text.hpp"
#include <cstring>

const static auto SIZE = 15;

Text::Text(const std::string& _text, const sf::Vector2f& _pos, const sf::Font& _font) :
    mText()
{
    mText.setString(_text);
    mText.setPosition(_pos);
    mText.setFont(_font);
    mText.setFillColor(sf::Color::White);
    mText.setCharacterSize(SIZE);
}

void Text::draw(sf::RenderWindow& window)
{
    window.draw(mText);
}

