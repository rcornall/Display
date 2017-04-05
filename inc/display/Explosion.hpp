#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>

const auto LINES_AMOUNT = 45;
class Explosion
{
    private:
        std::array<sf::Vector2f, LINES_AMOUNT> mPositions;
        std::array<sf::Vector2f, LINES_AMOUNT> mPreviousPositions;
        sf::VertexArray mVertexArray;
        std::array<std::vector<sf::Vector3f>, LINES_AMOUNT> mTracers;
        bool isRecyclable;
        std::array<sf::Vector2f, LINES_AMOUNT> mSpeed;
        sf::Vector2f mForce;

    public:
        Explosion();
        Explosion(sf::Vector2f position);
        void draw(sf::RenderWindow& window);
        void updatePosition(const float& dt);
        bool recyclable();

};

