//
// Created by Linus on 03.02.2022.
//

#include <array>
#include "../include/ray_extend.h"


float Vector2AngleUnsigned(Vector2 a, Vector2 b) {
    return std::acos((a.x * b.x + a.y * b.y) / (Vector2Length(a) * Vector2Length(b))) * 360 / (2 * PI);
}

float Vector2AngleSigned(Vector2 a, Vector2 b) {
    return atan2(a.x * b.y - b.x * a.y, a.x * a.y + b.x * b.y) * 360 / (2 * PI);
}

Vector2 Vector2ScaleTo(Vector2 v, float length) {
    float l = sqrt(v.x * v.x + v.y * v.y);
    return l == 0 ? v : length / l * v;
}

Vector2 Vector2ScaleUp(Vector2 v, float length) {
    return Vector2Length(v) >= length ? v : Vector2ScaleTo(v, length);
}

Vector2 Vector2ScaleDown(Vector2 v, float length) {
    return Vector2Length(v) <= length ? v : Vector2ScaleTo(v, length);
}

Vector2 Vector2ProjectOnto(Vector2 a, Vector2 b) {
    return b * (b * a) / (a * a);
}

bool CheckCollisionLineRect(Vector2 line_start, Vector2 line_end, Rectangle rect, Vector2 *collision_point) {
    //line starts in rect
    if (CheckCollisionPointRec(line_start, rect)) {
        *collision_point = line_start;
        return true;
    }
    //if not, it starts outside. Check all 4 sides to see if it enters

    bool collision = false;
    Vector2 last_collision = line_end;

    //define corners of the rectangle
    std::array<Vector2, 4> corners = {
            Vector2{rect.x, rect.y},
            Vector2{rect.x + rect.width, rect.y},
            Vector2{rect.x + rect.width, rect.y + rect.height},
            Vector2{rect.x, rect.y + rect.height},
            };

    //check collision for each side and remember collision closest to the starting point
    for(int i = 0; i < 4; i++) {
        if (CheckCollisionLines(line_start, line_end,
                                corners[i], corners[(i+1)%4],
                                &last_collision)
                                //check if new collision is closer than last collision (or, if no collision detected previously, the end point of the line
            && Vector2Distance(line_start, last_collision) < Vector2Distance(line_start, collision ? *collision_point : line_end)) {
            *collision_point = last_collision;
            collision = true;
        }
    }

    return collision;
}

bool CheckCollisionLineRect(Vector2 line_start, Vector2 line_end, Rectangle rect) {
    Vector2 _;
    return CheckCollisionLineRect(line_start, line_end, rect, &_);
}

Vector2 operator+(Vector2 a, Vector2 b) {
    return {a.x + b.x, a.y + b.y};
}

Vector2 operator-(Vector2 a, Vector2 b) {
    return {a.x - b.x, a.y - b.y};
}

Vector2 operator/(Vector2 v, float f) {
    return {v.x / f, v.y / f};
}

Vector2 operator*(Vector2 v, float f) {
    return {v.x * f, v.y * f};
}

Vector2 operator*(float f, Vector2 v) {
    return {f * v.x, f * v.y};
}

bool operator==(Vector2 a, Vector2 b) {
    return a.x == b.x && a.y == b.y;
}

//dot product
float operator*(Vector2 a, Vector2 b) {
    return Vector2DotProduct(a, b);
}