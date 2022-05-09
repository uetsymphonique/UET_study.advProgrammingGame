#include "PairTeleports.hpp"
void PairTeleports::loadTextureFromFile(SDL_Renderer* gRenderer, std::string path) {
    tele1.loadFromFile(gRenderer, path);
    tele2.loadFromFile(gRenderer, path);
}
SDL_PairRect PairTeleports::getPairRect() {
    return{tele1.getRect(), tele2.getRect()};
}
void PairTeleports::setPosPair(int x1, int y1, int x2, int y2) {
    tele1.setPos(x1, y1);
    tele2.setPos(x2, y2);
}
void PairTeleports::renderPairTele(SDL_Renderer* gRenderer) {
    tele1.render(gRenderer);
    tele2.render(gRenderer);
}
