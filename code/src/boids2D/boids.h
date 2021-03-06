//
// Created by Linus on 03.02.2022.
//

#ifndef BOIDS_BOIDS_H
#define BOIDS_BOIDS_H

#include "raylib.h"
#include "raymath.h"

#include "../ray_extend/ray_extend.h"

#include <array>
#include <vector>

#include <cmath>
#include <iostream>
#include <algorithm>

using std::array;
using std::vector;

void runBasic(int amount);

class Obstacle {
public:
    explicit Obstacle(Rectangle collider, Color c = DARKGRAY);
    void draw();

    [[nodiscard]] const Rectangle &getCollider() const;

private:
    Rectangle collider;
    Color color;
};


const int vision_range = 100;
const int vision_angle = 230;
const float steer_force = 0.8;
const float speed = 4.0;
const float BOID_SIZE = 8;

class Boid {
public:
    Boid(Vector2 pos, Vector2 dir);
    void move(vector<Boid> *boids, vector<Obstacle> *obstacles);
    void draw() const;
    void choose();
protected:
    Color color;
    Vector2 pos;
    Vector2 dir;
    bool chosen_boid;
};

bool checkRayCollision(Vector2 ray_start, Vector2 ray_end, vector<Obstacle> *obstacles);




#endif //BOIDS_BOIDS_H
