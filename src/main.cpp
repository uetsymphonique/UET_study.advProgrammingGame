#include "params.hpp"
#include "Utils.hpp"
#include "LTexture.hpp"
#include "Ball.hpp"
#include "Hole.hpp"
#include "Block.hpp"
#include "PairTeleports.hpp"
#include "Vec2d.hpp"
#include "InfoBlock.hpp"
#include "Timer.hpp"
#include "Swamp.hpp"
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int main(int argc, char* argv[]) {
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

    LTexture gIntroTextTexture;

    Ball ball;

    Hole hole;
    SDL_Rect holeRect;

    Timer gameTimer;
    vector<int>levels(NUM_OF_LEVELS);

    Block block1, block1Long, block1LongR;
    Block block2, block2Long, block2LongR;
    Block block3, block3Long, block3LongR;
    Block block4, block4Long, block4LongR;
    vector <InfoBlock> blockList;
    SDL_Rect blockRectList[20];

    bool hasTeleport = false;
    Teleport tele1;
    Teleport tele2;
    SDL_PairRect pairTeleRectList[1];


    bool hasSwamp = false;
    Swamp swamp;
    SDL_Rect swampRectList[1];
    bool isSwamped = false;
    Timer swampedBallTimer;

    bool hasWind = false;

    bool hasIce = false;

    LTexture gSwingsTextTexture;

    LTexture gWinEachLevelTextTexture;
    LTexture gResultEachLevelTextTexture;


    if(!init(gWindow, gRenderer))std::cout << "init failed\n";
    else {
        if(!loadMedia(gBackgroundTexture1, gBackgroundTexture2, gBackgroundTexture3, gBackgroundTexture4,
                      gTextEnterTexture,
                      gEnterTexture,
                      gLogoGame,
                      gMusic,
                      gIntroTextTexture,
                      ball,
                      hole,
                      block1, block2, block3, block4,
                      block1Long, block2Long, block3Long, block4Long,
                      block1LongR, block2LongR, block3LongR, block4LongR,
                      swamp,
                      tele1, tele2,
                      gFont,
                      gRenderer))
            std::cout << "load media failed\n";
        else {

            bool quit = false;
            bool isEnter = false;
            bool isPlayMusic = false;
            bool isWin = true;
            int swings = 0;
            int indexLevel;
            vector<Block>blocks(12);
            blocks[0] = block1;
            blocks[1] = block2;
            blocks[2] = block3;
            blocks[3] = block4;
            blocks[4] = block1Long;
            blocks[5] = block2Long;
            blocks[6] = block3Long;
            blocks[7] = block4Long;
            blocks[8] = block1LongR;
            blocks[9] = block2LongR;
            blocks[10] = block3LongR;
            blocks[11] = block4LongR;
            SDL_Event e;
            cout << levels.size();
            iota(levels.begin(), levels.end(), 0);
            while(!quit) {
                while(SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) quit = true;
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) isEnter = true; //nhan su kien la da vao game
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_m) {
                        Mix_HaltMusic();
                    }
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(x < 5 || x > SCREEN_WIDTH - 5 || y < 5 || y > SCREEN_HEIGHT - 5)ball.setPosBall(ball.getPosX(), ball.getPosY());
                    else {
                        ball.handleMouseEvent(&e, gRenderer, swings);
                    }
                }

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                ball.setBlendMode(SDL_BLENDMODE_BLEND);
                if(!isPlayMusic) {
                    Mix_PlayMusic( gMusic, -1 );
                    isPlayMusic = true;
                    std::cout << "play music\n";
                }
                //isEnter true thì hiện màn chơi
                if(isEnter) {
                    if(isWin && levels.size() > 0 && gameTimer.distanceTime()>= TIME_BETWEEN_2LEVELS) {
                        indexLevel = 0;
                        cout << indexLevel << " " << levels[indexLevel] << endl;
                        swings = 0;
                        isWin = false;
//                        for(int i=0;i<blockList.size();i++){
//                            blockList[i].free();
//                        }
                        //switch(levels[indexLevel]) {
                        switch(2) {
                        case 0: { //normal
                            hasTeleport = false;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture1;
                            ball.setPosBall(200, 600);
                            blockList.resize(4);
                            cout << blockList.size() << '\n';
                            blockList[0] = InfoBlock(90, 130, 0);
                            blockList[1] = InfoBlock(90 + 32, 130, 0);
                            blockList[2] = InfoBlock(190, 130, 0);
                            blockList[3] = InfoBlock(190 + 32, 130, 0);
                            blockRectList[0] = {90, 130, 32, 32};
                            blockRectList[1] = {90 + 32, 130, 32, 32};
                            blockRectList[2] = {190, 130, 32, 32};
                            blockRectList[3] = {190 + 32, 130, 32, 32};
                            hole.setPos(200, 100);
                        }
                        break;
                        case 1: { //normal
                            hasTeleport = false;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            //levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture1;
                            ball.setPosBall(240, 610);
                            blockList.resize(2);
                            cout << blockList.size() << '\n';
                            blockList[0] = InfoBlock(100, 150, 8);
                            blockRectList[0] = {100, 150, 147, 32};
                            blockList[1] = InfoBlock(100 + 147 - 32, 150 - 147, 8);
                            blockRectList[1] = {100 + 147 - 32, 150 - 147, 32, 147};
                            hole.setPos(150, 110);
                        }
                        break;
                        case 2: { //sandy
                            hasTeleport = false;
                            hasSwamp = true;
                            hasWind = false;
                            hasIce = false;
                            //levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture2;
                            ball.setPosBall(240, 610);
                            blockList.resize(3);
                            cout << blockList.size() << '\n';
                            blockList[0] = InfoBlock(50, 150, 5);
                            blockRectList[0] = {50, 150, 32, 147};
                            blockList[1] = InfoBlock(400, 200, 5);
                            blockRectList[1] = {400, 200, 32, 147};
                            blockList[2] = InfoBlock(200, 610, 1);
                            blockRectList[2] = {200, 610, 32, 32};
                            swamp.setPos(150, 150);
                            swampRectList[0] = {150, 150, 64, 64};
                            hole.setPos(150, 110);
                        }
                        break;
                        case 3: { //sandy
                            hasTeleport = false;
                            hasSwamp = true;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture1;
                            ball.setPosBall(240, 610);
                            blockList.resize(3);
                            cout << blockList.size() << '\n';
                            blockList[0] = InfoBlock(100, 150, 4);
                            blockRectList[0] = {100, 150, 147, 32};
                            blockList[1] = InfoBlock(100 + 147 - 32, 150 - 147, 4);
                            blockRectList[1] = {100 + 147 - 32, 150 - 147, 32, 147};
                            hole.setPos(150, 110);

                        }
                        break;
                        case 4: { //tropical
                            hasTeleport = true;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            tele1.setPos(350, 610);
                            tele2.setPos(50, 250);
                            pairTeleRectList[0].rect1 = tele1.getRect();
                            pairTeleRectList[0].rect2 = tele2.getRect();
                            gBackgroundTexture = gBackgroundTexture3;
                            ball.setPosBall(240, 610);
                            blockList.resize(4);
                            cout << blockList.size() << '\n';
                            blockList[0] = InfoBlock(0, 300, 10);
                            blockRectList[0] = {0, 300, 147, 32};
                            blockList[1] = InfoBlock(SCREEN_WIDTH - 147, 400, 10);
                            blockRectList[1] = {SCREEN_WIDTH - 147, 400, 147, 32};
                            blockList[2] = InfoBlock(150, 250, 10);
                            blockRectList[2] = {150, 250, 147, 32};
                            blockList[3] = InfoBlock(200, 350, 10);
                            blockRectList[3] = {200, 350, 147, 32};
                            hole.setPos(150, 110);
                        }
                        break;
                        case 5: { //tropical
                            hasTeleport = true;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            tele1.setPos(150, 50);
                            tele2.setPos(150, 200);
                            pairTeleRectList[0].rect1 = tele1.getRect();
                            pairTeleRectList[0].rect2 = tele2.getRect();
                            gBackgroundTexture = gBackgroundTexture3;
                            ball.setPosBall(330, 610);
                            blockList.resize(10);
                            cout << blockList.size() << '\n';
                            blockList[0] = InfoBlock(50, 110, 2);
                            blockRectList[0] = {50, 110, 32, 32};
                            blockList[1] = InfoBlock(100, 50, 2);
                            blockRectList[1] = {100, 50, 32, 32};
                            blockList[2] = InfoBlock(200, 50, 2);
                            blockRectList[2] = {200, 50, 32, 32};
                            blockList[3] = InfoBlock(50, 180, 2);
                            blockRectList[3] = {50, 180, 32, 32};
                            blockList[4] = InfoBlock(150, 110, 2);
                            blockRectList[4] = {150, 110, 32, 32};
                            blockList[5] = InfoBlock(230, 180, 10);
                            blockRectList[5] = {230, 180, 147, 32};
                            blockList[6] = InfoBlock(50, 250, 6);
                            blockRectList[6] = {50, 250, 32, 147};
                            blockList[7] = InfoBlock(230, 250, 6);
                            blockRectList[7] = {230, 250, 32, 147};
                            blockList[8] = InfoBlock(80, 450, 10);
                            blockRectList[8] = {80, 450, 147, 32};
                            blockList[9] = InfoBlock(300, 500, 10);
                            blockRectList[9] = {300, 500, 147, 32};
                            hole.setPos(50, 50);
                        }
                        break;
                        case 6: { //ice age
                            hasTeleport = true;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            tele1.setPos(82, 130);
                            tele2.setPos(100, 580);
                            pairTeleRectList[0].rect1 = tele1.getRect();
                            pairTeleRectList[0].rect2 = tele2.getRect();
                            gBackgroundTexture = gBackgroundTexture4;
                            ball.setPosBall(330, 610);
                            blockList.resize(18);
                            cout << blockList.size() << '\n';
                            blockList[0] = InfoBlock(0, 0, 2);
                            blockRectList[0] = {0, 0, 32, 32};
                            blockList[1] = InfoBlock(SCREEN_WIDTH - 32, 0, 2);
                            blockRectList[1] = {SCREEN_WIDTH - 32, 0, 32, 32};
                            blockList[2] = InfoBlock(168, 0, 10);
                            blockRectList[2] = {168, 0, 147, 32};
                            blockList[3] = InfoBlock(82, 0, 2);
                            blockRectList[3] = {82, 0, 32, 32};
                            blockList[4] = InfoBlock(SCREEN_WIDTH - 114, 0, 2);
                            blockRectList[4] = {SCREEN_WIDTH - 114, 0, 32, 32};
                            blockList[5] = InfoBlock(0, 64, 6);
                            blockRectList[5] = {0, 64, 32, 147};
                            blockList[6] = InfoBlock(SCREEN_WIDTH - 32, 64, 6);
                            blockRectList[6] = {SCREEN_WIDTH - 32, 64, 32, 147};
                            blockList[7] = InfoBlock(82, 64, 2);
                            blockRectList[7] = {82, 64, 32, 32};
                            blockList[8] = InfoBlock(82, 179, 2);
                            blockRectList[8] = {82, 179, 32, 32};
                            blockList[9] = InfoBlock(SCREEN_WIDTH - 114, 64, 2);
                            blockRectList[9] = {SCREEN_WIDTH - 114, 64, 32, 32};
                            blockList[10] = InfoBlock(SCREEN_WIDTH - 114, 179, 2);
                            blockRectList[10] = {SCREEN_WIDTH - 114, 179, 32, 32};
                            blockList[11] = InfoBlock(0, 243, 10);
                            blockRectList[11] = {0, 243, 147, 32};
                            blockList[12] = InfoBlock(SCREEN_WIDTH - 147, 243, 10);
                            blockRectList[12] = {SCREEN_WIDTH - 147, 243, 147, 32};
                            blockList[13] = InfoBlock(168, 179, 10);
                            blockRectList[13] = {168, 179, 147, 32};
                            blockList[14] = InfoBlock(0, 383, 10);
                            blockRectList[14] = {0, 383, 147, 32};
                            blockList[15] = InfoBlock(SCREEN_WIDTH - 147, 383, 10);
                            blockRectList[15] = {SCREEN_WIDTH - 147, 383, 147, 32};
                            blockList[16] = InfoBlock(168, 339, 10);
                            blockRectList[16] = {168, 339, 147, 32};
                            blockList[17] = InfoBlock(250, SCREEN_HEIGHT - 150, 6);
                            blockRectList[17] = {250, SCREEN_HEIGHT - 150, 32, 147};
                            hole.setPos(280, 100);
                        }
                        break;
                        }
                    } else if(!isWin) {
                        SDL_Color textColor = {0, 0, 0};
                        string s = "SWINGS: " + to_string(swings);
                        if(!gSwingsTextTexture.loadFromRenderedText(gRenderer, gFont, s, textColor)) {
                            std::cout << "failed to render swing text texture!\n";
                        }
                        gameTimer.updateTime();
                        gBackgroundTexture.render(gRenderer, 0, 0);
                        gSwingsTextTexture.render(gRenderer);
                        ball.setAlpha(255);
                        ball.renderBall(gRenderer);
                        hole.render(gRenderer);
                        ball.moveBall(blockRectList, blockList.size(), pairTeleRectList, 1,
                                      swampRectList, 1, isSwamped,
                                      hasSwamp, hasTeleport, hasWind, hasIce);
                        for(int i = 0; i < blockList.size(); i++) {
                            blocks[blockList[i].typeBlock].render(gRenderer, blockList[i].pos.x, blockList[i].pos.y);
                        }
                        if(hasTeleport) {
                            tele1.render(gRenderer);
                            tele2.render(gRenderer);
                        }
                        if(hasSwamp) {
                            swamp.render(gRenderer);
                            swamp.rotateSwamp();
                        }
                        holeRect = hole.getRect();
                        holeRect.h = 16;
                        if(ball.getScaleVelocity() > ball.MIN_VEL_OUT_HOLE || !checkCollisionCircleWithRect(ball.getRect(), holeRect)) {
                            ball.renderBall(gRenderer);
                        } else {
                            isWin = true;
                            ball.setPosBall(hole.getPosX(), hole.getPosY());
                            ball.renderBall(gRenderer);
                        }
                    } else if(levels.size() == NUM_OF_LEVELS) {
                        gBackgroundTexture1.render(gRenderer, 0, 0);
                        gIntroTextTexture.setBlendMode(SDL_BLENDMODE_BLEND);
                        gIntroTextTexture.setAlpha(gameTimer.distanceTime() * 255 / TIME_BETWEEN_2LEVELS);
                        gIntroTextTexture.render(gRenderer, (SCREEN_WIDTH - gIntroTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gIntroTextTexture.getHeight()) / 2);
                    } else if(levels.size() > 0) {
                        gBackgroundTexture.render(gRenderer);
                        string s1 = "Mission " + to_string(NUM_OF_LEVELS - levels.size()) + " completed!";
                        string s2;
                        if(swings > 1) s2 = "You completed in " + to_string(swings) + " swings!";
                        else s2 = "You completed with hole-in-one!";
                        SDL_Color textColor = {0, 0, 0};
                        if(!gWinEachLevelTextTexture.loadFromRenderedText(gRenderer, gFont, s1, textColor)) {
                            std::cout << "failed to render win text texture!\n";
                        }
                        if(!gResultEachLevelTextTexture.loadFromRenderedText(gRenderer, gFont, s2, textColor)) {
                            std::cout << "failed to render result text texture!\n";
                        }
                        gWinEachLevelTextTexture.render(gRenderer, (SCREEN_WIDTH - gWinEachLevelTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gWinEachLevelTextTexture.getHeight()) / 2 - 50);
                        gResultEachLevelTextTexture.render(gRenderer, (SCREEN_WIDTH - gResultEachLevelTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gResultEachLevelTextTexture.getHeight()) / 2 + 50);
                    } else if(levels.size() == 0) {
                        gBackgroundTexture1.render(gRenderer, 0, 0);
                        string s1 = "Congratulations, all missions completed!";
                        SDL_Color textColor = {0, 0, 0};
                        if(!gWinEachLevelTextTexture.loadFromRenderedText(gRenderer, gFont, s1, textColor)) {
                            std::cout << "failed to render win text texture!\n";
                        }
                        gWinEachLevelTextTexture.render(gRenderer, (SCREEN_WIDTH - gWinEachLevelTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gWinEachLevelTextTexture.getHeight()) / 2);
                        if(gameTimer.distanceTime()== TIME_BETWEEN_2LEVELS) quit = true;
                    } else if(gameTimer.distanceTime() < 3000) {
                        SDL_Color textColor = {0, 0, 0};
                        string s = "SWINGS: " + to_string(swings);
                        if(!gSwingsTextTexture.loadFromRenderedText(gRenderer, gFont, s, textColor)) {
                            std::cout << "failed to render swing text texture!\n";
                        }
                        gBackgroundTexture.render(gRenderer, 0, 0);
                        gSwingsTextTexture.render(gRenderer);
                        ball.setBlendMode(SDL_BLENDMODE_BLEND);
                        ball.setAlpha(255 - gameTimer.distanceTime() * 255 / TIME_BETWEEN_2LEVELS);
                        ball.renderBall(gRenderer);
                        hole.render(gRenderer);
                        for(int i = 0; i < blockList.size(); i++) {
                            blocks[blockList[i].typeBlock].render(gRenderer, blockList[i].pos.x, blockList[i].pos.y);
                        }
                        if(hasTeleport) {
                            tele1.render(gRenderer);
                            tele2.render(gRenderer);
                        }
                        if(hasSwamp) {
                            swamp.render(gRenderer);
                            swamp.rotateSwamp();
                        }
                    }
                } else {
                    gBackgroundTexture1.render(gRenderer, 0, 0);
                    gEnterTexture.render(gRenderer, (SCREEN_WIDTH - gEnterTexture.getWidth()) / 2, (SCREEN_HEIGHT - gEnterTexture.getHeight()) / 2);
                    gTextEnterTexture.render(gRenderer, (SCREEN_WIDTH - gTextEnterTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextEnterTexture.getHeight()) / 2 + 120);
                    gLogoGame.render(gRenderer, (SCREEN_WIDTH - gLogoGame.getWidth()) / 2, (SCREEN_HEIGHT - gLogoGame.getHeight()) / 2 - 100);
                }
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    TTF_CloseFont( gFont );
    gFont = NULL;
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    close(gWindow, gRenderer);

    return 0;
}
