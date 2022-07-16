//
// Created by Linus on 05/02/2022.
//
#include "boids.h"


void runBasic(int amount) {
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
    auto h = float(GetScreenHeight());

    vector<Obstacle> obstacles{
            Obstacle({450, 700, 50, 200}),
            Obstacle({750, 700, 50, 200}),
            Obstacle({350, 500, 600, 30}),
            Obstacle({450, 100, 400, 30}),
            Obstacle({1000, 50, 50, 700}),

            //edges

            Obstacle({0, -1, w, 1}),
            Obstacle({0, h, w, 1}),
            Obstacle({-1, 0, 1, h}),
            Obstacle({w, 0, 1, h}),
    };

    Vector2 upLeft = {-1, -1};


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

            //draw marker for obstacle adding
            if (upLeft != Vector2{-1, -1}) {
                float minx = std::min(upLeft.x, float(GetMouseX()));
                float maxx = std::max(upLeft.x, float(GetMouseX()));
                float miny = std::min(upLeft.y, float(GetMouseY()));
                float maxy = std::max(upLeft.y, float(GetMouseY()));

                Obstacle({minx, miny, maxx - minx, maxy - miny}).draw();
            }

        }
        EndDrawing();

        //start of obstacle adding
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            upLeft = Vector2({float(GetMouseX()), float(GetMouseY())});
        }
        //end of obstacle adding
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

            float minx = std::min(upLeft.x, float(GetMouseX()));
            float maxx = std::max(upLeft.x, float(GetMouseX()));
            float miny = std::min(upLeft.y, float(GetMouseY()));
            float maxy = std::max(upLeft.y, float(GetMouseY()));

            obstacles.push_back(Obstacle({minx, miny, maxx - minx, maxy - miny}));

            upLeft = {-1, -1};
        }
        //removing obstacles
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle &o) {
                return CheckCollisionPointRec({float(GetMouseX()), float(GetMouseY())}, o.getCollider());
            }), obstacles.end());
        }


    }

}


bool checkRayCollision(Vector2 ray_start, Vector2 ray_end, vector<Obstacle> *obstacles) {
    return std::any_of(obstacles->begin(), obstacles->end(), [ray_start, ray_end](Obstacle &o) {
        return CheckCollisionLineRect(ray_start, ray_end, o.getCollider()); //ray collides with an obstacle
    });
}