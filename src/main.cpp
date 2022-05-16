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
#include "Player.hpp"
#include "InfoWind.hpp"
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char* argv[]) {
    vector<Player> topPlayers(10);
    vector<int>tempMinSw(NUM_OF_LEVELS);
    vector<int>minSwingsEachLevel(NUM_OF_LEVELS);
    int minTotalSwings = 0, tempMinTotal = 0;;
    fstream highScoresStream;
    highScoresStream.open("note.txt", ios::in );
    if(!highScoresStream.is_open()) {
        std::cout << "failed to open file\n";
        return 404;
    }
    for(int i = 0; i < topPlayers.size(); i++)highScoresStream >> topPlayers[i];
    for(int i = 0; i < minSwingsEachLevel.size(); i++) {
        highScoresStream >> minSwingsEachLevel[i];
        tempMinSw[i] = minSwingsEachLevel[i];
    }
    highScoresStream >> minTotalSwings;
    highScoresStream.close();
    tempMinTotal = minTotalSwings;
    for(int i = 0; i < topPlayers.size(); i++) cout << topPlayers[i] << '\n';
    for(int i = 0; i < minSwingsEachLevel.size(); i++)cout << minSwingsEachLevel[i] << " ";
    cout << minTotalSwings << '\n';

    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    LTexture gBackgroundTexture1;
    LTexture gBackgroundTexture2;
    LTexture gBackgroundTexture3;
    LTexture gBackgroundTexture4;
    LTexture gBackgroundTexture;


    LTexture gEnterTexture;
    TTF_Font *gFont = NULL;
    LTexture gTextEnterTexture[NUM_OF_CHOICES_IN_MENU];
    LTexture gLogoGame;

    LTexture gIntroTextTexture;

    Ball ball;

    Hole hole;
    SDL_Rect holeRect;
    Mix_Chunk* gHoleChunk = NULL;

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
    vector<SDL_Rect>swampRectList;
    bool isSwamped = false;
    Timer swampedBallTimer;

    bool hasWind = false;
    Wind wind200high, wind300high, wind200low, wind300low, wind200highr, wind300highr, wind200lowr, wind300lowr, wind200high_vflip, wind200high_hflip;
    vector<InfoWind>windList;
    vector<SDL_Rect>windRectList;

    bool hasIce = false;
    Ice iceMini, iceLong, iceBig;
    vector<InfoIce>iceList;
    vector<SDL_Rect>iceRectList;

    LTexture gSwingsTextTexture;

    LTexture gWinEachLevelTextTexture;
    LTexture gResultEachLevelTextTexture;
    LTexture gHighScoresTextTexture;
    LTexture gNameTitle;
    LTexture gRankingTitle;
    LTexture gScoreTitle;
    LTexture gPlayerNameTextTexture[10];
    LTexture gPlayerScoreTextTexture[10];

    LTexture gBackgroundSaveNameTexture;
    LTexture gDialogTypeNameTexture;
    LTexture gTypeNameTitle;
    LTexture gNameTypingTexture;

    if(!init(gWindow, gRenderer))std::cout << "init failed\n";
    else {
        if(!loadMedia(gBackgroundTexture1, gBackgroundTexture2, gBackgroundTexture3, gBackgroundTexture4, gBackgroundSaveNameTexture,
                      gTextEnterTexture,
                      gEnterTexture,
                      gLogoGame,
                      gMusic,
                      gIntroTextTexture,
                      gRankingTitle, gNameTitle, gScoreTitle,
                      gDialogTypeNameTexture, gTypeNameTitle,
                      ball,
                      hole,gHoleChunk,
                      block1, block2, block3, block4,
                      block1Long, block2Long, block3Long, block4Long,
                      block1LongR, block2LongR, block3LongR, block4LongR,
                      swamp,
                      tele1, tele2,
                      iceMini, iceLong, iceBig,
                      wind200high, wind300high, wind200low, wind300low,
                      wind200highr, wind300highr, wind200lowr, wind300lowr,
                      wind200high_vflip, wind200high_hflip,
                      gFont,
                      gRenderer))
            std::cout << "load media failed\n";
        else {

            bool quit = false;
            bool isEnter = false;
            bool isWin = true;
            bool isHighScores = false;
            bool currentPlayerIsSaved = false;
            bool isSave = false;
            int choiceMenu = 0;
            int swings = 0;
            int totalSwings = 0;
            string nameTyping = "";
            int indexLevel;
            vector<Block>blocks(NUM_OF_TYPES_BLOCK);
            {
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
            }

            vector<Ice>ices(NUM_OF_TYPES_ICE);
            {
                ices[ICEMINI] = iceMini;
                ices[ICELONG] = iceLong;
                ices[ICEBIG] = iceBig;
            }

            vector<Wind>winds(NUM_OF_TYPES_WIND);
            {
                winds[WIND200HIGH] = wind200high;
                winds[WIND200HIGH].setSpeedScroll(3);
                winds[WIND200HIGHR] = wind200highr;
                winds[WIND200HIGHR].setSpeedScroll(3);
                winds[WIND300HIGH] = wind300high;
                winds[WIND300HIGH].setSpeedScroll(3);
                winds[WIND300HIGHR] = wind300highr;
                winds[WIND300HIGHR].setSpeedScroll(3);
                winds[WIND200LOW] = wind200high;
                winds[WIND200LOW].setSpeedScroll(6);
                winds[WIND200LOWR] = wind200highr;
                winds[WIND200LOWR].setSpeedScroll(6);
                winds[WIND300LOW] = wind300high;
                winds[WIND300LOW].setSpeedScroll(6);
                winds[WIND300LOWR] = wind300highr;
                winds[WIND300LOWR].setSpeedScroll(6);
                winds[WIND200HIGH_VFLIP] = wind200high_vflip;
                winds[WIND200HIGH_VFLIP].setSpeedScroll(3);
                winds[WIND200HIGH_HFLIP] = wind200high_hflip;
                winds[WIND200HIGH_HFLIP].setSpeedScroll(3);
            }

            SDL_Event e;
            cout << levels.size();
            iota(levels.begin(), levels.end(), 0);
            while(!quit) {
                while(SDL_PollEvent(&e) != 0) {
                    if(e.type == SDL_QUIT) quit = true;
                    else if(e.type == SDL_KEYDOWN) {
                        if(e.key.keysym.sym == SDLK_ESCAPE) {
                            isEnter = false;
                            isHighScores = false;
                        } else if(e.key.keysym.sym == SDLK_SPACE) {
                            if(isSave && nameTyping.size() <= 12) {
                                nameTyping += char(e.key.keysym.sym);
                            }
                            if(choiceMenu == 0 && !isHighScores ) {
                                isEnter = true;
                            }
                            if(choiceMenu == 1 && !isEnter) {
                                isHighScores = true;
                            }
                            break;
                        }

                        else if(e.key.keysym.sym == SDLK_m) {
                            if(isSave && nameTyping.size() <= 12) {
                                nameTyping += char(SDLK_m);
                            } else {
                                if( Mix_PlayingMusic() == 0 ) {
                                    Mix_PlayMusic( gMusic, -1 );
                                } else {
                                    if( Mix_PausedMusic() == 1 ) {
                                        Mix_ResumeMusic();
                                    } else {
                                        Mix_PauseMusic();
                                    }
                                }
                            }
                        } else if((e.key.keysym.sym <= SDLK_z && e.key.keysym.sym >= SDLK_a)
                                  || (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9)
                                  || e.key.keysym.sym == SDLK_PERIOD) {
                            if(isSave && nameTyping.size() <= 12) {
                                nameTyping += char(e.key.keysym.sym);
                            }
                        } else if(e.key.keysym.sym == SDLK_BACKSPACE) {
                            if(isSave) {
                                nameTyping.erase(nameTyping.size() - 1);
                            }
                        } else if(e.key.keysym.sym == SDLK_UP) {
                            if(!isEnter && !isHighScores) {
                                choiceMenu++;
                                choiceMenu %= NUM_OF_CHOICES_IN_MENU;
                            }
                        } else if(e.key.keysym.sym == SDLK_DOWN) {
                            if(!isEnter && !isHighScores) {
                                choiceMenu--;
                                choiceMenu += NUM_OF_CHOICES_IN_MENU;
                                choiceMenu %= NUM_OF_CHOICES_IN_MENU;
                            }
                        } else if(e.key.keysym.sym == SDLK_RETURN) {
                            if(isSave) {
                                currentPlayerIsSaved = true;
                            }
                        }
                    }
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if(x < 5 || x > SCREEN_WIDTH - 5 || y < 5 || y > SCREEN_HEIGHT - 5)ball.setPosBall(ball.getPosX(), ball.getPosY());
                    else {
                        if(!isSwamped&&!isWin&&isEnter) ball.handleMouseEvent(&e, gRenderer, swings, totalSwings);
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                ball.setBlendMode(SDL_BLENDMODE_BLEND);
                if( Mix_PlayingMusic() == 0 ) {
                    Mix_PlayMusic( gMusic, -1 );
                }

                //isEnter true thì hiện màn chơi
                if(isEnter) {
                    if(isWin && levels.size() > 0 && gameTimer.distanceTime() >= TIME_BETWEEN_2LEVELS) {
                        indexLevel = 0;
                        swings = 0;
                        isWin = false;
                        switch(levels[indexLevel]) {
                        case 0: { //normal
                            hasTeleport = false;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture1;
                            ball.setPosBall(200, 600);
                            blockList.resize(2);
                            blockList[0] = InfoBlock(50, 130, BLOCK1LONGR);
                            blockList[1] = InfoBlock(280, 130, BLOCK1LONGR);
                            blockRectList[0] = {50, 130, 147, 32};
                            blockRectList[1] = {280, 130, 147, 32};
                            hole.setPos(200, 100);
                        }
                        break;
                        case 1: { //normal
                            hasTeleport = false;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture1;
                            ball.setPosBall(200, 600);
                            blockList.resize(4);
                            blockList[0] = InfoBlock(50, 100, BLOCK1);
                            blockRectList[0] = {50, 100, 32, 32};
                            blockList[1] = InfoBlock(blockRectList[0].x + 70, blockRectList[0].y - 70, BLOCK1);
                            blockRectList[1] = {blockRectList[0].x + 70, blockRectList[0].y - 70, 32, 32};
                            blockList[2] = InfoBlock(blockRectList[0].x, blockRectList[0].y + 100, BLOCK1LONGR);
                            blockRectList[2] = {blockRectList[0].x, blockRectList[0].y + 100, 147, 32};
                            blockList[3] = InfoBlock(blockRectList[0].x + 200, blockRectList[1].y, BLOCK1LONG);
                            blockRectList[3] = {blockRectList[0].x + 200, blockRectList[1].y, 32, 147};
                            hole.setPos(blockRectList[1].x, blockRectList[0].y);
                        }
                        break;
                        case 2: { //normal
                            hasTeleport = false;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture1;
                            ball.setPosBall(240, 610);
                            blockList.resize(8);
                            blockList[0] = InfoBlock(150, 300, BLOCK1LONGR);
                            blockRectList[0] = {150, 300, 147, 32};
                            blockList[1] = InfoBlock(blockRectList[0].x + 147 + 32, blockRectList[0].y + 32 - 147, BLOCK1LONG);
                            blockRectList[1] = {blockRectList[0].x + 147 + 32, blockRectList[0].y + 32 - 147, 32, 147};
                            blockList[2] = InfoBlock(blockRectList[1].x + 32 - 147, blockRectList[1].y - 32 - 32, BLOCK1LONGR);
                            blockRectList[2] = {blockRectList[1].x + 32 - 147, blockRectList[1].y - 32 - 32, 147, 32};
                            blockList[3] = InfoBlock(blockRectList[2].x - 32 - 32, blockRectList[2].y, BLOCK1LONG);
                            blockRectList[3] = {blockRectList[2].x - 32 - 32, blockRectList[2].y, 32, 147};
                            blockList[4] = InfoBlock(blockRectList[0].x + 147, blockRectList[0].y + 32 + 64, BLOCK1);
                            blockRectList[4] = {blockRectList[0].x + 147, blockRectList[0].y + 32 + 64, 32, 32};
                            blockList[5] = InfoBlock(blockRectList[1].x + 32 + 64, blockRectList[1].y - 32, BLOCK1);
                            blockRectList[5] = {blockRectList[1].x + 32 + 64, blockRectList[1].y - 32, 32, 32};
                            blockList[6] = InfoBlock(blockRectList[2].x - 32, blockRectList[2].y - 64 - 32, BLOCK1);
                            blockRectList[6] = {blockRectList[2].x - 32, blockRectList[2].y - 64 - 32, 32, 32};
                            blockList[7] = InfoBlock(blockRectList[0].x - 64 - 32, blockRectList[0].y - 32, BLOCK1);
                            blockRectList[7] = {blockRectList[0].x - 64 - 32, blockRectList[0].y - 32, 32, 32};
                            hole.setPos(250, 210);
                        }
                        break;
                        case 3: { //sandy
                            hasTeleport = false;
                            hasSwamp = true;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture2;
                            ball.setPosBall(200, 610);
                            blockList.resize(5);
                            blockList[0] = InfoBlock(200, 500, BLOCK2);
                            blockRectList[0] = {200, 500, 32, 32};
                            blockList[1] = InfoBlock(400, 500, BLOCK2);
                            blockRectList[1] = {400, 500, 32, 32};
                            blockList[2] = InfoBlock(400, 200, BLOCK2LONG);
                            blockRectList[2] = {400, 200, 32, 147};
                            blockList[3] = InfoBlock(60, 120, BLOCK2LONGR);
                            blockRectList[3] = {60, 120, 147, 32};
                            blockList[4] = InfoBlock(60 + 147 + 40, 120, BLOCK2LONG);
                            blockRectList[4] = {60 + 147 + 40, 120, 32, 147};
                            swampRectList.resize(3);
                            swampRectList[0] = {50, 320, 64, 64};
                            swampRectList[1] = {300, 160, 64, 64};
                            swampRectList[2] = {120, 320, 64, 64};
                            hole.setPos(100, 200);
                        }
                        break;
                        case 4: { //sandy
                            hasTeleport = false;
                            hasSwamp = true;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture2;
                            ball.setPosBall(240, 610);
                            blockList.resize(5);
                            swampRectList.resize(4);
                            blockList[0] = InfoBlock(50, 150, BLOCK2LONG);
                            blockRectList[0] = {50, 150, 32, 147};
                            blockList[1] = InfoBlock(400, 200, BLOCK2LONG);
                            blockRectList[1] = {400, 200, 32, 147};
                            blockList[2] = InfoBlock(200, 610, BLOCK2);
                            blockRectList[2] = {200, 610, 32, 32};
                            blockList[3] = InfoBlock(150, 50, BLOCK2LONGR);
                            blockRectList[3] = {150, 50, 147, 32};
                            swampRectList[0] = {150, 150, 64, 64};
                            swampRectList[1] = {150, 250, 64, 64};
                            swampRectList[2] = {250, 250, 64, 64};
                            blockList[4] = InfoBlock(swampRectList[1].x + 30, swampRectList[1].y + 64 + 40, BLOCK2LONGR);
                            blockRectList[4] = {swampRectList[1].x + 30, swampRectList[1].y + 64 + 40, 147, 32};
                            swampRectList[3] = {blockRectList[0].x, blockRectList[3].y, 64, 64};
                            hole.setPos(150, 110);

                        }
                        break;
                        case 5: { //tropical
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
                        case 6: { //tropical
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
                        case 7: { //tropical
                            hasTeleport = true;
                            hasSwamp = false;
                            hasWind = false;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            tele1.setPos(82, 130);
                            tele2.setPos(100, 580);
                            pairTeleRectList[0].rect1 = tele1.getRect();
                            pairTeleRectList[0].rect2 = tele2.getRect();
                            gBackgroundTexture = gBackgroundTexture3;
                            ball.setPosBall(330, 610);
                            blockList.resize(18);
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
                        case 8: { //ice age
                            hasTeleport = false;
                            hasSwamp = false;
                            hasWind = true;
                            hasIce = false;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture4;
                            ball.setPosBall(450, 580);
                            blockList.resize(5);
                            blockList[0] = InfoBlock(0, 130, BLOCK4LONGR);
                            blockList[4] = InfoBlock(147 + 16, 130, BLOCK4LONGR);
                            blockRectList[0] = {0, 130, 147, 32};
                            blockRectList[4] = {147 + 20, 130, 147, 32};
                            windRectList.resize(3);
                            windList.resize(3);
                            windList[0] = InfoWind(50, 380, WIND200LOW);
                            windRectList[0] = {50, 380, 200, 64};
                            windList[1] = InfoWind(windRectList[0].x + 200, windRectList[0].y - 64, WIND200HIGH_HFLIP);
                            windRectList[1] = {windRectList[0].x + 200, windRectList[0].y - 64, 200, 64};
                            windList[2] = InfoWind(windRectList[1].x - 200, windRectList[1].y - 64, WIND200LOWR);
                            windRectList[2] = {windRectList[1].x - 200, windRectList[1].y - 64, 200, 64};
                            blockList[2] = InfoBlock(0, windRectList[0].y + 64, BLOCK4LONGR);
                            blockRectList[2] = {0, windRectList[0].y + 64, 147, 32};
                            blockList[3] = InfoBlock(SCREEN_WIDTH - 147, blockRectList[2].y, BLOCK4LONGR);
                            blockRectList [3] = {SCREEN_WIDTH - 147, blockRectList[2].y, 147, 32};
                            blockList[1] = InfoBlock(SCREEN_WIDTH - 147, windRectList[2].y - 80, BLOCK4LONG);
                            blockRectList[1] = {SCREEN_WIDTH - 147, windRectList[2].y - 80, 32, 147};
                            hole.setPos(350, 100);
                        }
                        break;
                        case 9: { //ice age
                            hasTeleport = false;
                            hasSwamp = false;
                            hasWind = true;
                            hasIce = true;
                            levels.erase(levels.begin() + indexLevel);
                            gBackgroundTexture = gBackgroundTexture4;
                            ball.setPosBall(360, 620);
                            iceList.resize(2);
                            iceRectList.resize(2);
                            iceList[0] = InfoIce(SCREEN_WIDTH - 150, 600 - 64, ICELONG);
                            iceRectList[0] = {SCREEN_WIDTH - 150, 600 - 64, 150, 64};
                            blockList.resize(8);
                            windList.resize(3);
                            windRectList.resize(3);
                            blockList[0] = InfoBlock(iceRectList[0].x - 32, SCREEN_HEIGHT - 147, BLOCK4LONG);
                            blockRectList[0] = {iceRectList[0].x - 32, SCREEN_HEIGHT - 147, 32, 147};
                            windList[0] = InfoWind(blockRectList[0].x - 200, blockRectList[0].y, WIND200HIGH_HFLIP);
                            windRectList[0] = {blockRectList[0].x - 200, blockRectList[0].y, 200, 64};
                            windList[1] = InfoWind(SCREEN_WIDTH - 200, iceRectList[0].y - 50 - 64, WIND200HIGHR);
                            windRectList[1] = {SCREEN_WIDTH - 200, iceRectList[0].y - 50 - 64, 200, 64};
                            blockList[1] = InfoBlock(SCREEN_WIDTH - 147, windRectList[1].y - 32, BLOCK4LONGR);
                            blockRectList [1] = {SCREEN_WIDTH - 147, windRectList[1].y - 32, 147, 32};
                            blockList[2] = InfoBlock(windRectList[1].x, windRectList[1].y - 147, BLOCK4LONG);
                            blockRectList[2] = {windRectList[1].x, windRectList[1].y - 147, 32, 147};
                            blockList[3] = InfoBlock(windRectList[0].x - 32, windRectList[0].y - 147, BLOCK4LONG);
                            blockRectList[3] = {windRectList[0].x - 32, windRectList[0].y - 147, 32, 147};
                            blockList[4] = InfoBlock(blockRectList[3].x, blockRectList[3].y - 128 - 147, BLOCK4LONG);
                            blockRectList[4] = {blockRectList[3].x, blockRectList[3].y - 128 - 147, 32, 147};
                            iceList[1] = InfoIce(blockRectList[3].x, blockRectList[3].y - 128, ICEBIG);
                            iceRectList[1] = {blockRectList[3].x, blockRectList[3].y - 128, 128, 128};
                            windList[2] = InfoWind(blockRectList[4].x + 32, blockRectList[4].y - 25, WIND300LOWR);
                            windRectList[2] = {blockRectList[4].x + 32, blockRectList[4].y - 25, 300, 64};
                            blockList[5] = InfoBlock(blockRectList[2].x + 32 + 28, blockRectList[2].y, BLOCK4);
                            blockRectList[5] = {blockRectList[2].x + 32 + 28, blockRectList[2].y, 32, 32};
                            blockList[6] = InfoBlock(blockRectList[5].x + 32 + 28, blockRectList[5].y, BLOCK4);
                            blockRectList[6] = {blockRectList[5].x + 32 + 28, blockRectList[5].y, 32, 32};
                            blockList[7] = InfoBlock(blockRectList[6].x + 32 + 28, blockRectList[6].y, BLOCK4);
                            blockRectList[7] = {blockRectList[6].x + 32 + 28, blockRectList[6].y, 32, 32};
                            hole.setPos(blockRectList[6].x, blockRectList[6].y + 50);
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
                        if(!isSwamped) swampedBallTimer.updateTime();
                        if(!isSwamped || (isSwamped && swampedBallTimer.distanceTime() > 4000)) {
                            if(isSwamped) {
                                ball.setPosBall(ball.getPosBeforeSwing().x, ball.getPosBeforeSwing().y);
                            }
                            isSwamped = false;
                            ball.setAlpha(255);
                            ball.moveBall(blockRectList, blockList.size(), pairTeleRectList, 1,
                                          swampRectList, isSwamped,
                                          iceRectList,
                                          windRectList, windList,
                                          hasSwamp, hasTeleport, hasWind, hasIce);
                        } else {
                            ball.turnAround();
                            ball.setAlpha(255 - swampedBallTimer.distanceTime() * 255 / 4000);
                        }

                        ball.renderBall(gRenderer);
                        hole.render(gRenderer);
                        renderAllObjects(gRenderer,
                                         blocks, blockList, tele1, tele2,
                                         swamp, swampRectList,
                                         ices, iceList, winds, windList,
                                         hasTeleport, hasSwamp, hasIce, hasWind);

                        holeRect = hole.getRect();
                        holeRect.h = 16;
                        if(ball.getScaleVelocity() > ball.MIN_VEL_OUT_HOLE || !checkCollisionCircleWithRect(ball.getRect(), holeRect)) {
                            ball.renderBall(gRenderer);
                        } else {
                            isWin = true;
                            Mix_PlayChannel(-1,gHoleChunk,0);
                            ball.setPosBall(hole.getPosX(), hole.getPosY());
                            ball.renderBall(gRenderer);
                        }
                    } else if(levels.size() == NUM_OF_LEVELS) {
                        renderIntro(gRenderer, gBackgroundTexture1, gIntroTextTexture, gameTimer);

                    } else if(levels.size() > 0) {
                        renderResultWinEachLevel(gRenderer, gBackgroundTexture,
                                                 gWinEachLevelTextTexture, gResultEachLevelTextTexture,
                                                 gHighScoresTextTexture,
                                                 gFont,
                                                 NUM_OF_LEVELS - levels.size(), swings,
                                                 minSwingsEachLevel[NUM_OF_LEVELS - levels.size() - 1], tempMinSw[NUM_OF_LEVELS - levels.size() - 1]);
                    } else if(levels.size() == 0) {
                        if(gameTimer.distanceTime() <= TIME_BETWEEN_2LEVELS) {
                            if(gameTimer.distanceTime() <= TIME_BETWEEN_2LEVELS / 2) {
                                renderResultWinEachLevel(gRenderer,
                                                         gBackgroundTexture, gWinEachLevelTextTexture,
                                                         gResultEachLevelTextTexture, gHighScoresTextTexture, gFont,
                                                         NUM_OF_LEVELS - levels.size(), swings,
                                                         minSwingsEachLevel[NUM_OF_LEVELS - levels.size() - 1], tempMinSw[NUM_OF_LEVELS - levels.size() - 1]);
                            } else renderWinOverall(gRenderer,
                                                        gBackgroundTexture1, gWinEachLevelTextTexture,
                                                        gResultEachLevelTextTexture, gHighScoresTextTexture, gFont,
                                                        totalSwings, minTotalSwings, tempMinTotal);
                        }
                        if(gameTimer.distanceTime() >= TIME_BETWEEN_2LEVELS) {
                            isSave = true;
                            if(currentPlayerIsSaved) {
                                Player currentPlayer = Player(nameTyping, totalSwings);
                                sortPlayer(topPlayers, currentPlayer);
                                updateHighScores(minSwingsEachLevel, tempMinSw, minTotalSwings, tempMinTotal);
                                levels.resize(NUM_OF_LEVELS);
                                iota(levels.begin(), levels.end(), 0);
                                nameTyping = "";
                                isEnter = false;
                                isSave = false;
                                currentPlayerIsSaved = false;
                            } else {
                                gBackgroundSaveNameTexture.render(gRenderer);
                                gDialogTypeNameTexture.render(gRenderer, (SCREEN_WIDTH - gDialogTypeNameTexture.getWidth()) / 2,
                                                              (SCREEN_HEIGHT - gDialogTypeNameTexture.getHeight()) / 2);
                                gTypeNameTitle.render(gRenderer, (SCREEN_WIDTH - gTypeNameTitle.getWidth()) / 2,
                                                      gDialogTypeNameTexture.getPosY() + (63 - gTypeNameTitle.getHeight()) / 2);
                                SDL_Color textColor = {0, 0, 0};
                                if(!gNameTypingTexture.loadFromRenderedText(gRenderer, gFont, nameTyping + "_", textColor)) {
                                    std::cout << "failed to load name typing texture!\n";
                                }
                                gNameTypingTexture.render(gRenderer, (SCREEN_WIDTH - gNameTypingTexture.getWidth()) / 2,
                                                          gDialogTypeNameTexture.getPosY() + 84 + (59 - gNameTypingTexture.getHeight()) / 2);
                            }

                        }
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
                        renderAllObjects(gRenderer,
                                         blocks, blockList, tele1, tele2,
                                         swamp, swampRectList,
                                         ices, iceList, winds, windList,
                                         hasTeleport, hasSwamp, hasIce, hasWind);
                    }
                } else {
                    totalSwings = 0;
                    if(!isHighScores) renderMenuAndLogo(gRenderer, gBackgroundTexture1, gEnterTexture, gTextEnterTexture, gLogoGame, choiceMenu);
                    else {
                        renderHighScoreBoard(gRenderer, gBackgroundTexture4, gRankingTitle, gNameTitle, gScoreTitle, gPlayerNameTextTexture, gPlayerScoreTextTexture, gFont, topPlayers);
                    }
                }
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    highScoresStream.open("note.txt", ios::out | ios::trunc);
    updateDatabaseScores(highScoresStream, topPlayers, minSwingsEachLevel, minTotalSwings);
    highScoresStream.close();
    TTF_CloseFont( gFont );
    gFont = NULL;
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    close(gWindow, gRenderer);
    return 0;
}
