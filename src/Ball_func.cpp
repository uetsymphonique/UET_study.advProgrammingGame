#include "Ball.hpp"

void Ball::setPosBall(double x, double y) {
    setPos(x, y);
    velocBall = Vec2d(0.0, 0.0);
    isCharging = false;
    isDown = false;
}
void Ball::handleMouseEvent(SDL_Event *e, SDL_Renderer* gRenderer, int &swings,int& totalSwings) {
    int x, y;
    if(e->type == SDL_MOUSEBUTTONDOWN) {
        isDown = true;
        isCharging = true;
        SDL_GetMouseState(&x, &y);
        initMousePos = Vec2d(x, y);
    }
    if(e->type == SDL_MOUSEBUTTONUP) {
        if(isCharging) {
            Mix_PlayChannel(-1, gChargeChunk, 0);
            swings++;
            totalSwings++;
        }
        isCharging = false;
        isDown = false;

    }
    if(isDown && e->type == SDL_MOUSEMOTION) {
        countTurnAround = 0;
        posBeforeSwing = getPos();
        isCharging = true;
        SDL_GetMouseState(&x, &y);
        mousePos = Vec2d(x, y);
        velocBall = Vec2d((initMousePos.x - mousePos.x) / 5, (initMousePos.y - mousePos.y) / 5);
        //std::cout<<velocBall.x<<" "<<velocBall.y<<'\n';


        angleDirect = atan(1.0 * velocBall.y / velocBall.x) * (180 / 3.1415) + 90;
        if(velocBall.getScale() > MAX_SCALE_VEL) {
            double scale = velocBall.getScale();
            velocBall.x = velocBall.x / scale * MAX_SCALE_VEL;
            velocBall.y = velocBall.y / scale * MAX_SCALE_VEL;
        }
        //gPowerFgClip->w=int(velocBall.getScale());
        if(velocBall.x < 0) angleDirect += 180;
        //std::cout<<velocBall.getScale()<<'\n';
    } else {
        isCharging = false;
    }
}
bool Ball::checkCollisionWithDirect(SDL_Rect blockRect) {
    int posWithBlock = posBallWithBlock(blockRect);
    switch(posWithBlock) {
    case TOP_MID: {

    } break;
    }
}
void Ball::moveBall(SDL_Rect blockRectList[], int numOfBlocks,
                    SDL_PairRect pairTeleRectList[], int numOfPairsTele,
                    vector<SDL_Rect> swampRectList, bool& isSwamped,
                    vector<SDL_Rect> iceRectList,
                    vector<SDL_Rect> windRectList, vector<InfoWind> windList,
                    bool hasSwamp, bool hasTeleport, bool hasWind, bool hasIce) {

    if(!isCharging) {
        if(abs(velocBall.y) <= 0.0001) {
            if(velocBall.y >= 0) velocBall.y = 0.0001;
            else velocBall.y = -0.0001;
        }
        Vec2d tempPos = pos + velocBall;
        bool collisionX = false;
        bool collisionY = false;
        bool moved = false;
        //collision with wall
        if(tempPos.x <= 0) {
            pos.x = 0;
            moved = true;
            velocBall.x *= -1.0;
        }
        if(tempPos.x + BALL_WIDTH >= SCREEN_WIDTH) {
            pos.x = SCREEN_WIDTH - BALL_WIDTH;
            moved = true;
            velocBall.x *= -1.0;
        }
        if(tempPos.y <= 0) {
            pos.y = 0;
            moved = true;
            velocBall.y *= -1.0;
        }
        if(tempPos.y + BALL_HEIGHT >= SCREEN_HEIGHT) {
            pos.y = SCREEN_HEIGHT - BALL_HEIGHT;
            moved = true;
            velocBall.y *= -1.0;
        }
        SDL_FloatRect tempRect = SDL_FloatRect(tempPos.x, tempPos.y, BALL_WIDTH, BALL_HEIGHT);
        bool hasCollision = false;
        for(int i = 0; i < numOfBlocks; i++) {
            if(checkCollision(tempRect, blockRectList[i])) {
                std::cout << "found collision\n";
                int topBlock = blockRectList[i].y;
                int botBlock = blockRectList[i].y + blockRectList[i].h;
                int leftBlock = blockRectList[i].x;
                int rightBlock = blockRectList[i].x + blockRectList[i].w;
                double ratioV = velocBall.getRatio();
                std::cerr << "posBallWithBlock: " << posBallWithBlock(blockRectList[i]) << '\n';
                moved = true;
                switch(posBallWithBlock(blockRectList[i])) {
                case TOP_MID: {
                    if(velocBall.y >= 0) {
                        pos.x += (topBlock - BALL_HEIGHT - pos.y) * ratioV;
                        pos.y = topBlock - BALL_HEIGHT;
                        velocBall.y *= -1.0;
                    }
                }
                break;
                case BOT_MID: {
                    if(velocBall.y <= 0) {
                        pos.x += (botBlock - pos.y) * ratioV;
                        pos.y = botBlock;
                        velocBall.y *= -1.0;
                    }
                }
                break;
                case MID_LEFT: {
                    if(velocBall.x >= 0) {
                        pos.y += (leftBlock - BALL_WIDTH - pos.x) / ratioV;
                        pos.x = leftBlock - BALL_WIDTH;
                        velocBall.x *= -1.0;
                    }
                }
                break;
                case MID_RIGHT: {
                    if(velocBall.x <= 0) {
                        pos.y += (rightBlock - pos.x) / ratioV;
                        pos.x = rightBlock;
                        velocBall.x *= -1.0;
                    }
                }
                break;
                case TOP_LEFT: {
                    if(velocBall.x >= 0 && velocBall.y >= 0) {
                        if((tempRect.getRight() - leftBlock) - (tempRect.getBottom() - topBlock) > 0.01) {
                            pos.x += (topBlock - BALL_HEIGHT - pos.y) * ratioV;
                            pos.y = topBlock - BALL_HEIGHT;
                            velocBall.y *= -1.0;
                        } else if((tempRect.getRight() - leftBlock) - (tempRect.getBottom() - topBlock) < -0.01) {
                            pos.y += (leftBlock - BALL_WIDTH - pos.x) / ratioV;
                            pos.x = leftBlock - BALL_WIDTH;
                            velocBall.x *= -1.0;
                        } else {
                            pos.y = topBlock - BALL_HEIGHT;
                            pos.x = leftBlock - BALL_WIDTH;
                            velocBall.x *= -1.0;
                            velocBall.y *= -1.0;
                        }
                    }
                }
                break;
                case BOT_RIGHT: {
                    if(velocBall.x <= 0 && velocBall.y <= 0) {
                        if((tempRect.getLeft() - leftBlock) - (tempRect.getTop() - topBlock) < -0.01) {
                            pos.x += (botBlock - pos.y) * ratioV;
                            pos.y = botBlock;
                            velocBall.y *= -1.0;
                        } else if((tempRect.getLeft() - leftBlock) - (tempRect.getTop() - topBlock) > 0.01) {
                            pos.y += (rightBlock - pos.x) / ratioV;
                            pos.x = rightBlock;
                            velocBall.x *= -1.0;
                        } else {
                            pos.y = botBlock;
                            velocBall.y *= -1.0;
                            pos.x = rightBlock;
                            velocBall.x *= -1.0;
                        }
                    }
                }
                break;
                case TOP_RIGHT: {
                    if(velocBall.x <= 0 && velocBall.y >= 0) {
                        if((rightBlock - tempRect.getLeft()) - (tempRect.getBottom() - topBlock) > 0.01) {
                            pos.x += (topBlock - BALL_HEIGHT - pos.y) * ratioV;
                            pos.y = topBlock - BALL_HEIGHT;
                            velocBall.y *= -1.0;
                        } else if((rightBlock - tempRect.getLeft()) - (tempRect.getBottom() - topBlock) < -0.01) {
                            pos.y += (rightBlock - pos.x) / ratioV;
                            pos.x = rightBlock;
                            velocBall.x *= -1.0;
                        } else {
                            pos.y = topBlock - BALL_HEIGHT;
                            velocBall.y *= -1.0;
                            pos.x = rightBlock;
                            velocBall.x *= -1.0;
                        }
                    }
                }
                break;
                case BOT_LEFT: {
                    if(velocBall.x >= 0 && velocBall.y <= 0) {
                        if((rightBlock - tempRect.getRight()) - (tempRect.getTop() - topBlock) > 0.01) {
                            pos.y += (leftBlock - BALL_WIDTH - pos.x) / ratioV;
                            pos.x = leftBlock - BALL_WIDTH;
                            velocBall.x *= -1.0;
                        } else if((rightBlock - tempRect.getRight()) - (tempRect.getTop() - topBlock) < -0.01) {
                            pos.x += (botBlock - pos.y) * ratioV;
                            pos.y = botBlock;
                            velocBall.y *= -1.0;
                        } else {
                            pos.x = leftBlock - BALL_WIDTH;
                            velocBall.x *= -1.0;
                            pos.y = botBlock;
                            velocBall.y *= -1.0;
                        }
                    }
                }
                break;
                }
                Mix_PlayChannel(-1,gCollisionChunk,0);
                break;
            }
        }
        if(!moved) {
            pos = pos + velocBall;
        }

        //collision with teleports
        if(int(velocBall.getScale()) > 0 && hasTeleport) {
            for(int i = 0; i < numOfPairsTele; i++) {
                if(checkCollision(getFloatRect(), pairTeleRectList[i].rect1)) {
                    setPosX(pairTeleRectList[i].rect2.x);
                    setPosY(pairTeleRectList[i].rect2.y);
                    SDL_FloatRect tempRect = getFloatRect();
                    tempRect.x += velocBall.x / DECREASE_VEL;
                    tempRect.y += velocBall.y / DECREASE_VEL;
                    if(checkCollision(tempRect, pairTeleRectList[i].rect2)) {
                        pos.x += velocBall.x / abs(velocBall.x) * 20;
                        pos.y += velocBall.y / abs(velocBall.y) * 20;
                        //velocBall.x=0;velocBall.y=0;
                    }
                    break;
                } else if(checkCollision(getFloatRect(), pairTeleRectList[i].rect2)) {
                    setPosX(pairTeleRectList[i].rect1.x);
                    setPosY(pairTeleRectList[i].rect1.y);
                    SDL_FloatRect tempRect = getFloatRect();
                    tempRect.x += velocBall.x / DECREASE_VEL;
                    tempRect.y += velocBall.y / DECREASE_VEL;
                    if(checkCollision(tempRect, pairTeleRectList[i].rect1)) {
                        pos.x += velocBall.x / abs(velocBall.x) * 20;
                        pos.y += velocBall.y / abs(velocBall.y) * 20;
                        //velocBall.x=0;velocBall.y=0;
                    }
                    break;
                }
            }

        }
        if(hasSwamp) {
            for(int i = 0 ; i < swampRectList.size(); i++) {
                if(checkCollisionCircleWithRect(getRect(), swampRectList[i])) {
                    isSwamped = true;
                    setPosBall(swampRectList[i].x + swampRectList[i].w / 2.0 - BALL_WIDTH / 2, swampRectList[i].y + swampRectList[i].h / 2.0 - BALL_HEIGHT / 2);
                    break;
                }
            }
        }
        velocBall.x /= DECREASE_VEL;
        velocBall.y /= DECREASE_VEL;
        if(hasIce) {
            for(int i = 0; i < iceRectList.size(); i++) {
                if(checkCollisionCircleWithRect(getRect(), iceRectList[i])) {
                    velocBall.x *= (DECREASE_VEL + 0.02);
                    velocBall.y *= (DECREASE_VEL + 0.02);
                    break;
                }
            }
        }
        if(hasWind) {
            for(int i = 0; i < windRectList.size(); i++) {
                if(checkCollision(getFloatRect(), windRectList[i])) {
                    velocBall = velocBall + windList[i].velocWind;
                    break;
                }
            }
        }
    }

}
int Ball:: posBallWithBlock(SDL_Rect blockRect) {
    int topRect, botRect, leftRect, rightRect;
    topRect = blockRect.y;
    botRect = blockRect.y + blockRect.h;
    leftRect = blockRect.x;
    rightRect = blockRect.x + blockRect.w;
    SDL_FloatRect ballRect = getFloatRect();
    if(ballRect.getRight() <= leftRect) {
        if(ballRect.getBottom() <= topRect) {
            std::cout << "top_left\n";
            return TOP_LEFT;
        }
        if(ballRect.getTop() <= botRect) {
            std::cout << "mid_left\n";
            return MID_LEFT;
        }
        std::cout << "bot_left\n";
        return BOT_LEFT;
    }
    if(ballRect.getLeft() <= rightRect) {
        if(ballRect.getBottom() <= topRect) {
            std::cout << "top_mid\n";
            return TOP_MID;
        }
        if(ballRect.getTop() <= botRect) {
            std::cout << "center\n";
            return CENTER;
        }
        std::cout << "bot_mid\n";
        return BOT_MID;
    }
    if(ballRect.getBottom() <= topRect) {
        std::cout << "top_right\n";
        return TOP_RIGHT;
    }
    if(ballRect.getTop() <= botRect) {
        std::cout << "mid_right\n";
        return MID_RIGHT;
    }
    std::cout << "bot_right\n";
    return BOT_RIGHT;
}
bool Ball::loadTextureFromFile(SDL_Renderer* gRenderer, std::string ballpath, std::string directpath,
                               std::string powermeterbgpath, std::string powermeterfgpath, std::string powerMeterOverlayPath,
                               std::string chargeMusicPath,std::string collisionMusicPath) {
    bool success = true;
    if(!loadFromFile(gRenderer, ballpath)) {
        std::cout << "load ball failed\n";
        success = false;
    }
    if(!gDirect.loadFromFile(gRenderer, directpath)) {
        std::cout << "load direct failed\n";
        success = false;
    }
    if(!gPowermeterBg.loadFromFile(gRenderer, powermeterbgpath)) {
        std::cout << "load PM_background failed\n";
        success = false;
    }
    for(int i = 0; i < 57; i++) {
        if(!gPowermeterFg[i].loadFromFile(gRenderer, powermeterfgpath)) {
            std::cout << "load PM_background failed\n";
            success = false;
        }
        gPowermeterFg[i].setWidth(i);
        gPowermeterFg[i].setHeight(8);
    }
    if(!gPowermeterOverlay.loadFromFile(gRenderer, powerMeterOverlayPath)) {
        std::cout << "load PM_overlay failed\n";
        success = false;
    }
    gChargeChunk = Mix_LoadWAV(chargeMusicPath.c_str());
    if(gChargeChunk == NULL) {
        std::cout << "load charge chunk failed!\n";
        success = false;
    }
    gCollisionChunk = Mix_LoadWAV(collisionMusicPath.c_str());
    if(gCollisionChunk == NULL) {
        std::cout << "load collision chunk failed!\n";
        success = false;
    }
    return success;
}
void Ball::renderBall(SDL_Renderer* gRenderer) {
    render(gRenderer);
    gPowermeterBg.render(gRenderer, 400, 600);
    gPowermeterOverlay.render(gRenderer, 400, 600);

    //std::cout<<gPowermeterFg.getHeight()<<'\n';// 8 56
    if(isCharging && isDown) {
        //std::cout<<gPowerFgClip->w<<'\n';
        int scale = velocBall.getScale();
        gPowermeterFg[int(scale * 1.4)].render(gRenderer, 404, 604);
        gDirect.render(gRenderer, getPosX(), getPosY() + 8 - 32, NULL, angleDirect);
    }
}
void Ball::freeBall() {
    free();
    gDirect.free();
    gPowermeterBg.free();
    for(int i = 0; i < 57; i++) {
        gPowermeterFg[i].free();
    }

    gPowermeterOverlay.free();
}

double Ball::getScaleVelocity() {
    return velocBall.getScale();
}
Vec2d Ball::getPosBeforeSwing() {
    return posBeforeSwing;
}
void Ball::turnAround() {
    if(countTurnAround == 0) {
        pos.x -= 5;
    }
    if(countTurnAround == 6) {
        pos.y -= 5;
    }
    if(countTurnAround == 12) {
        pos.x += 5;
    }
    if(countTurnAround == 18) {
        pos.y += 5;
    }
    countTurnAround++;
    countTurnAround %= 19;
}
SDL_FloatRect Ball::getFloatRect(){
    SDL_FloatRect ans = SDL_FloatRect(pos.x,pos.y,BALL_WIDTH,BALL_HEIGHT);
    return ans;
}

