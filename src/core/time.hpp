#pragma once

#include <chrono>

class Time
{
public:
    Time();

    static void start();
    static void update();

    static double time();
    static double deltaTime();

protected:

    typedef std::chrono::system_clock::time_point sysTime;
    typedef std::chrono::milliseconds ms;

    sysTime start_;
    sysTime now_;

    ms time_;
    ms deltaTime_;
};
