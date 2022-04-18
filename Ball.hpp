#ifndef BALLCLASS__
#define BALLCLASS__
#include "Vec2d.hpp"
#include "LTexture.hpp"
#include "Block.hpp"
class Ball:public LTexture{
public:
    Ball(){
    };
    void freeBall();
    void handleMouseEvent(SDL_Event *e,SDL_Renderer* gRenderer);
    void setPosBall(double x,double y);
    void standardlizePosBall();
    void moveBall(SDL_Rect blockRecList[],int numOfBlocks);
    void renderBall(SDL_Renderer* gRenderer);
    bool loadTextureFromFile(SDL_Renderer* gRenderer,std::string ballpath,std::string directpath,
                               std::string powerMeterBgPath,std::string powerMeterFgPath,std::string powerMeterOverlayPath);
private:
    static const int BALL_WIDTH = 16;
    static const int BALL_HEIGHT = 16;
    const double DECREASE_VEL = 1.05;
    const double MIN_VEL_OUT_HOLE = 100;
    //for set velocity and direction
    Vec2d initMousePos;Vec2d mousePos;
    Vec2d velocBall;
    double angleDirect;

    //status of ball
    bool isCharging = false;bool isDown = false;

    //More Texture...
    LTexture gDirect; //direction
    LTexture gPowermeterBg;
    LTexture gPowermeterFg[57];
    LTexture gPowermeterOverlay;
};
#endif // BALLCLASS__
