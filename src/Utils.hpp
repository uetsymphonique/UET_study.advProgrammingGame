#ifndef UTILS__
#define UTILS__
#include "params.hpp"
#include "LTexture.hpp"
#include "Ball.hpp"
#include "Hole.hpp"
#include "Teleport.hpp"
#include "Swamp.hpp"
#include "Timer.hpp"
#include "Ice.hpp"
#include "Wind.hpp"
#include "Player.hpp"
Mix_Music *gMusic = NULL;
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer) {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL couldn't init! SDL Error: " << SDL_GetError() << '\n';
        success = false;
    } else {
        //set texture filtering to linear
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            std::cout << "warning: linear texture filtering not enabled!\n";
        gWindow = SDL_CreateWindow("game ngu toan bug", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL) {
            std::cout << "window couldn't be created! SDL Error: " << SDL_GetError() << '\n';
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL) {
                std::cout << "renderer couldn't be created! SDL Error: " << SDL_GetError() << '\n';
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags)) {
                    std::cout << "SDL_image couldn't init! SDL_image Error: " << SDL_GetError() << '\n';
                    success = false;
                }
                if(TTF_Init() == -1) {
                    std::cout << "SDL_ttf couldn't init! SDL_ttf Error: " << TTF_GetError() << "\n";
                    success = false;
                }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}
