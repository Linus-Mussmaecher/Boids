//
// Created by Linus on 05/02/2022.
//

#include "teams.h"

void runSimulation(int amountPerTeam){
    vector<TeamBoid> red_team{};
    vector<TeamBoid> blue_team{};
    red_team.reserve(amountPerTeam);
    blue_team.reserve(amountPerTeam);
    for(int i = 0; i < amountPerTeam; i++){
        red_team.push_back(
                TeamBoid(
                        {
                                float(GetRandomValue(0, GetScreenWidth()/2)),
                                float(GetRandomValue(0, GetScreenHeight()))
                        },
                        Vector2Rotate({0, speed}, 2 * PI * float(GetRandomValue(0, 100)) / 100),
                        RED, 0
                ));
        blue_team.push_back(
                TeamBoid(
                        {
                                float(GetRandomValue(GetScreenWidth()/2, GetScreenWidth())),
                                float(GetRandomValue(0, GetScreenHeight()))
                        },
                        Vector2Rotate({0, speed}, 2 * PI * float(GetRandomValue(0, 100)) / 100),
                        BLUE,1
                ));
    }

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

            for (TeamBoid &boid: red_team) {
                boid.move(&red_team, &blue_team, &obstacles);
                boid.draw();
            }

            for (TeamBoid &boid: blue_team) {
                boid.move(&blue_team, &red_team, &obstacles);
                boid.draw();
            }

            red_team.erase(std::remove_if(red_team.begin(), red_team.end(), [](TeamBoid &tb){return tb.getHealth() <= 0;}), red_team.end());
            blue_team.erase(std::remove_if(blue_team.begin(), blue_team.end(), [](TeamBoid &tb){return tb.getHealth() <= 0;}), blue_team.end());

        }
        EndDrawing();


    }
}