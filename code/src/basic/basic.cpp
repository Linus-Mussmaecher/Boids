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

    auto w = float(GetScreenWidth());
    auto h= float(GetScreenHeight());

    vector<Obstacle> obstacles{
            Obstacle({450, 700, 50, 200}),
            Obstacle({750, 700, 50, 200}),
            Obstacle({350, 500, 600, 30}),
            Obstacle({450, 100, 400, 30}),

            //edges

            Obstacle({0, -1, w, 1}),
            Obstacle({0, h, w, 1}),
            Obstacle({-1, 0, 1, h}),
            Obstacle({w, 0, 1, h}),
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


bool checkRayCollision(Vector2 ray_start, Vector2 ray_end, vector<Obstacle> *obstacles) {
    return std::any_of(obstacles->begin(), obstacles->end(), [ray_start, ray_end](Obstacle &o) {
        return CheckCollisionLineRect(ray_start, ray_end, o.getCollider()); //ray collides with an obstacle
    });
}