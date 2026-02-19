#include <iostream>
#include <gamefile/gamefile.h>
#include <game/routine/routine.hpp>
#include <logger.hpp>
int main(int argc, char *argv[]) {
    Log("Pudding is launching...");
    Routine* routine = new Routine();
    Log("Initializing pudding...");
    routine->Initialize();
    if(argv[0] == "lt")
    {
        routine->LaunchTest();
    }
    routine->Update();
    routine->Exit();
}