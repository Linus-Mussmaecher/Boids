//
// Created by Linus on 08.02.2022.
//

#ifndef BOIDS_BOIDS3D_H
#define BOIDS_BOIDS3D_H

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

void run3D(int amount);

class Obstacle3D {
public:
    explicit Obstacle3D(BoundingBox collider, Color c = DARKGRAY);
    void draw();

    [[nodiscard]] const BoundingBox &getCollider() const;

private:
    BoundingBox collider;
    Color color;
};


const int vision_range_3D = 50;
const float steer_force_3D = 0.8;
const float speed_3D = 4.0;
const float BOID_SIZE_3D = 3;

class Boid3D {
public:
    Boid3D(Vector3 pos, Vector3 dir);
    void move(vector<Boid3D> *boids, vector<Obstacle3D> *obstacles, Vector3 size);
    void draw() const;
    void choose();
protected:
    Color color;
    Vector3 pos;
    Vector3 dir;
    bool chosen_boid;
};



#endif //BOIDS_BOIDS3D_H
