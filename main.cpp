#include "params.hpp"
#include "LTexture.hpp"
#include "Ball.hpp"
#include "Hole.hpp"
#include "Block.hpp"
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
        gWindow = SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
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
				//if( Mix_OpenAudio(int frequency,Uint16 format,int channels,int chunksize) < 0 )
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
               TTF_Font* gFont,
               SDL_Renderer* &gRenderer){
    bool success = true;
    for(Block&block:blockList){
        if(!block.loadFromFile(gRenderer,"tile32_dark.png")){
            std::cout<<"failed load block texture\n";success = false;
        }
    }

    if(!ball.loadTextureFromFile(gRenderer,"ball.png","point.png","powermeter_bg.png","powermeter_fg.png","powermeter_overlay.png")){
        std::cout<<"failed load ball texture\n";success = false;
    }
    if(!hole.loadFromFile(gRenderer,"hole.png")){
        std::cout<<"failed load hole texture\n";success = false;
    }
    if(!gBackgroundTexture.loadFromFile(gRenderer,"background.png")){
        std::cout<<"failed load backgr\n";success = false;
    }
    if(!gEnterTexture.loadFromFile(gRenderer,"click2start.png")){
        std::cout<<"failed to load enter texture\n";
    }
    if(!gLogoGame.loadFromFile(gRenderer,"logogame.png")){
        std::cout<<"failed to load logo\n";
    }
    gMusic = Mix_LoadMUS("musicgame.wav");
    if(gMusic == NULL){
        std::cout<<"failed to load music theme! SDL_mixer Error: "<<Mix_GetError()<<'\n';
        success =false;
    }
    gFont = TTF_OpenFont("lazy.ttf",20);
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
int main(int argc,char* argv[])
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    LTexture gBackgroundTexture;
    LTexture gEnterTexture;
    TTF_Font *gFont = NULL;
    LTexture gTextEnterTexture;
    LTexture gLogoGame;
    Ball ball;
    vector<Block> blockList(2);
    Block block;
    Hole hole;
    if(!init(gWindow,gRenderer))std::cout<<"init failed\n";
    else{
        if(!loadMedia(gBackgroundTexture,
                      gTextEnterTexture,
                      gEnterTexture,
                      gLogoGame,
                      gMusic,
                      ball,
                      hole,
                      blockList,
                      gFont,
                      gRenderer))
            std::cout<<"load media failed\n";
        else{
            bool quit = false;
            bool isEnter = false;
            bool isPlayMusic = false;
            ball.setPosBall(100,100);
            SDL_Event e;
            while(!quit){
                while(SDL_PollEvent(&e)!=0){
                    if(e.type == SDL_QUIT) quit = true;
                    else if(e.type == SDL_KEYDOWN&&e.key.keysym.sym == SDLK_SPACE) isEnter = true;
                    else if(e.type == SDL_KEYDOWN&&e.key.keysym.sym == SDLK_m){
                        Mix_HaltMusic();
                    }
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    if(x<5||x>SCREEN_WIDTH-5||y<5||y>SCREEN_HEIGHT-5)ball.setPosBall(ball.getPosX(),ball.getPosY());
                    else{
                        ball.handleMouseEvent(&e,gRenderer);
                    }

                }
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
                SDL_RenderClear(gRenderer);
                gBackgroundTexture.render(gRenderer,0,0);

                if(!isPlayMusic){Mix_PlayMusic( gMusic, -1 );isPlayMusic = true;std::cout<<"play music\n";}
                if(isEnter){
                    ball.renderBall(gRenderer);
                    for(int i=0;i<blockList.size();i++){
                        blockList[i].setPos(100*i,400);
                        blockList[i].render(gRenderer);
                    }

                    hole.setPos(200,200);
                    hole.render(gRenderer);
                    ball.moveBall();
                    if(abs(hole.getPosX()-ball.getPosX())>5||abs(hole.getPosY()-ball.getPosY())>5){
                        ball.renderBall(gRenderer);
                    }
                    else{
                        ball.setPosBall(hole.getPosX(),hole.getPosY());
                    }
                }
                else{
                    gEnterTexture.render(gRenderer,(SCREEN_WIDTH-gEnterTexture.getWidth())/2,(SCREEN_HEIGHT-gEnterTexture.getHeight())/2);
                    gTextEnterTexture.render(gRenderer,(SCREEN_WIDTH-gTextEnterTexture.getWidth())/2,(SCREEN_HEIGHT-gTextEnterTexture.getHeight())/2+120);
                    gLogoGame.render(gRenderer,(SCREEN_WIDTH-gLogoGame.getWidth())/2,(SCREEN_HEIGHT-gLogoGame.getHeight())/2-100);
                }
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    TTF_CloseFont( gFont );gFont = NULL;
	Mix_FreeMusic( gMusic );gMusic = NULL;
    close(gWindow,gRenderer);

    return 0;
}
