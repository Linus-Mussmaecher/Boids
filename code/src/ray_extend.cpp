//
// Created by Linus on 03.02.2022.
//

#include "../include/ray_extend.h"



float Vector2AngleUnsigned(Vector2 a, Vector2 b){
    return std::acos((a.x * b.x + a.y * b.y)/(Vector2Length(a) * Vector2Length(b))) * 360 / (2 * PI);
}

float Vector2AngleSigned(Vector2 a, Vector2 b){
    return atan2(a.x*b.y-b.x*a.y,a.x*a.y+b.x*b.y)  * 360 / (2 * PI);
}

Vector2  Vector2ScaleTo(Vector2 v, float length){
    float l = sqrt(v.x * v.x + v.y * v.y);
    return l == 0 ? v : length/l * v;
}
Vector2 Vector2ScaleUp(Vector2 v, float length){
    return Vector2Length(v) >= length ? v : Vector2ScaleTo(v, length);
}

Vector2 Vector2ScaleDown(Vector2 v, float length){
    return Vector2Length(v) <= length ? v : Vector2ScaleTo(v, length);
}

Vector2 Vector2ProjectOnto(Vector2 a, Vector2 b){
    return b * (b * a)/(a*a);
}

bool IsInRectangle(Vector2 v, Rectangle rect){
    return v.x >= rect.x && v.x <= rect.x + rect.width && v.y >= rect.y && v.y <= rect.y + rect.height;
}

Vector2 operator+(Vector2 a, Vector2 b){
    return {a.x + b.x, a.y + b.y};
}
Vector2 operator-(Vector2 a, Vector2 b){
    return {a.x - b.x, a.y - b.y};
}
Vector2 operator/(Vector2 v, float f){
    return {v.x /f, v.y / f};
}
Vector2 operator*(Vector2 v, float f){
    return {v.x * f, v.y * f};
}
Vector2 operator*(float f, Vector2 v){
    return {f * v.x, f* v.y};
}
bool operator==(Vector2 a, Vector2 b){
    return a.x == b.x && a.y == b.y;
}

//dot product
float operator*(Vector2 a, Vector2 b){
    return Vector2DotProduct(a,b);
}