#include <cstdlib>
#include <ctime>

namespace helper
{

template<typename T>
T randF(const T lo, const T hi)
{
    static bool seeded = false;
    if(!seeded)
    {
        srand(static_cast<unsigned>(time(0)));
        seeded = true;
    }
    T ret = lo + static_cast<T>(rand())/static_cast<T>(RAND_MAX/(hi-lo));
    return ret;
}

} /* namespace helper */
