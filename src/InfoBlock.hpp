#ifndef INFOBLOCKCLASS__
#define INFOBLOCKCLASS__
#include "params.hpp"
#include "Vec2d.hpp"
struct InfoBlock{
    Vec2d pos;
    int typeBlock;
    InfoBlock(double posX = 0.0,double posY = 0.0,int typeBlock = 0){
        this->pos = Vec2d(posX,posY);
        if(typeBlock<NUM_OF_TYPES_BLOCK)this->typeBlock = typeBlock;
        else this->typeBlock = 0;
    }
};
#endif // INFOBLOCKSCLASS__
