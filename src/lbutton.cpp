#include "LButton.hpp"
LButton::LButton(){
    LTexture();
}
bool LButton::loadButtonFromFile(SDL_Renderer* &gRenderer,std::string path1,std::string path2){
    bool success = true;
    if(!loadFromFile(gRenderer,path1)){
        std::cout<<"failed to load button1\n";
        success = false;
    }
    if(!mouseComing.loadFromFile(gRenderer,path2)){
        std::cout<<"failed to load button2\n";
        success = false;
    }
    return success;
}
void LButton::renderButton(SDL_Renderer* &gRenderer){
    if(status == MOUSE_IN) mouseComing.render(gRenderer);
    else render(gRenderer);
}
bool LButton::hasClicked(){
    return isClicked;
}
void LButton::setClicked(bool clicked){
    isClicked = clicked;
}
void LButton::handleEvent(SDL_Event* e){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        int x,y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if(x<pos.x) inside = false;
        if(y<pos.y) inside = false;
        if(x>pos.x+mWidth) inside = false;
        if(y>pos.y+mHeight) inside = false;
        if(inside){
            status=MOUSE_IN;
            if(e->type == SDL_MOUSEBUTTONDOWN){
                isClicked = true;
            }
        }
        else status = MOUSE_OUT;
    }
}

