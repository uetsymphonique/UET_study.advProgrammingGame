#ifndef LBUTTONCLASS__
#define LBUTTONCLASS__
#include "LTexture.hpp"
class LButton:public LTexture{
public:
    LButton();
    bool loadButtonFromFile(SDL_Renderer* &gRenderer,std::string path1,std::string path2);
    void handleEvent(SDL_Event*e);
    void renderButton(SDL_Renderer* &gRenderer);
    bool hasClicked();
    void setClicked(bool clicked);
private:
    const int MOUSE_IN = 1;
    const int MOUSE_OUT = 0;
    LTexture mouseComing;
    int status = 0;
    bool isClicked = false;
};
#endif // LBUTTONCLASS__
