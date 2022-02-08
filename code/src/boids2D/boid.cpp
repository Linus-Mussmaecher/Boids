//
// Created by Linus on 03.02.2022.
//

#include "boids.h"

Boid::Boid(Vector2 pos, Vector2 dir) :
        pos(pos), dir(dir), color({
                                          static_cast<unsigned char>(GetRandomValue(0, 255)),
                                          static_cast<unsigned char>(GetRandomValue(0, 255)),
                                          static_cast<unsigned char>(GetRandomValue(0, 255)),
                                          255
                                  }),
        chosen_boid(false) {
}

void Boid::move(vector<Boid> *boids, vector<Obstacle> *obstacles) {
    //loop over all boids
    Vector2 mate_pos_sum = Vector2Zero();
    Vector2 mate_dir_sum = Vector2Zero();
    Vector2 mate_avoid_force = Vector2Zero();
    int mate_count = 0;

    for (Boid b: *boids) {
        //for those visible, add their values to the average calculations
        if (Vector2Distance(b.pos, pos) < vision_range &&
            abs(Vector2AngleSigned(dir, b.pos - pos)) < float(vision_angle) / 2) {

            mate_pos_sum = mate_pos_sum + b.pos;
            mate_dir_sum = mate_dir_sum + b.dir;
            //radial separation force
            mate_avoid_force = mate_avoid_force +
                               ((pos == b.pos) ? -1 * dir : (pos - b.pos) / Vector2Distance(pos, b.pos)) * steer_force;
            mate_count++;
        }
    }

    Vector2 rule_force = Vector2Zero();

    if (mate_count != 0) {
        Vector2 mate_pos_avg = mate_pos_sum / float(mate_count);
        Vector2 mate_dir_avg = mate_dir_sum / float(mate_count);

        //separation
        Vector2 separation_force = mate_avoid_force * 0.3;
        //alignment
        Vector2 alignment_force = Vector2ScaleTo(mate_dir_avg, steer_force * 0.5f);
        //cohesion
        Vector2 cohesion_force = Vector2ScaleTo(mate_pos_avg - pos, steer_force * 0.9f);

        rule_force =
                separation_force +
                alignment_force +
                cohesion_force;
    }

    //avoid walls
    Vector2 avoid_force = Vector2Zero();
    //calculate future position
    Vector2 ray = Vector2ScaleTo(dir, vision_range);
    //check if future position leaves borders
    if (checkRayCollision(pos, pos + ray,  obstacles)) {
        avoid_force = Vector2ScaleTo(dir, steer_force); // set a default value. If the boid is stuck inside an obstacle, it will thus push out
        //find a directin without collision
        for (int i = 0; i < 100; i++) {
            //randomly decide wether to check the left or right option first
            bool left_first = GetRandomValue(0, 1) == 0;
            //generate two ray pointing to the left and right
            Vector2 ray1 = Vector2Rotate(ray, float(left_first ? i : -i) * 2.f * PI / 100);
            Vector2 ray2 = Vector2Rotate(ray, float(left_first ? -i : i) * 2.f * PI / 100);

            if (!checkRayCollision(pos, pos + ray1,  obstacles)) {
                avoid_force = ray1;
                break;
            }
            if (!checkRayCollision(pos, pos + ray2,  obstacles)) {
                avoid_force = ray2;
                break;
            }
        }
        //apply force to change dir to the required direction, possible even slowing down the boid
        avoid_force = Vector2ScaleTo(avoid_force, speed) - dir;
        //limit steering per frame
        if (Vector2Length(avoid_force) > steer_force)
            avoid_force = Vector2ScaleTo(avoid_force, steer_force);

        //if rules are pushing into the environment, avoid that part of the force
        Vector2 projection = Vector2ProjectOnto(rule_force, avoid_force);
        //if the dot product is negative (the vectors are pointing in opposite direction, remove that part of the rule_force
        if (projection * avoid_force < 0) {
            rule_force = rule_force - projection;
        }
    } else {
        //no obstacles in the way -> speed up!
        dir = Vector2ScaleUp(dir, speed);
    }

    //limit speed
    dir = Vector2ScaleDown(dir + avoid_force + rule_force, speed);

    //movement
    Vector2 next_pos = pos + dir;
    for(Obstacle &o : *obstacles){
        if(CheckCollisionLineRect(pos, pos+dir, o.getCollider(), &next_pos)){
            next_pos = next_pos - Vector2ScaleTo(dir, 1);
        } //if we would collide with this one, just move until collision point and a bit back
    }
    pos = next_pos;

}

const Color c1 = GREEN;//{166,200,255,255};
const Color c2 = BLUE;//{0,98,255,255};

void Boid::draw() const {

    float f = (1 + Vector2DotProduct({1,0}, Vector2Normalize(dir)))/2.f;
    DrawCircle(int(pos.x), int(pos.y), BOID_SIZE / 2, {
        static_cast<unsigned char>(float(c1.r) + f * float(c2.r - c1.r)),
        static_cast<unsigned char>(float(c1.g) + f * float(c2.g - c1.g)),
        static_cast<unsigned char>(float(c1.b) + f * float(c2.b - c1.b)),
        255
    });
    if (chosen_boid) {
        DrawCircle(int(pos.x), int(pos.y), vision_range, {255, 255, 255, 100});
        Vector2 ray = Vector2ScaleTo(dir, vision_range);
        Vector2 project_pos = pos + ray;
        DrawLine(int(pos.x), int(pos.y), int(project_pos.x), int(project_pos.y), {255, 200, 200, 150});
    }
}

void Boid::choose() {
    chosen_boid = true;
}

