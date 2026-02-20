#include <iostream>
#include <gamefile/gamefile.h>
#include <game/routine/routine.hpp>
#include <logger.hpp>
int main(int argc, char *argv[]) {
    Log("Pudding is launching...");
    Routine* routine = new Routine();
    Log("Initializing pudding...");
    if(argc > 1){
        if(strncmp(argv[1],"--lt",2))
        {
            routine->LaunchTest();
            routine->Exit();
            return 0;
        }
    }
    if(routine->Initialize() == 1)
    {
        return 0;
    }
    routine->Update();
    routine->Exit();
}