#ifndef WINDCLASS__
#define WINDCLASS__
#include "LTexture.hpp"
class Wind: public LTexture{
private:
    SDL_Rect clip[7]={{0,0,200,64},{0,32,200,64},{0,32*2,200,64},{0,32*3,200,64},{0,32*4,200,64},{0,32*5,200,64},{0,32*6,200,64}};
    int countClip = 0;
    int speedScroll;
public:
    Wind();
    void setSpeedScroll(int speedScroll);
    void renderWind(SDL_Renderer* &gRenderer,int x,int y,double angle,SDL_RendererFlip flip);
    int scrollWind();
};
#endif // WINDCLASS__
