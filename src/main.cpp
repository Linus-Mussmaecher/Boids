#include "boids2D/boids.h"

int main() {
    //init
    SetTraceLogLevel(LOG_NONE);
    InitWindow(1200, 900, "Boids");
    SetTargetFPS(64);

    runBasic(128);

    CloseWindow();
    return 0;
}
