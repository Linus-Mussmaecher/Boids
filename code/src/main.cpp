#include "boids2D/boids.h"
#include "boids3D/boids3D.h"

int main() {
    //init
    InitWindow(1200, 900, "Boids");
    SetTargetFPS(64);

    runBasic(128);

    CloseWindow();
    return 0;
}
