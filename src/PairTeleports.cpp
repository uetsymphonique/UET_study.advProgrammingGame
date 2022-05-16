#include "PairTeleports.hpp"
PairTeleports::PairTeleports(double x1, double y1 , double x2, double y2,int typeTele){
    posTele1 = Vec2d(x1,y1);
    posTele2 = Vec2d(x2,y2);
    this->typeTele = typeTele;
}
