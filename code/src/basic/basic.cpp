//
// Created by Linus on 05/02/2022.
//
#include "basic.h"


void runBasic(int amount){
    vector<Boid> boids{};
    boids.reserve(amount);
    for (int i = 0; i < amount; i++) {
        boids.push_back(Boid(
                {
                        float(GetRandomValue(0, GetScreenWidth())),
                        float(GetRandomValue(0, GetScreenHeight()))
                },
                Vector2Rotate({0, speed}, 2 * PI * float(GetRandomValue(0, 100)) / 100)
        ));
    }
#ifdef _DEBUG
    boids[0].choose();
#endif


    vector<Obstacle> obstacles{
            Obstacle({450, 700, 50, 200}),
            Obstacle({750, 700, 50, 200}),
            Obstacle({350, 500, 600, 30}),
            Obstacle({450, 100, 400, 30}),
    };


    while (!WindowShouldClose()) {

        BeginDrawing();
        {

            ClearBackground(BLACK);

            for (Obstacle &obstacle: obstacles) {
                obstacle.draw();
            }

            for (Boid &boid: boids) {
                boid.move(&boids, &obstacles);
                boid.draw();
            }

        }
        EndDrawing();


    }

}