#include "time.hpp"

#define MS_PER_SECOND   1000.0f

Time t_;

Time::Time()
{
}

void Time::start()
{
    t_.start_ = std::chrono::system_clock::now();
}

void Time::update()
{
    auto last = t_.now_;

    t_.now_ = std::chrono::system_clock::now();
    t_.time_ = std::chrono::duration_cast<ms>(t_.now_ - t_.start_);
    t_.deltaTime_ = std::chrono::duration_cast<ms>(t_.now_ - last);
}

double Time::time()
{
    return t_.time_.count() / MS_PER_SECOND;
}

double Time::deltaTime()
{
    return t_.deltaTime_.count() / MS_PER_SECOND;
}
