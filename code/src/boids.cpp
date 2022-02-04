#include "../include/boids.h"

int main() {
    //init
    InitWindow(1200, 900, "Boids");
    SetTargetFPS(64);
    int amount = 100;

    vector <Boid> boids{};
    boids.reserve(amount);
    for (int i = 0; i < amount; i++) {
        boids.push_back(Boid(
                {
                        float(GetRandomValue(0, GetScreenWidth())),
                        float(GetRandomValue(0, GetScreenHeight()))
                },
                {
                    speed,//* cos(float(i)/float(amount) * 2.f * PI),
                    speed * 0//* sin(float(i)/float(amount) * 2.f * PI)
                 }
        ));
    }
//    boids[0].choose();
//    boids.push_back(Boid({100, 200}, {speed, 0.f}));
//    boids.push_back(Boid({800, 200}, {-speed, 0.f}));

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
