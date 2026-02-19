#include "logger.hpp"
#include <cstdio>
#include <iostream>

void Log(const char* message)
{
    if(debugMode)
    {
        std::cout << message << std::endl;
    }
}