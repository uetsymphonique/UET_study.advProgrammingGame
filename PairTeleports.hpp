#ifndef PAIRTELEPORTS
#define PAIRTELEPORTS
#include "Teleport.hpp"
class PairTeleports{
private:
    Teleport tele1;
    Teleport tele2;
public:
    PairTeleports();
    void loadTextureFromFile(SDL_Renderer* gRenderer,std::string path);
    SDL_PairRect getPairRect();
    void setPosPair(int x1,int y1,int x2,int y2);
    void renderPairTele(SDL_Renderer* gRenderer);
};

#endif // PAIRTELEPORTS
