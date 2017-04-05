#include <SFML/Graphics.hpp>

class Explosion
{
    private:
        sf::Vector2f mPosition;
        sf::VertexArray mVertexArray;

    public:
        Explosion();
        Explosion(sf::Vector2f position);
        void draw(sf::RenderWindow& window);

};

