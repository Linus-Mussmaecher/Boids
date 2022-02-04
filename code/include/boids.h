//
// Created by Linus on 03.02.2022.
//

#ifndef BOIDS_BOIDS_H
#define BOIDS_BOIDS_H

#include "raylib.h"
#include "raymath.h"

#include "ray_extend.h"

#include <array>
#include <vector>

#include <iostream>
#include <algorithm>

using std::array;
using std::vector;

const int vision_range = 100;
const int vision_angle = 230;
const float steer_force = 0.8;
const float speed = 4.0;
const float BOID_SIZE = 8;

class Boid {
public:
    Boid(Vector2 pos, Vector2 dir, bool chosen_boid = false);
    void move(vector<Boid> *boids);
    void draw() const;
    void choose();
private:
    Color color;
    Vector2 pos;
    Vector2 dir;
    bool chosen_boid;
};





#endif //BOIDS_BOIDS_H
