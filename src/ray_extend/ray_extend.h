//
// Created by Linus on 03.02.2022.
//

#ifndef BOIDS_RAY_EXTEND_H
#define BOIDS_RAY_EXTEND_H

#include "raylib.h"
#include "raymath.h"
#include <cmath>


//returns the smallest angle between a and b in degrees. Result will be between 0 and 180
float Vector2AngleUnsigned(Vector2 a, Vector2 b);

//returns the signed angle between vectors a and b in degrees. Result will be between -180 and 180 degrees
float Vector2AngleSigned(Vector2 a, Vector2 b);

//returns a vector with length length pointing into direction v
Vector2  Vector2ScaleTo(Vector2 v, float length);

//scales the vector to the desired size iff it is currently shorter
Vector2 Vector2ScaleUp(Vector2 v, float length);

//scales the vector to the desired size iff it is currently longer
Vector2 Vector2ScaleDown(Vector2 v, float length);

//returns the perpendicular projection of vector a onto base vector b
Vector2 Vector2ProjectOnto(Vector2 a, Vector2 b);

//checks if the line between the two vectors collides with the rectangle
//returns the collision point by reference. If the line starts inside the rectangle, the collision point is the starting point
bool CheckCollisionLineRect(Vector2 line_start, Vector2 line_end, Rectangle rect, Vector2* collision_point);

//checks if the line between the two vectors collides with the rectangle
bool CheckCollisionLineRect(Vector2 line_start, Vector2 line_end, Rectangle rect);

Vector2 operator*(float f, Vector2 v);
float scalar_product(Vector2 a, Vector2 b);


//returns a vector with length length pointing into direction v
Vector3  Vector3ScaleTo(Vector3 v, float length);

//scales the vector to the desired size iff it is currently shorter
Vector3 Vector3ScaleUp(Vector3 v, float length);

//scales the vector to the desired size iff it is currently longer
Vector3 Vector3ScaleDown(Vector3 v, float length);

//returns the perpendicular projection of vector a onto base vector b
Vector3 Vector3ProjectOnto(Vector3 a, Vector3 b);

Vector3 operator*(float f, Vector3 v);
bool operator==(Vector3 a, Vector3 b);
float scalar_product(Vector3 a, Vector3 b);


#endif //BOIDS_RAY_EXTEND_H
