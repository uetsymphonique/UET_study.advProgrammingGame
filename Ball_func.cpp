#include "Ball.hpp"

void Ball::setPosBall(double x,double y){
    setPos(x,y);
    velocBall = Vec2d(0.0,0.0);
    isCharging = false;
    isDown = false;
}
void Ball::handleMouseEvent(SDL_Event *e,SDL_Renderer* gRenderer){
    int x,y;
    if(e->type==SDL_MOUSEBUTTONDOWN){
        isDown = true;
        isCharging = true;
        SDL_GetMouseState(&x,&y);
        initMousePos=Vec2d(x,y);
    }
    if(e->type==SDL_MOUSEBUTTONUP){
        isDown = false;
    }
    if(isDown&&e->type==SDL_MOUSEMOTION){

        isCharging = true;
        SDL_GetMouseState(&x,&y);
        mousePos=Vec2d(x,y);
        velocBall=Vec2d((initMousePos.x-mousePos.x)/5,(initMousePos.y-mousePos.y)/5);
        //std::cout<<velocBall.x<<" "<<velocBall.y<<'\n';


        angleDirect = atan(1.0*velocBall.y/velocBall.x)*(180/3.1415)+90;
        if(velocBall.getScale()>56){
            double scale = velocBall.getScale();
            velocBall.x=velocBall.x/scale*56;
            velocBall.y=velocBall.y/scale*56;
        }
        //gPowerFgClip->w=int(velocBall.getScale());
        if(velocBall.x<0) angleDirect+=180;
        std::cout<<velocBall.getScale()<<'\n';
    }
    else {isCharging = false;}
}
void Ball::moveBall(){
    if(!isCharging){
        setPos(getPosX()+velocBall.x,getPosY()+velocBall.y);
        //normalize position of ball
        if(getPosX()<0)setPosX(0);
        if(getPosX()+BALL_WIDTH>SCREEN_WIDTH)setPosX(SCREEN_WIDTH-BALL_WIDTH);
        if(getPosY()<0)setPosY(0);
        if(getPosY()+BALL_HEIGHT>SCREEN_HEIGHT)setPosY(SCREEN_HEIGHT-BALL_HEIGHT);
        //collision with wall screen
        if(getPosX()==0||getPosX()+BALL_WIDTH==SCREEN_WIDTH){
            velocBall.x=0-velocBall.x;
        }
        if(getPosY()==0||getPosY()+BALL_HEIGHT==SCREEN_HEIGHT){
            velocBall.y=0-velocBall.y;
        }
        velocBall.x/=DECREASE_VEL;
        velocBall.y/=DECREASE_VEL;
    }
}
bool Ball::loadTextureFromFile(SDL_Renderer* gRenderer,std::string ballpath,std::string directpath,
                               std::string powermeterbgpath,std::string powermeterfgpath,std::string powerMeterOverlayPath){
    bool success = true;
    if(!loadFromFile(gRenderer,ballpath)){
        std::cout<<"load ball failed\n";success = false;
    }
    if(!gDirect.loadFromFile(gRenderer,directpath)){
        std::cout<<"load direct failed\n";success = false;
    }
    if(!gPowermeterBg.loadFromFile(gRenderer,powermeterbgpath)){
        std::cout<<"load PM_background failed\n";success = false;
    }
    if(!gPowermeterFg.loadFromFile(gRenderer,powermeterfgpath)){
        std::cout<<"load PM_background failed\n";success = false;
    }if(!gPowermeterOverlay.loadFromFile(gRenderer,powerMeterOverlayPath)){
        std::cout<<"load PM_overlay failed\n";success = false;
    }
    for(int i=0;i<57;i++){
        powerClips[i].x=404;
        powerClips[i].y=604;
        powerClips[i].h=8;
        powerClips[i].w=56;
    }
    return success;
}
void Ball::renderBall(SDL_Renderer* gRenderer){
    render(gRenderer);
    gPowermeterBg.render(gRenderer,400,600);
    gPowermeterOverlay.render(gRenderer,400,600);

    //std::cout<<gPowermeterFg.getHeight()<<'\n';// 8 56
    if(isCharging&&isDown){
        //std::cout<<gPowerFgClip->w<<'\n';
        int scale = velocBall.getScale();
        gPowermeterFg.render(gRenderer,404,604,&powerClips[scale]);
        gDirect.render(gRenderer,getPosX(),getPosY()+8-32,NULL,angleDirect);
    }
}
void Ball::freeBall(){
    free();
    gDirect.free();
    gPowermeterBg.free();
    gPowermeterFg.free();
    gPowermeterOverlay.free();
}
