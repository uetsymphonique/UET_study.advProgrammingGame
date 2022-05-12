#include "Ball.hpp"

void Ball::setPosBall(double x, double y) {
    setPos(x, y);
    velocBall = Vec2d(0.0, 0.0);
    isCharging = false;
    isDown = false;
}
void Ball::handleMouseEvent(SDL_Event *e, SDL_Renderer* gRenderer, int &swings) {
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
void Ball::moveBall(SDL_Rect blockRectList[], int numOfBlocks,
                    SDL_PairRect pairTeleRectList[], int numOfPairsTele,
                    vector<SDL_Rect> swampRectList, bool& isSwamped,
                    bool hasSwamp, bool hasTeleport, bool hasWind, bool hasIce) {
    if(!isCharging && (abs(velocBall.y) >= 0.2 || abs(velocBall.x) >= 0.2)) {
        //std::cout<<pos.x<<" "<<pos.y<<'\n';
        Vec2d v = velocBall;
        bool collisionX = false;
        bool collisionY = false;
        SDL_Rect ballRect = getRect();
        int leftBall, rightBall, topBall, bottomBall;
        leftBall = ballRect.x;
        rightBall = leftBall + ballRect.w;
        topBall = ballRect.y;
        bottomBall = topBall + ballRect.h;
        double ratioVeloc = velocBall.getRatio();
        //check collision with blocks and walls

        //collision made by only change of x
        if(abs(velocBall.x) >= 0.4) {
            ballRect.x += velocBall.x;
            if(ballRect.x + BALL_WIDTH >= SCREEN_WIDTH) {
                velocBall = Vec2d(SCREEN_WIDTH - rightBall, (SCREEN_WIDTH - rightBall) / ratioVeloc);
                collisionX = true;
            } else if(ballRect.x <= 0) {
                velocBall = Vec2d(0 - leftBall, (0 - leftBall) / ratioVeloc);
                collisionX = true;
            } else {
                for(int i = 0; i < numOfBlocks; i++) {
                    if(checkCollision(ballRect, blockRectList[i])) {
                        collisionX = true;
                        if(velocBall.x > 0) {
                            velocBall = Vec2d(blockRectList[i].x - pos.x - BALL_WIDTH - 2,
                                              (blockRectList[i].x - pos.x - BALL_WIDTH - 2) / ratioVeloc);
                            std::cout << "velocity: " << velocBall.x << " " << velocBall.y << '\n';
                        } else if(velocBall.x < 0) {
                            velocBall = Vec2d(blockRectList[i].x + blockRectList[i].w - pos.x + 2, (blockRectList[i].x + blockRectList[i].w - pos.x + 2) / ratioVeloc);
                            std::cout << "velocity: " << velocBall.x << " " << velocBall.y << '\n';
                        }
                        break;
                    }
                }
            }
        }

        //collision made by only change of y
        ballRect.x = leftBall;
        if(abs(velocBall.y) >= 0.4) {
            ballRect.y += velocBall.y;
            if(ballRect.y + BALL_HEIGHT >= SCREEN_HEIGHT) {
                velocBall = Vec2d((SCREEN_HEIGHT - (pos.y + BALL_HEIGHT)) * ratioVeloc, SCREEN_HEIGHT - (pos.y + BALL_HEIGHT));
                collisionY = true;
            } else if(ballRect.y <= 0) {
                velocBall = Vec2d((0 - pos.y) * ratioVeloc, 0 - pos.y);
                collisionY = true;
            } else {
                for(int i = 0; i < numOfBlocks; i++) {
                    if(checkCollision(ballRect, blockRectList[i])) {
                        if(velocBall.y > 0) {
                            velocBall = Vec2d((blockRectList[i].y - (pos.y + BALL_HEIGHT) - 2) * ratioVeloc, blockRectList[i].y - (pos.y + BALL_HEIGHT) - 2);
                        } else {
                            velocBall = Vec2d((blockRectList[i].y + blockRectList[i].h - pos.y + 2) * ratioVeloc,
                                              blockRectList[i].y + blockRectList[i].h - pos.y + 2);
                        }
                        collisionY = true;
                        break;
                    }
                }
            }
        }

        //collision made by x and y change
        ballRect.x += velocBall.x;
        if(!collisionX && !collisionY ) {
            for(int i = 0; i < numOfBlocks; i++) {
                if(checkCollision(ballRect, blockRectList[i])) {
                    Vec2d v1;
                    if(velocBall.y > 0) {
                        v1 = Vec2d((blockRectList[i].y - (pos.y + BALL_HEIGHT) - 2) * ratioVeloc,
                                   blockRectList[i].y - (pos.y + BALL_HEIGHT) - 2);
                    } else {
                        v1 = Vec2d((blockRectList[i].y + blockRectList[i].h - pos.y + 2) * ratioVeloc,
                                   blockRectList[i].y + blockRectList[i].h - pos.y + 2);
                    }
                    SDL_Rect tempBallRect = getRect();
                    tempBallRect.x += velocBall.x;
                    tempBallRect.y += velocBall.y;
                    if(checkCollision(tempBallRect, blockRectList[i])) {
                        collisionY = true;
                    }
                    Vec2d v2;
                    if(velocBall.x > 0) {
                        v2 = Vec2d(blockRectList[i].x - (pos.x + BALL_WIDTH) - 2,
                                   (blockRectList[i].x - (pos.x + BALL_WIDTH) - 2) / ratioVeloc);
                    } else {
                        v2 = Vec2d(blockRectList[i].x + blockRectList[i].w - pos.x + 2,
                                   (blockRectList[i].x + blockRectList[i].w - pos.x + 2) / ratioVeloc);
                    }
                    tempBallRect = getRect();
                    tempBallRect.x += velocBall.x;
                    tempBallRect.y += velocBall.y;
                    if(checkCollision(tempBallRect, blockRectList[i])) {
                        collisionX = true;
                    }
                    if(collisionX)velocBall = v1;
                    if(collisionY)velocBall = v2;
                    break;
                }
            }
        }

        pos.x += velocBall.x;
        pos.y += velocBall.y;
        velocBall = v;
        if(collisionX)velocBall.x = 0 - velocBall.x / DECREASE_VEL;
        if(collisionY)velocBall.y = 0 - velocBall.y / DECREASE_VEL;


        //collision with teleports
        if(int(velocBall.getScale()) > 0 && hasTeleport) {
            for(int i = 0; i < numOfPairsTele; i++) {
                if(checkCollision(getRect(), pairTeleRectList[i].rect1)) {
                    setPosX(pairTeleRectList[i].rect2.x);
                    setPosY(pairTeleRectList[i].rect2.y);
                    SDL_Rect tempRect = getRect();
                    tempRect.x += velocBall.x / DECREASE_VEL;
                    tempRect.y += velocBall.y / DECREASE_VEL;
                    if(checkCollision(tempRect, pairTeleRectList[i].rect2)) {
                        pos.x += velocBall.x / abs(velocBall.x) * 20;
                        pos.y += velocBall.y / abs(velocBall.y) * 20;
                        //velocBall.x=0;velocBall.y=0;
                    }
                    break;
                } else if(checkCollision(getRect(), pairTeleRectList[i].rect2)) {
                    setPosX(pairTeleRectList[i].rect1.x);
                    setPosY(pairTeleRectList[i].rect1.y);
                    SDL_Rect tempRect = getRect();
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

    }

}
bool Ball::loadTextureFromFile(SDL_Renderer* gRenderer, std::string ballpath, std::string directpath,
                               std::string powermeterbgpath, std::string powermeterfgpath, std::string powerMeterOverlayPath,
                               std::string chargeMusicPath) {
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
