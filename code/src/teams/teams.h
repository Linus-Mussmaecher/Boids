//
// Created by Linus on 05/02/2022.
//

#ifndef BOIDS_TEAMS_H
#define BOIDS_TEAMS_H

#include "../basic/basic.h"

void runSimulation(int amountPerTeam);


class TeamBoid{
public:
    TeamBoid(const Vector2 &pos, const Vector2 &dir, Color color, uint8_t team);

    void move(vector<TeamBoid> *allies, vector<TeamBoid> *enemies, vector<Obstacle> *obstacles);
    void draw() const;
    void choose();

    [[nodiscard]] uint8_t getTeam() const;
    [[nodiscard]] uint8_t getHealth() const;
private:
    uint8_t team;
    uint8_t health;

    Color color;
    Vector2 pos;
    Vector2 dir;
    bool chosen_boid;
};



#endif //BOIDS_TEAMS_H
