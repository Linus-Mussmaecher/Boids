#include "basic/basic.h"

int main() {
    //init
    InitWindow(1200, 900, "Boids");
    SetTargetFPS(64);

    runBasic(110);

    CloseWindow();
    return 0;
}
