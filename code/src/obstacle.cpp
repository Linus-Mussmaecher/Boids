//
// Created by Linus on 05.02.2022.
//

#include "../include/boids.h"



Obstacle::Obstacle(Rectangle collider, Color c) :
        collider(collider), color(c){
}

void Obstacle::draw() {
    DrawRectangle(int(collider.x), int(collider.y), int(collider.width), int(collider.height), color);
}

const Rectangle &Obstacle::getCollider() const {
    return collider;
}
