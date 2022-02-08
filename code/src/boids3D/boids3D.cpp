//
// Created by Linus on 08.02.2022.
//

#include "boids3D.h"

void run3D(int amount){

    float x_size = 500;
    float y_size = 500;
    float z_size = 500;

    vector<Boid3D> boids{};
    boids.reserve(amount);
    for (int i = 0; i < amount; i++) {
        boids.push_back(Boid3D(
                {
                        float(GetRandomValue(0, int(x_size))),
                        float(GetRandomValue(0, int(y_size))),
                        float(GetRandomValue(0, int(x_size))),
                },
                {speed_3D, 0, 0}
        ));
    }
#ifdef _DEBUG
    boids[0].choose();
#endif



    vector<Obstacle3D> obstacles{
            Obstacle3D({{400, 300, 400}, {500, 400, 500}}, DARKGRAY),

            //edges

            Obstacle3D({{0, 0, 0}, {0, y_size, z_size}}, BLANK),
            Obstacle3D({{x_size, 0, 0}, {x_size, y_size, z_size}}, BLANK),
            Obstacle3D({{0, 0, 0}, {x_size, 0, y_size}}, BLANK),
            Obstacle3D({{0, y_size, 0}, {x_size, y_size, z_size}}, BLANK),
            Obstacle3D({{0, 0, 0}, {x_size, y_size, 0}}, BLANK),
            Obstacle3D({{0, 0, z_size}, {x_size, y_size, z_size}}, BLANK)
    };


    Camera3D camera{0};
    camera.position = {x_size / 2,-100,z_size + 100};
    camera.target = {x_size/2,y_size/2,z_size/2};
    camera.up = {0,0,1};
    camera.fovy = 90.f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_FREE);

    while (!WindowShouldClose()) {

        UpdateCamera(&camera);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        {


            for (Obstacle3D &obstacle: obstacles) {
                obstacle.draw();
            }

            for (Boid3D &boid: boids) {
                boid.move(&boids, &obstacles, {x_size, y_size, z_size});
                boid.draw();
            }

            DrawBoundingBox({{0,0,0}, {x_size, y_size, z_size}}, BLACK);

        }
        EndMode3D();
        EndDrawing();


    }
}