//
// Created by Linus on 08.02.2022.
//

#include "boids3D.h"

Boid3D::Boid3D(Vector3 pos, Vector3 dir) :
pos(pos),
dir(dir),
color(BLUE),
chosen_boid(false)
{

}

void Boid3D::move(vector<Boid3D> *boids, vector<Obstacle3D> *obstacles, Vector3 size) {
    //loop over all boids
    Vector3 mate_pos_sum = Vector3Zero();
    Vector3 mate_dir_sum = Vector3Zero();
    Vector3 mate_avoid_force = Vector3Zero();
    int mate_count = 0;

    for (Boid3D b: *boids) {
        //for those visible, add their values to the average calculations
        if (Vector3Distance(b.pos, pos) < vision_range_3D){

            mate_pos_sum = mate_pos_sum + b.pos;
            mate_dir_sum = mate_dir_sum + b.dir;
            //radial separation force
            mate_avoid_force = mate_avoid_force +
                               ((pos == b.pos) ? -1 * dir : (pos - b.pos) / Vector3Distance(pos, b.pos)) * steer_force_3D;
            mate_count++;
        }
    }

    Vector3 rule_force = Vector3Zero();

    if (mate_count != 0) {
        Vector3 mate_pos_avg = mate_pos_sum / float(mate_count);
        Vector3 mate_dir_avg = mate_dir_sum / float(mate_count);

        //separation
        Vector3 separation_force = mate_avoid_force * 0.3;
        //alignment
        Vector3 alignment_force = Vector3ScaleTo(mate_dir_avg, steer_force_3D * 0.5f);
        //cohesion
        Vector3 cohesion_force = Vector3ScaleTo(mate_pos_avg - pos, steer_force_3D * 0.9f);

        rule_force =
                separation_force +
                alignment_force +
                cohesion_force;
    }

//    //avoid walls
//    Vector3 avoid_force = Vector3Zero();
//    //calculate future position
//    Vector3 ray = Vector3ScaleTo(dir, vision_range_3D);
//    //check if future position leaves borders
//    if (checkRayCollision(pos, pos + ray,  obstacles)) {
//        avoid_force = Vector2ScaleTo(dir, steer_force_3D); // set a default value. If the boid is stuck inside an obstacle, it will thus push out
//        //find a directin without collision
//        for (int i = 0; i < 100; i++) {
//            //randomly decide wether to check the left or right option first
//            bool left_first = GetRandomValue(0, 1) == 0;
//            //generate two ray pointing to the left and right
//            Vector2 ray1 = Vector2Rotate(ray, float(left_first ? i : -i) * 2.f * PI / 100);
//            Vector2 ray2 = Vector2Rotate(ray, float(left_first ? -i : i) * 2.f * PI / 100);
//
//            if (!checkRayCollision(pos, pos + ray1,  obstacles)) {
//                avoid_force = ray1;
//                break;
//            }
//            if (!checkRayCollision(pos, pos + ray2,  obstacles)) {
//                avoid_force = ray2;
//                break;
//            }
//        }
//        //apply force to change dir to the required direction, possible even slowing down the boid
//        avoid_force = Vector2ScaleTo(avoid_force, speed) - dir;
//        //limit steering per frame
//        if (Vector2Length(avoid_force) > steer_force)
//            avoid_force = Vector2ScaleTo(avoid_force, steer_force);
//
//        //if rules are pushing into the environment, avoid that part of the force
//        Vector2 projection = Vector2ProjectOnto(rule_force, avoid_force);
//        //if the dot product is negative (the vectors are pointing in opposite direction, remove that part of the rule_force
//        if (projection * avoid_force < 0) {
//            rule_force = rule_force - projection;
//        }
//    } else {
//        //no obstacles in the way -> speed up!
//        dir = Vector2ScaleUp(dir, speed);
//    }

    //limit speed
    dir = Vector3ScaleDown(dir +  rule_force, speed_3D);

    //movement
    Vector3 next_pos = pos + dir;
//    for(Obstacle &o : *obstacles){
//        if(CheckCollisionLineRect(pos, pos+dir, o.getCollider(), &next_pos)){
//            next_pos = next_pos - Vector2ScaleTo(dir, 1);
//        } //if we would collide with this one, just move until collision point and a bit back
//    }
    pos = next_pos;


    if(pos.x > size.x) pos.x = 0;
    if(pos.y > size.y) pos.y = 0;
    if(pos.z > size.z) pos.z = 0;
    if(pos.x < 0) pos.x = size.x;
    if(pos.y < 0) pos.y = size.y;
    if(pos.z < 0) pos.z = size.z;
}

void Boid3D::draw() const {
    DrawSphere(pos, BOID_SIZE_3D, color);
    if(chosen_boid) {
        DrawLine3D(pos, pos + vision_range_3D * Vector3Normalize(dir), {255, 200, 200, 150});
    }
}

void Boid3D::choose() {
    chosen_boid = true;
}
