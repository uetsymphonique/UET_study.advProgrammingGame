#include "params.hpp"
#include "Utils.hpp"
#include "LTexture.hpp"
#include "Ball.hpp"
#include "Hole.hpp"
#include "Block.hpp"
#include "PairTeleports.hpp"
#include "Vec2d.hpp"
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main(int argc,char* argv[]) {
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    LTexture gBackgroundTexture1;
    LTexture gBackgroundTexture2;
    LTexture gBackgroundTexture3;
    LTexture gBackgroundTexture4;
    LTexture gBackgroundTexture;

    LTexture gEnterTexture;
    TTF_Font *gFont = NULL;
    LTexture gTextEnterTexture;
    LTexture gLogoGame;

    Ball ball;

    Hole hole;

    vector<int>levels(12);

    Block block1,block1Long,block1LongR;
    Block block2,block2Long,block2LongR;
    Block block3,block3Long,block3LongR;
    Block block4,block4Long,block4LongR;
    vector <Block> blockList;
    SDL_Rect blockRectList[20];

    bool hasTeleport = false;
    bool hasSwamp = false;
    bool hasWind = false;
    bool hasIce = false;
    Teleport tele1;
    Teleport tele2;
    SDL_PairRect pairTeleRectList[1];


    if(!init(gWindow,gRenderer))std::cout<<"init failed\n";
    else {
        if(!loadMedia(gBackgroundTexture1,gBackgroundTexture2,gBackgroundTexture3,gBackgroundTexture4,
                      gTextEnterTexture,
                      gEnterTexture,
                      gLogoGame,
                      gMusic,
                      ball,
                      hole,
                      block1,block2,block3,block4,
                      block1Long,block2Long,block3Long,block4Long,
                      block1LongR,block2LongR,block3LongR,block4LongR,
                      tele1,tele2,
                      gFont,
                      gRenderer))
            std::cout<<"load media failed\n";
        else {
            bool quit = false;
            bool isEnter = false;
            bool isPlayMusic = false;
            bool isWin = true;
            int indexLevel;
            SDL_Event e;
            cout<<levels.size();
            iota(levels.begin(),levels.end(),0);
            while(!quit) {
                while(SDL_PollEvent(&e)!=0) {
                    if(e.type == SDL_QUIT) quit = true;
                    else if(e.type == SDL_KEYDOWN&&e.key.keysym.sym == SDLK_SPACE) isEnter = true;//nhan su kien la da vao game
                    else if(e.type == SDL_KEYDOWN&&e.key.keysym.sym == SDLK_m) {
                        Mix_HaltMusic();
                    }
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    if(x<5||x>SCREEN_WIDTH-5||y<5||y>SCREEN_HEIGHT-5)ball.setPosBall(ball.getPosX(),ball.getPosY());
                    else {
                        ball.handleMouseEvent(&e,gRenderer);
                    }

                }
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
                SDL_RenderClear(gRenderer);


                if(!isPlayMusic) {
                    Mix_PlayMusic( gMusic, -1 );
                    isPlayMusic = true;
                    std::cout<<"play music\n";
                }
                //isEnter true thì hiện màn chơi
                if(isEnter) {
                    if(isWin&&levels.size()>0) {
                        SDL_Delay(1000);
                        indexLevel = rng()%levels.size();
                        cout<<indexLevel<<" "<<levels[indexLevel]<<endl;

                        isWin = false;
                        switch(8) {
                        case 0:
                            {
                               hasTeleport = false;
                                hasSwamp = false;
                                hasWind = false;
                                hasIce = false;
                                //levels.erase(levels.begin()+indexLevel);
                                gBackgroundTexture=gBackgroundTexture1;
                                ball.setPosBall(200,600);
                                blockList.resize(4);
                                blockList[0] = block1;
                                blockList[1] = block1;
                                blockList[2] = block1;
                                blockList[3] = block1;
                                blockList[0].setPos(90,130);
                                blockList[1].setPos(90+32,130);
                                blockList[2].setPos(190,130);
                                blockList[3].setPos(190+32,130);
                                blockRectList[0] = {90,130,32,32};
                                blockRectList[1] = {90+32,130,32,32};
                                blockRectList[2] = {190,130,32,32};
                                blockRectList[3] = {190+32,130,32,32};
                                hole.setPos(200,100);
                            }
                            break;
                        case 1:
                            {
                                hasTeleport = false;
                                hasSwamp = false;
                                hasWind = false;
                                hasIce = false;
                                //levels.erase(levels.begin()+indexLevel);
                                gBackgroundTexture=gBackgroundTexture1;
                                ball.setPosBall(240,610);
                                blockList.resize(2);
                                blockList[0]=block1LongR;
                                blockList[0].setPos(100,150);
                                blockRectList[0] = {100,150,147,32};
                                blockList[1]=block1Long;
                                blockList[1].setPos(100+147-32,150-147);
                                blockRectList[1] = {100+147-32,150-147,32,147};
                                hole.setPos(150,110);
                            }
                            break;
                        case 2:
                            {
                                hasTeleport = false;
                                hasSwamp = false;
                                hasWind = false;
                                hasIce = false;
                                //levels.erase(levels.begin()+indexLevel);
                                gBackgroundTexture=gBackgroundTexture1;
                                ball.setPosBall(240,610);
                                blockList.resize(15);
                                fill(blockList.begin(),blockList.end(),block1);
                                for(int i = 0; i<5; i++) {
                                    blockList[i].setPos(100+32*i,180+32*pow(-1,i));
                                    blockRectList[i] = {100+32*i,180+32*pow(-1,i),32,32};
                                }
                                for(int i=5; i<9; i++) {
                                    blockList[i].setPos(100+32*(i-5),500);
                                    blockRectList[i] = {100+32*(i-5),500,32,32};
                                }
                                for(int i=9; i<12; i++) {
                                    blockList[i].setPos(100+32*4,110+32-32*(i-8));
                                    blockRectList[i] = {100+32*4,110+32-32*(i-8),32,32};
                                }
                                for(int i=12; i<15; i++) {
                                    blockList[i].setPos(240+32*(i-12),400);
                                    blockRectList[i] = {240+32*(i-12),400,32,32};
                                }
                                hole.setPos(150,110);
                            }
                            break;
                        case 3:
                            hasTeleport = false;
                            hasSwamp = true;
                            hasWind = false;
                            hasIce = false;
                            gBackgroundTexture=gBackgroundTexture2;
                            ball.setPosBall(240,610);
                            blockList.resize(15);
                            fill(blockList.begin(),blockList.end(),block1);
                            for(int i = 0; i<5; i++) {
                                blockList[i].setPos(100+32*i,180+32*pow(-1,i));
                                blockRectList[i] = {100+32*i,180+32*pow(-1,i),32,32};
                            }
                            for(int i=5; i<9; i++) {
                                blockList[i].setPos(100+32*(i-5),500);
                                blockRectList[i] = {100+32*(i-5),500,32,32};
                            }
                            for(int i=9; i<12; i++) {
                                blockList[i].setPos(100+32*4,110+32-32*(i-8));
                                blockRectList[i] = {100+32*4,110+32-32*(i-8),32,32};
                            }
                            for(int i=12; i<15; i++) {
                                blockList[i].setPos(240+32*(i-12),400);
                                blockRectList[i] = {240+32*(i-12),400,32,32};
                            }
                            hole.setPos(150,110);
                            break;
                        case 4:
                            //levels.erase(levels.begin()+indexLevel);
                            gBackgroundTexture=gBackgroundTexture2;
                            hole.setPos(200,200);
                            break;
                        case 5:
                            //levels.erase(levels.begin()+indexLevel);
                            for(int i=0; i<blockList.size(); i++) {
                                blockList[i].setPos(100*i+100,400);
                                blockRectList[i] = {100*i+100,400,32,32};
                            }
                            gBackgroundTexture=gBackgroundTexture2;
                            hole.setPos(200,200);
                            break;
                        case 6:
                            {
                                hasTeleport = true;
                                hasSwamp = false;
                                hasWind = false;
                                hasIce = false;
                                //levels.erase(levels.begin()+indexLevel);
                                tele1.setPos(350,610);
                                tele2.setPos(50,250);
                                pairTeleRectList[0].rect1 = tele1.getRect();
                                pairTeleRectList[0].rect2 = tele2.getRect();
                                gBackgroundTexture=gBackgroundTexture3;
                                ball.setPosBall(240,610);
                                blockList.resize(4);
                                fill(blockList.begin(),blockList.end(),block3LongR);
                                blockList[0].setPos(0,300);
                                blockRectList[0] = {0,300,147,32};
                                blockList[1].setPos(SCREEN_WIDTH-147,400);
                                blockRectList[1] = {SCREEN_WIDTH-147,400,147,32};
                                blockList[2].setPos(150,250);
                                blockRectList[2] = {150,250,147,32};
                                blockList[3].setPos(200,350);
                                blockRectList[3] = {200,350,147,32};
                                hole.setPos(150,110);
                            }
                            break;
                        case 7:
                            {
                                hasTeleport = true;
                                hasSwamp = false;
                                hasWind = false;
                                hasIce = false;
                                //levels.erase(levels.begin()+indexLevel);
                                tele1.setPos(150,50);
                                tele2.setPos(150,200);
                                pairTeleRectList[0].rect1 = tele1.getRect();
                                pairTeleRectList[0].rect2 = tele2.getRect();
                                gBackgroundTexture=gBackgroundTexture3;
                                ball.setPosBall(330,610);
                                blockList.resize(10);
                                fill(blockList.begin(),blockList.end(),block3);
                                blockList[0].setPos(50,110);
                                blockRectList[0] = {50,110,32,32};
                                blockList[1].setPos(100,50);
                                blockRectList[1] = {100,50,32,32};
                                blockList[2].setPos(200,50);
                                blockRectList[2] = {200,50,32,32};
                                blockList[3].setPos(50,180);
                                blockRectList[3] = {50,180,32,32};
                                blockList[4].setPos(150,110);
                                blockRectList[4] = {150,110,32,32};
                                blockList[5] = block3LongR; blockList[5].setPos(230,180);
                                blockRectList[5] = {230,180,147,32};
                                blockList[6] = block3Long; blockList[6].setPos(50,250);
                                blockRectList[6] = {50,250,32,147};
                                blockList[7] = block3Long; blockList[7].setPos(230,250);
                                blockRectList[7] = {230,250,32,147};
                                blockList[8] = block3LongR; blockList[8].setPos(80,450);
                                blockRectList[8] = {80,450,147,32};
                                blockList[9] = block3LongR; blockList[9].setPos(300,500);
                                blockRectList[9] = {300,500,147,32};
                                hole.setPos(50,50);
                            }
                            break;
                        case 8:
                            {
                                hasTeleport = true;
                                hasSwamp = false;
                                hasWind = false;
                                hasIce = false;
                                //levels.erase(levels.begin()+indexLevel);
                                tele1.setPos(82,130);
                                tele2.setPos(100,580);
                                pairTeleRectList[0].rect1 = tele1.getRect();
                                pairTeleRectList[0].rect2 = tele2.getRect();
                                gBackgroundTexture=gBackgroundTexture3;
                                ball.setPosBall(330,610);
                                blockList.resize(18);
                                fill(blockList.begin(),blockList.end(),block3);
                                blockList[0].setPos(0,0);
                                blockRectList[0] = {0,0,32,32};
                                blockList[1].setPos(SCREEN_WIDTH-32,0);
                                blockRectList[1] = {SCREEN_WIDTH-32,0,32,32};
                                blockList[2] = block3LongR ;blockList[2].setPos(168,0);
                                blockRectList[2] = {168,0,147,32};
                                blockList[3].setPos(82,0);
                                blockRectList[3] = {82,0,32,32};
                                blockList[4].setPos(SCREEN_WIDTH-114,0);
                                blockRectList[4] = {SCREEN_WIDTH-114,0,32,32};
                                blockList[5] = block3Long; blockList[5].setPos(0,64);
                                blockRectList[5] = {0,64,32,147};
                                blockList[6] = block3Long; blockList[6].setPos(SCREEN_WIDTH-32,64);
                                blockRectList[6] = {SCREEN_WIDTH-32,64,32,147};
                                blockList[7].setPos(82,64);
                                blockRectList[7] = {82,64,32,32};
                                blockList[8].setPos(82,179);
                                blockRectList[8] = {82,179,32,32};
                                blockList[9].setPos(SCREEN_WIDTH-114,64);
                                blockRectList[9] = {SCREEN_WIDTH-114,64,32,32};
                                blockList[10].setPos(SCREEN_WIDTH-114,179);
                                blockRectList[10] = {SCREEN_WIDTH-114,179,32,32};
                                blockList[11] = block3LongR; blockList[11].setPos(0,243);
                                blockRectList[11] = {0,243,147,32};
                                blockList[12] = block3LongR; blockList[12].setPos(SCREEN_WIDTH-147,243);
                                blockRectList[12] = {SCREEN_WIDTH-147,243,147,32};
                                blockList[13] = block3LongR ;blockList[13].setPos(168,179);
                                blockRectList[13] = {168,179,147,32};
                                blockList[14] = block3LongR; blockList[14].setPos(0,383);
                                blockRectList[14] = {0,383,147,32};
                                blockList[15] = block3LongR; blockList[15].setPos(SCREEN_WIDTH-147,383);
                                blockRectList[15] = {SCREEN_WIDTH-147,383,147,32};
                                blockList[16] = block3LongR ;blockList[16].setPos(168,339);
                                blockRectList[16] = {168,339,147,32};
                                blockList[17] = block3Long ;blockList[17].setPos(250,SCREEN_HEIGHT-150);
                                blockRectList[17] = {250,SCREEN_HEIGHT-150,32,147};
                                hole.setPos(280,100);
                            }
                            break;
                        case 9:
                            //levels.erase(levels.begin()+indexLevel);
                            for(int i=0; i<blockList.size(); i++) {
                                blockList[i].setPos(100*i+100,400);
                                blockRectList[i] = {100*i+100,400,32,32};
                            }
                            gBackgroundTexture=gBackgroundTexture4;
                            hole.setPos(200,200);
                            break;
                        case 10:
                            //levels.erase(levels.begin()+indexLevel);
                            for(int i=0; i<blockList.size(); i++) {
                                blockList[i].setPos(100*i+100,400);
                                blockRectList[i] = {100*i+100,400,32,32};
                            }
                            gBackgroundTexture=gBackgroundTexture4;
                            break;
                        case 11:
                            //levels.erase(levels.begin()+indexLevel);
                            for(int i=0; i<blockList.size(); i++) {
                                blockList[i].setPos(100*i+100,400);
                                blockRectList[i] = {100*i+100,400,32,32};
                            }
                            gBackgroundTexture=gBackgroundTexture4;
                            hole.setPos(200,200);
                            break;
                        }
                    }

                    gBackgroundTexture.render(gRenderer,0,0);
                    ball.renderBall(gRenderer);

                    hole.render(gRenderer);
                    ball.moveBall(blockRectList,blockList.size(),pairTeleRectList,1,hasSwamp,hasTeleport);
                    for(int i=0; i<blockList.size(); i++) {
                        blockList[i].render(gRenderer);
                    }

                    if(ball.getScaleVelocity()>ball.MIN_VEL_OUT_HOLE||!checkCollision(ball.getRect(),hole.getRect())) {
                        if(hasTeleport){
                            tele1.render(gRenderer);
                            tele2.render(gRenderer);
                        }
                        ball.renderBall(gRenderer);
                    } else {
                        isWin = true;
                        ball.setPosBall(hole.getPosX(),hole.getPosY());
                        ball.renderBall(gRenderer);
                    }

                } else {
                    gBackgroundTexture1.render(gRenderer,0,0);
                    gEnterTexture.render(gRenderer,(SCREEN_WIDTH-gEnterTexture.getWidth())/2,(SCREEN_HEIGHT-gEnterTexture.getHeight())/2);
                    gTextEnterTexture.render(gRenderer,(SCREEN_WIDTH-gTextEnterTexture.getWidth())/2,(SCREEN_HEIGHT-gTextEnterTexture.getHeight())/2+120);
                    gLogoGame.render(gRenderer,(SCREEN_WIDTH-gLogoGame.getWidth())/2,(SCREEN_HEIGHT-gLogoGame.getHeight())/2-100);
                }
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    TTF_CloseFont( gFont );
    gFont = NULL;
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    close(gWindow,gRenderer);

    return 0;
}
