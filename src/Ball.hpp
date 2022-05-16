#ifndef BALLCLASS__
#define BALLCLASS__
#include "Vec2d.hpp"
#include "LTexture.hpp"
#include "Block.hpp"
#include "Wind.hpp"
#include "InfoWind.hpp"
class Ball: public LTexture {
  public:
    int countTurnAround = 0;
    const double MIN_VEL_OUT_HOLE = 40;
    Ball() {};
    void freeBall();
    void handleMouseEvent(SDL_Event *e, SDL_Renderer* gRenderer, int &swings,int&totalSwings);
    void setPosBall(double x, double y);
    void standardlizePosBall();
    void moveBall(SDL_Rect blockRecList[], int numOfBlocks,
                  SDL_PairRect pairTeleRectList[], int numOfPairsTele,
                  vector<SDL_Rect> swampRectList, bool& isSwamped,
                  vector<SDL_Rect> iceRectList,
                  vector<SDL_Rect> windRectList, vector<InfoWind> windList,
                  bool hasSwamp = false, bool hasTeleport = false, bool hasWind = false, bool hasIce = false);
    void renderBall(SDL_Renderer* gRenderer);
    bool loadTextureFromFile(SDL_Renderer* gRenderer, std::string ballpath, std::string directpath,
                             std::string powerMeterBgPath, std::string powerMeterFgPath, std::string powerMeterOverlayPath,
                             std::string chargeMusicPath,std::string collisionMusicPath);
    double getScaleVelocity();
    Vec2d getPosBeforeSwing();
    void turnAround();
    bool checkCollisionWithDirect(SDL_Rect blockRect);
    int posBallWithBlock(SDL_Rect blockRect);
    SDL_FloatRect getFloatRect();
  private:
    static const int BALL_WIDTH = 16;
    static const int BALL_HEIGHT = 16;
    const double DECREASE_VEL = 1.05;
    const double MAX_SCALE_VEL = 40;

    //for set velocity and direction
    Vec2d initMousePos;
    Vec2d mousePos;
    Vec2d velocBall;
    double angleDirect;

    //status of ball
    bool isCharging = false;
    bool isDown = false;
    bool isTeleported = false;

    //More Texture...
    LTexture gDirect; //direction
    LTexture gPowermeterBg;
    LTexture gPowermeterFg[57];
    LTexture gPowermeterOverlay;

    //sfx
    Mix_Chunk *gChargeChunk = NULL;
    Mix_Chunk *gCollisionChunk = NULL;

    //pos before each swing
    Vec2d posBeforeSwing;

    enum POS_WITH_RECT{
        TOP_LEFT,
        TOP_MID,
        TOP_RIGHT,
        MID_RIGHT,
        BOT_RIGHT,
        BOT_MID,
        BOT_LEFT,
        MID_LEFT,
        CENTER
    };

};
#endif // BALLCLASS__