bool loadMedia(LTexture &gBackgroundTexture1, LTexture &gBackgroundTexture2, LTexture &gBackgroundTexture3, LTexture &gBackgroundTexture4,
               LTexture &gTextEnterTexture,
               LTexture &gEnterTexture,
               LTexture &gLogoGame,
               Mix_Music* &gMusic,
               LTexture &gIntroTextTexture,
               Ball& ball,
               Hole& hole,
               Block &block1, Block &block2, Block &block3, Block &block4,
               Block &block1Long, Block &block2Long, Block &block3Long, Block &block4Long,
               Block &block1LongR, Block &block2LongR, Block &block3LongR, Block &block4LongR,
               Swamp& swamp,
               Teleport &tele1,
               Teleport &tele2,
               Ice& iceMini,Ice& iceLong, Ice& iceBig,
               Wind&wind200high,Wind&wind300high,Wind&wind200low,Wind&wind300low,
               Wind&wind200highr,Wind&wind300highr,Wind&wind200lowr,Wind&wind300lowr,
               Wind&wind200high_vflip,Wind&wind200high_hflip,
               TTF_Font* &gFont,
               SDL_Renderer* &gRenderer) {
    bool success = true;
    if(!wind200high.loadFromFile(gRenderer,"gfx/wind.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind200high_vflip.loadFromFile(gRenderer,"gfx/wind.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind200high_hflip.loadFromFile(gRenderer,"gfx/wind.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind200highr.loadFromFile(gRenderer,"gfx/wind.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind200low.loadFromFile(gRenderer,"gfx/wind.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind200lowr.loadFromFile(gRenderer,"gfx/wind.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind300high.loadFromFile(gRenderer,"gfx/wind300.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind300highr.loadFromFile(gRenderer,"gfx/wind300.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind300low.loadFromFile(gRenderer,"gfx/wind300.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!wind300lowr.loadFromFile(gRenderer,"gfx/wind300.png")){
        std::cout<<"failed load wind texture\n";
        success = false;
    }
    if(!iceMini.loadFromFile(gRenderer,"gfx/ice.png")){
        std::cout<<"failed load ice texture\n";
        success = false;
    }
    if(!iceLong.loadFromFile(gRenderer,"gfx/ice2.png")){
        std::cout<<"failed load ice texture\n";
        success = false;
    }
    if(!iceBig.loadFromFile(gRenderer,"gfx/ice3.png")){
        std::cout<<"failed load ice texture\n";
        success = false;
    }
    if(!tele1.loadFromFile(gRenderer, "gfx/teleport.png")) {
        std::cout << "failed load teleport texture\n";
        success = false;
    }
    if(!tele2.loadFromFile(gRenderer, "gfx/teleport.png")) {
        std::cout << "failed load teleport texture\n";
        success = false;
    }
    if(!block1.loadFromFile(gRenderer, "gfx/tile32_dark.png")) {
        std::cout << "failed load block1 texture\n";
        success = false;
    }
    if(!block2.loadFromFile(gRenderer, "gfx/tile32_lightyellow.png")) {
        std::cout << "failed load block2 texture\n";
        success = false;
    }
    if(!block3.loadFromFile(gRenderer, "gfx/tile32_lightpink.png")) {
        std::cout << "failed load block3 texture\n";
        success = false;
    }
    if(!block4.loadFromFile(gRenderer, "gfx/tile32_lightblue.png")) {
        std::cout << "failed load block4 texture\n";
        success = false;
    }
    if(!block1Long.loadFromFile(gRenderer, "gfx/tile32_dark150.png")) {
        std::cout << "failed load block1Long texture\n";
        success = false;
    }
    if(!block2Long.loadFromFile(gRenderer, "gfx/tile32_lightyellow150.png")) {
        std::cout << "failed load block2Long texture\n";
        success = false;
    }
    if(!block3Long.loadFromFile(gRenderer, "gfx/tile32_lightpink150.png")) {
        std::cout << "failed load block3Long texture\n";
        success = false;
    }
    if(!block4Long.loadFromFile(gRenderer, "gfx/tile32_lightblue150.png")) {
        std::cout << "failed load block4Long texture\n";
        success = false;
    }
    if(!block1LongR.loadFromFile(gRenderer, "gfx/tile32_dark150rotate.png")) {
        std::cout << "failed load block1Long texture\n";
        success = false;
    }
    if(!block2LongR.loadFromFile(gRenderer, "gfx/tile32_lightyellow150rotate.png")) {
        std::cout << "failed load block2Long texture\n";
        success = false;
    }
    if(!block3LongR.loadFromFile(gRenderer, "gfx/tile32_lightpink150rotate.png")) {
        std::cout << "failed load block3Long texture\n";
        success = false;
    }
    if(!block4LongR.loadFromFile(gRenderer, "gfx/tile32_lightblue150rotate.png")) {
        std::cout << "failed load block4Long texture\n";
        success = false;
    }
    if(!swamp.loadFromFile(gRenderer, "gfx/swamp.png")) {
        std::cout << "failed load swamp texture\n";
        success = false;
    }

    if(!ball.loadTextureFromFile(gRenderer, "gfx/ball.png", "gfx/point.png",
                                 "gfx/powermeter_bg.png", "gfx/powermeter_fg.png", "gfx/powermeter_overlay.png",
                                 "sfx/charge.mp3")) {
        std::cout << "failed load ball texture\n";
        success = false;
    }
    if(!hole.loadFromFile(gRenderer, "gfx/hole.png")) {
        std::cout << "failed load hole texture\n";
        success = false;
    }
    if(!gBackgroundTexture1.loadFromFile(gRenderer, "gfx/background.png")) {
        std::cout << "failed load backgr\n";
        success = false;
    }
    if(!gBackgroundTexture2.loadFromFile(gRenderer, "gfx/background_desert.png")) {
        std::cout << "failed load backgr\n";
        success = false;
    }
    if(!gBackgroundTexture3.loadFromFile(gRenderer, "gfx/background_tropicalLand.png")) {
        std::cout << "failed load backgr\n";
        success = false;
    }
    if(!gBackgroundTexture4.loadFromFile(gRenderer, "gfx/background_iceAge.png")) {
        std::cout << "failed load backgr\n";
        success = false;
    }
    if(!gEnterTexture.loadFromFile(gRenderer, "gfx/click2start.png")) {
        std::cout << "failed to load enter texture\n";
    }
    if(!gLogoGame.loadFromFile(gRenderer, "gfx/logoo.png")) {
        std::cout << "failed to load logo\n";
    }
    gMusic = Mix_LoadMUS("sfx/musicgame.wav");
    if(gMusic == NULL) {
        std::cout << "failed to load music theme! SDL_mixer Error: " << Mix_GetError() << '\n';
        success = false;
    }
    gFont = TTF_OpenFont("gfx/fontgame.ttf", 21);
    if(gFont == NULL) {
        std::cout << "load lazy font failed!SDL_ttf Font: " << TTF_GetError() << '\n';
        success = false;
    } else {
        SDL_Color textColor = {0, 0, 0};
        //if(!gTextEnterTexture.loadFromRenderedText(gRenderer,gFont,"Press \"Space\" to start",textColor)){
        if(!gTextEnterTexture.loadFromRenderedText(gRenderer, gFont, "Press \"Space\" to start", textColor)) {
            std::cout << "failed to render text texture!\n";
            success = false;
        }
        string introText = "A little game from TQM";
        if(!gIntroTextTexture.loadFromRenderedText(gRenderer, gFont, introText, textColor)) {
            std::cout << "failed to render text texture!\n";
            success = false;
        }
    }

    return success;
}
void renderMenuAndLogo(SDL_Renderer* &gRenderer, LTexture &gBackgroundTexture,
                       LTexture &gEnterTexture, LTexture &gTextEnterTexture, LTexture &gLogoGame) {
    gBackgroundTexture.render(gRenderer, 0, 0);
    gEnterTexture.render(gRenderer, (SCREEN_WIDTH - gEnterTexture.getWidth()) / 2, (SCREEN_HEIGHT - gEnterTexture.getHeight()) / 2);
    gTextEnterTexture.render(gRenderer, (SCREEN_WIDTH - gTextEnterTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextEnterTexture.getHeight()) / 2 + 120);
    gLogoGame.render(gRenderer, (SCREEN_WIDTH - gLogoGame.getWidth()) / 2, (SCREEN_HEIGHT - gLogoGame.getHeight()) / 2 - 100);
}
void renderIntro(SDL_Renderer* &gRenderer, LTexture& gBackgroundTexture,LTexture& gIntroTextTexture,Timer &gameTimer){
    gBackgroundTexture.render(gRenderer, 0, 0);
    gIntroTextTexture.setBlendMode(SDL_BLENDMODE_BLEND);
    gIntroTextTexture.setAlpha(gameTimer.distanceTime() * 255 / TIME_BETWEEN_2LEVELS);
    gIntroTextTexture.render(gRenderer, (SCREEN_WIDTH - gIntroTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gIntroTextTexture.getHeight()) / 2);
}
void renderResultWinEachLevel(SDL_Renderer* &gRenderer, LTexture& gBackgroundTexture,
                              LTexture& gWinEachLevelTextTexture,LTexture&gResultEachLevelTextTexture,
                              TTF_Font* &gFont,
                              int mission,int swings){
    gBackgroundTexture.render(gRenderer);
    string s1 = "Mission " + to_string(mission) + " completed!";
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
}
void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer) {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}

#endif // UTILS__
