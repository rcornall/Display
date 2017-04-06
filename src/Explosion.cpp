#include "Explosion.hpp"
#include "helper.hpp"

Explosion::Explosion() :
    mVertexArray(sf::LinesStrip, LINES_AMOUNT),
    isRecyclable(false),
    mForce(helper::randF(-20.f,20.f), helper::randF(-5.f,30.f))
{
    for(auto& it : mPositions)
        it = sf::Vector2f(50.f,40.f);
    for(auto& it : mSpeed)
        it = sf::Vector2f(helper::randF(-20.f,20.f),helper::randF(0.f,30.f));
}

Explosion::Explosion(sf::Vector2f position) :
    mVertexArray(sf::LinesStrip, LINES_AMOUNT),
    isRecyclable(false),
    mForce(helper::randF(-20.f,20.f), helper::randF(-5.f,30.f))
{
    // set positions of all 45 lines to start at the same point
    for(auto& it : mPositions)
        it = position;
    for(auto& it : mSpeed)
        it = sf::Vector2f(helper::randF(-20.f,20.f),helper::randF(0.f,30.f));


}

void Explosion::updatePosition(const float& dt)
{
    mPreviousPositions = mPositions;
    mVertexArray.clear();
    
    // need to update position of tracers[100 each] for every linestrip. 100*45 4500 positions
    for(auto i = 0; i<LINES_AMOUNT; ++i)
    {
        mPositions[i] = mPositions[i] + mSpeed[i]*dt + 0.5f*mForce*2.f*(float)pow(dt,2);
        mSpeed[i] = (mPositions[i] - mPreviousPositions[i])/dt;
        
        mTracers[i].push_back(sf::Vector3f(mPositions[i].x, mPositions[i].y, 100));
        for(auto& tracer : mTracers[i])
        {
            tracer.z = std::max(tracer.z-100*dt,0.f) ;
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
            mVertexArray.append(sf::Vertex(sf::Vector2f(tracer.x,tracer.y),sf::Color(255,255,0,tracer.z*2.5)));
        }
    }
}


void Explosion::draw(sf::RenderWindow& window)
{
    window.draw(mVertexArray);
}
