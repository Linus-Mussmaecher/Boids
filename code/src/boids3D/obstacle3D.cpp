//
// Created by Linus on 08.02.2022.
//


#include "boids3D.h"

Obstacle3D::Obstacle3D(BoundingBox collider, Color c) :
        collider(collider),
        color(c){

}

void Obstacle3D::draw() {
    if(color.a != 0) {
        DrawCube(collider.min,
                 (collider.max - collider.min).x,
                 (collider.max - collider.min).x,
                 (collider.max - collider.min).x,
                 color
        );
    }
}

const BoundingBox &Obstacle3D::getCollider() const {
    return collider;
}

