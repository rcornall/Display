#include "Explosion.hpp"
#include "helper.hpp"
#include <iostream>

const static auto MAX_ALPHA = 100;

Explosion::Explosion() :
    mIsRecyclable(false),
    mDying(false),
    mTimeAlive(0),
    mForce(0, helper::randF(35.f,40.f))
{
    for(auto& it : mVertexArrays)
        it = sf::VertexArray(sf::LinesStrip);
    for(auto& it : mPositions)
        it = sf::Vector2f(50.f,40.f);
    for(auto& it : mSpeed)
        it = sf::Vector2f(helper::randF(-40.f,40.f),helper::randF(10.f,-70.f));
}

Explosion::Explosion(sf::Vector2f position) :
    mIsRecyclable(false),
    mDying(false),
    mTimeAlive(0),
    mForce(0, helper::randF(35.f,40.f))
{
    for(auto& it : mVertexArrays)
        it = sf::VertexArray(sf::LinesStrip);
    // set positions of all 45 lines to start at the same mouse point
    for(auto& it : mPositions)
        it = position;
    for(auto& it : mSpeed)
        it = sf::Vector2f(helper::randF(-40.f,40.f),helper::randF(10.f,-70.f));
}

void Explosion::updatePosition(const float& dt)
{
    mTimeAlive += dt;
    if(mTimeAlive > 1.0f) /* start dying after 1 sec */
        mDying = true;

    mPreviousPositions = mPositions;
    for(auto& it : mVertexArrays)
        it.clear();
    
    // need to update position of tracers[100 each] for every linestrip. 100*45 4500 positions
    for(auto i = 0; i<LINES_AMOUNT; ++i)
    {
        mPositions[i] = mPositions[i] + mSpeed[i]*dt + 0.5f*mForce*2.f*(float)pow(dt,2); /* Leapfrog method */
        mSpeed[i] = (mPositions[i] - mPreviousPositions[i])/dt; /* new speed is dp/dt */
        
        if(!mDying)
            mTracers[i].push_back(sf::Vector3f(mPositions[i].x, mPositions[i].y, MAX_ALPHA));
        else /* start fading out */
            mTracers[i].push_back(sf::Vector3f(mPositions[i].x, mPositions[i].y, MAX_ALPHA - mTimeAlive*50));

        for(auto& tracer : mTracers[i])
        {
            tracer.z = std::max(tracer.z-MAX_ALPHA*dt,0.f);
            if(mDying)
                tracer.z = std::max(tracer.z-200*dt,0.f);
        }
        // remove elements of tracer with 0 alpha value
        mTracers[i].erase(
            std::remove_if(
                mTracers[i].begin(),
                mTracers[i].end(),
                [](sf::Vector3f tracer) -> bool {
                    if(tracer.z == 0)
                        return true;
                    else
                        return false;
                }
            ),
            mTracers[i].end()
        );
        for(const auto& tracer : mTracers[i])
        {
            mVertexArrays[i].append(sf::Vertex(sf::Vector2f(tracer.x,tracer.y),sf::Color(255,255,0,tracer.z*2.5)));
        }
    }
    if(!mIsRecyclable)
    {
        // once no tracers are left then we can let users know the explosion can be deleted
        if(mTracers[0].size() < 1)
        {
            mIsRecyclable = true;
        }
    }

        
}


void Explosion::draw(sf::RenderWindow& window)
{
    for(auto& it : mVertexArrays)
        window.draw(it);
}
