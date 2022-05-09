#include "Block.hpp"
Block::Block(): LTexture() {};
Block::Block(SDL_Renderer* gRenderer,std::string path){
    if(!loadFromFile(gRenderer,path)){
        std::cout<<"failed to load texture of block";
    }
}
