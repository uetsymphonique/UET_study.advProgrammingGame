#ifndef VEC2D__
#define VEC2D__
//using as vector 2 dimensions or point in Decartes
#include "params.hpp"
struct Vec2d{
    double x,y;
    Vec2d():x(0.0),y(0.0){}
    Vec2d(double _x,double _y):x(_x),y(_y){}
    double getScale(){
        return sqrt(x*x+y*y);
    }
    double getRatio(){
        return x/y;
    }
};
#endif // VEC2D__
