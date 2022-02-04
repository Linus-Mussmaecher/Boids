#include "../include/boids.h"

int main() {
    //init
    InitWindow(1200, 900, "Boids");
    SetTargetFPS(64);
    int amount = 110;

    vector <Boid> boids{};
    boids.reserve(amount);
    for (int i = 0; i < amount; i++) {
        boids.push_back(Boid(
                {
                        float(GetRandomValue(0, GetScreenWidth())),
                        float(GetRandomValue(0, GetScreenHeight()))
                },
                Vector2Rotate({0,speed}, 2 * PI * float(GetRandomValue(0, 100)) / 100)
        ));
    }
//    boids[0].choose();

    while (!WindowShouldClose()) {

        BeginDrawing();
        {

            ClearBackground(BLACK);
            for(Boid &boid : boids){
                boid.move(&boids);
                boid.draw();
            }

        }
        EndDrawing();


    }


    CloseWindow();
    return 0;
}
