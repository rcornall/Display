#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>

const auto LINES_AMOUNT = 65;
class Explosion
{
    private:
        std::array<sf::Vector2f, LINES_AMOUNT> mPositions;
        std::array<sf::Vector2f, LINES_AMOUNT> mPreviousPositions;
        std::array<sf::VertexArray, LINES_AMOUNT> mVertexArrays;
        std::array<std::vector<sf::Vector3f>, LINES_AMOUNT> mTracers;
        bool mIsRecyclable;
        bool mDying;
        float mTimeAlive;
        std::array<sf::Vector2f, LINES_AMOUNT> mSpeed;
        sf::Vector2f mForce;

    public:
        Explosion();
        Explosion(sf::Vector2f position);
        void draw(sf::RenderWindow& window);
        void updatePosition(const float& dt);
        bool recyclable()
        {
            return mIsRecyclable;
        }

};

