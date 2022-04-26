#ifndef TELEPORTCLASS__
#define TELEPORTCLASS__
#include "params.hpp"
#include "LTexture.hpp"
class Teleport:public LTexture{
private:
public:
    Teleport();
    Teleport(int mW,int mH,SDL_Texture* mT);
};
#endif // TELEPORTCLASS__
