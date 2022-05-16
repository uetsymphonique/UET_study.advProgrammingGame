#ifndef VEC2D__
#define VEC2D__
//using as vector 2 dimensions or point in Decartes
#include "params.hpp"
struct Vec2d {
    double x, y;
    Vec2d(): x(0.0), y(0.0) {}
    Vec2d(double _x, double _y): x(_x), y(_y) {}
    double getScale() {
        return sqrt(x * x + y * y);
    }
    double getRatio() {
        return x / y;
    }
    Vec2d operator+(Vec2d other){
        return {x+other.x,y+other.y};
    }
    Vec2d operator/(double d){
        return {x/d,y/d};
    }
};

#endif // VEC2D__
