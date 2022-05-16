#include "Wind.hpp"
Wind::Wind():LTexture(){};
void Wind::setSpeedScroll(int speedScroll){
    this->speedScroll=speedScroll;
}
void Wind::renderWind(SDL_Renderer* &gRenderer, int x,int y,double angle,SDL_RendererFlip flip){
    if(mWidth>200){
        for(int i = 0;i<7;i++)clip[i].w = mWidth;
    }
    render(gRenderer,x,y,&clip[scrollWind()],angle,NULL,flip);
}
int Wind::scrollWind(){
    int ret = countClip/speedScroll;
    countClip++;
    if(countClip>=speedScroll*7){
        countClip = 0;
    }
    return ret;
}
