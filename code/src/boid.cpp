//
// Created by Linus on 03.02.2022.
//

#include <cmath>

#include "../include/boids.h"

Boid::Boid(Vector2 pos, Vector2 dir, bool chosen_boid) :
        pos(pos), dir(dir), color({
                                          static_cast<unsigned char>(GetRandomValue(0, 255)),
                                          static_cast<unsigned char>(GetRandomValue(0, 255)),
                                          static_cast<unsigned char>(GetRandomValue(0, 255)),
                                          255
                                  }),
        chosen_boid(chosen_boid) {
}

void Boid::move(vector<Boid> *boids) {
    //shortened screen restraints
    auto w = float(GetScreenWidth());
    auto h = float(GetScreenHeight());

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
    Vector2 project_pos = pos + ray;
    //check if future position leaves borders
    if (!IsInRectangle(project_pos, {0, 0, w, h})) {
        //find a directin without collision
        for (int i = 0; i < 100; i++) {
            bool left_first = GetRandomValue(0, 1) == 0;
            Vector2 ray1 = Vector2Rotate(ray, float(left_first ? i : -i) * 2.f * PI / 100);
            Vector2 ray2 = Vector2Rotate(ray, float(left_first ? -i : i) * 2.f * PI / 100);
            if (IsInRectangle(pos + ray1, {0, 0, w, h})) {
                avoid_force = ray1;
                break;
            }
            if (IsInRectangle(pos + ray2, {0, 0, w, h})) {
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
        if(projection * avoid_force < 0){
            rule_force = rule_force - projection;
        }
    } else {
        //no obstacles in the way -> speed up!
        dir = Vector2ScaleUp(dir, speed);
    }

    //limit speed
    dir = Vector2ScaleDown(dir + avoid_force + rule_force, speed);

    //movement
    pos = pos + dir;

    //wrapping

//    if (pos.x < 0) pos.x += w;
//    if (pos.x > w) pos.x -= w;
//    if (pos.y < 0) pos.y += h;
//    if (pos.y > h) pos.y -= h;


}

void Boid::draw() const {
    DrawCircle(int(pos.x), int(pos.y), BOID_SIZE / 2, color);
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

