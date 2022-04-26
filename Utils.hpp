#ifndef UTILS__
#define UTILS__
#include "params.hpp"
#include "LTexture.hpp"
#include "Ball.hpp"
#include "Hole.hpp"
#include "Teleport.hpp"
Mix_Music *gMusic = NULL;
bool init(SDL_Window* &gWindow,SDL_Renderer* &gRenderer){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"SDL couldn't init! SDL Error: "<<SDL_GetError()<<'\n';
        success = false;
    }else{
        //set texture filtering to linear
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
            std::cout<<"warning: linear texture filtering not enabled!\n";
        gWindow = SDL_CreateWindow("game ngu toan bug",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(gWindow==NULL){
            std::cout<<"window couldn't be created! SDL Error: "<<SDL_GetError()<<'\n';
            success = false;
        }
        else{
            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL){
                std::cout<<"renderer couldn't be created! SDL Error: "<<SDL_GetError()<<'\n';
                success = false;
            }
            else{
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);

                //initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags)){
                    std::cout<<"SDL_image couldn't init! SDL_image Error: "<<SDL_GetError()<<'\n';
                    success = false;
                }
                if(TTF_Init()==-1){
                    std::cout<<"SDL_ttf couldn't init! SDL_ttf Error: "<<TTF_GetError()<<"\n";
                    success = false;
                }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
            }
        }
    }return success;
}
bool loadMedia(LTexture &gBackgroundTexture,
               LTexture &gTextEnterTexture,
               LTexture &gEnterTexture,
               LTexture &gLogoGame,
               Mix_Music* &gMusic,
               Ball& ball,
               Hole& hole,
               vector<Block>&blockList,
               Teleport &tele1,
               Teleport &tele2,
               TTF_Font* gFont,
               SDL_Renderer* &gRenderer){
    bool success = true;
    if(!tele1.loadFromFile(gRenderer,"gfx/teleport.png")){
         std::cout<<"failed load teleport texture\n";success = false;
    }
    if(!tele2.loadFromFile(gRenderer,"gfx/teleport.png")){
         std::cout<<"failed load teleport texture\n";success = false;
    }

    for(Block&block:blockList){
        if(!block.loadFromFile(gRenderer,"gfx/tile32_dark.png")){
            std::cout<<"failed load block texture\n";success = false;
        }
    }

    if(!ball.loadTextureFromFile(gRenderer,"gfx/ball.png","gfx/point.png",
                                 "gfx/powermeter_bg.png","gfx/powermeter_fg.png","gfx/powermeter_overlay.png",
                                 "sfx/charge.mp3")){
        std::cout<<"failed load ball texture\n";success = false;
    }
    if(!hole.loadFromFile(gRenderer,"gfx/hole.png")){
        std::cout<<"failed load hole texture\n";success = false;
    }
    if(!gBackgroundTexture.loadFromFile(gRenderer,"gfx/background.png")){
        std::cout<<"failed load backgr\n";success = false;
    }
    if(!gEnterTexture.loadFromFile(gRenderer,"gfx/click2start.png")){
        std::cout<<"failed to load enter texture\n";
    }
    if(!gLogoGame.loadFromFile(gRenderer,"gfx/logoo.png")){
        std::cout<<"failed to load logo\n";
    }
    gMusic = Mix_LoadMUS("musicgame.wav");
    if(gMusic == NULL){
        std::cout<<"failed to load music theme! SDL_mixer Error: "<<Mix_GetError()<<'\n';
        success =false;
    }
    gFont = TTF_OpenFont("gfx/maagkramp.ttf",21);
    if(gFont == NULL) {
        std::cout<<"load lazy font failed!SDL_ttf Font: "<<TTF_GetError()<<'\n';
        success = false;
    }
    else{
        SDL_Color textColor = {0,0,0};
        //if(!gTextEnterTexture.loadFromRenderedText(gRenderer,gFont,"Press \"Space\" to start",textColor)){
        if(!gTextEnterTexture.loadFromRenderedText(gRenderer,gFont,"Press \"Space\" to start",textColor)){
            std::cout<<"failed to render text texture!\n";success = false;
        }
    }
    return success;
}
void close(SDL_Window* &gWindow,SDL_Renderer* &gRenderer){
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL; gWindow = NULL;
    SDL_Quit();IMG_Quit();Mix_Quit();TTF_Quit();
}

#endif // UTILS__
