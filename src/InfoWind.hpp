#ifndef INFOWINDCLASS__
#define INFOWINDCLASS__
struct InfoWind{
    Vec2d pos;
    Vec2d velocWind;
    int typeWind;
    Vec2d VELOCITIES_OF_WIND[NUM_OF_TYPES_WIND] = {{2,-2},{2,-2},
    {1,-1},{1,-1},
    {-2,2},{-2,2},
    {-1,1},{-1,1},
    {2,2},{-2,-2}};
    InfoWind(double posX = 0.0,double posY = 0.0,int typeWind = 0){
        pos = Vec2d(posX,posY);
        this->typeWind = typeWind;
        velocWind = VELOCITIES_OF_WIND[typeWind];
    }
};
#endif // INFOWINDCLASS__
