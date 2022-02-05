#include "basic/basic.h"
#include "teams/teams.h"

int main() {
    //init
    InitWindow(1200, 900, "Boids");
    SetTargetFPS(64);


    runSimulation(60);

    CloseWindow();
    return 0;
}
