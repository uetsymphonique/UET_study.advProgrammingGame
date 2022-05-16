#ifndef ICECLASS__
#define ICECLASS__
#include "LTexture.hpp"
class Ice: public LTexture{
private:
public:
    Ice();
};
struct InfoIce{
    Vec2d pos;
    int typeIce;
    InfoIce(double posX = 0.0,double posY = 0.0,int typeIce = 0){
        pos = Vec2d(posX,posY);
        if(typeIce<NUM_OF_TYPES_ICE) this->typeIce = typeIce;
        else this->typeIce = 0;
    }
};
#endif // ICECLASS__
