#include <iostream>
#include <gamefile/gamefile.h>
#include <game/routine/routine.hpp>
int main() {
    Routine* routine = new Routine();
    routine->Initialize();
    routine->Update();
    routine->Exit();
}