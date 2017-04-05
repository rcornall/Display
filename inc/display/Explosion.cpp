#include "Explosion.hpp"

Explosion::Explosion()
{
    mPosition = sf::Vector2f(40.f, 50.f);
}

Explosion::Explosion(sf::Vector2f position)
{
    mPosition = position;
}

void Explosion::draw(sf::RenderWindow& window)
{
    window.draw(mVertexArray);
}
