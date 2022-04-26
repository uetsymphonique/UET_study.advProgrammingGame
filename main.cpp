#include "params.hpp"
#include "Utils.hpp"
#include "LTexture.hpp"
#include "Ball.hpp"
#include "Hole.hpp"
#include "Block.hpp"
#include "PairTeleports.hpp"
#include "Vec2d.hpp"

int main(int argc,char* argv[]) {
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    LTexture gBackgroundTexture;

    LTexture gEnterTexture;
    TTF_Font *gFont = NULL;
    LTexture gTextEnterTexture;
    LTexture gLogoGame;

    Ball ball;

    Hole hole;

    vector<int>levels(12);

    vector <Block> blockList(2);
    SDL_Rect blockRectList[2];

    Teleport tele1;
    Teleport tele2;
    SDL_PairRect pairTeleRectList[1];


    if(!init(gWindow,gRenderer))std::cout<<"init failed\n";
    else {
        if(!loadMedia(gBackgroundTexture,
                      gTextEnterTexture,
                      gEnterTexture,
                      gLogoGame,
                      gMusic,
                      ball,
                      hole,
                      blockList,
                      tele1,tele2,
                      gFont,
                      gRenderer))
            std::cout<<"load media failed\n";
        else {
            bool quit = false;
            bool isEnter = false;
            bool isPlayMusic = false;
            ball.setPosBall(100,100);
            for(int i=0; i<blockList.size(); i++) {
                blockList[i].setPos(100*i+100,400);
                blockRectList[i] = {100*i+100,400,32,32};
            }
            tele1.setPos(150,250);
            tele2.setPos(400,500);
            pairTeleRectList[0].rect1 = tele1.getRect();
            pairTeleRectList[0].rect2 = tele2.getRect();
            SDL_Event e;
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
                gBackgroundTexture.render(gRenderer,0,0);

                if(!isPlayMusic) {
                    Mix_PlayMusic( gMusic, -1 );
                    isPlayMusic = true;
                    std::cout<<"play music\n";
                }
                //isEnter true thì hiện màn chơi
                if(isEnter) {
                    ball.renderBall(gRenderer);
                    hole.setPos(200,200);
                    hole.render(gRenderer);
                    ball.moveBall(blockRectList,2,pairTeleRectList,1);
                    for(int i=0; i<blockList.size(); i++) {
                        blockList[i].render(gRenderer);
                        }

                    if(ball.getScaleVelocity()>ball.MIN_VEL_OUT_HOLE||!checkCollision(ball.getRect(),hole.getRect())) {
                        tele1.render(gRenderer);
                        tele2.render(gRenderer);
                        ball.renderBall(gRenderer);

                    } else {
                        ball.setPosBall(hole.getPosX(),hole.getPosY());
                    }

                } else {
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
