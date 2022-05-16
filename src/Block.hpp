#ifndef BLOCKCLASS__
#define BLOCKCLASS__
#include "params.hpp"
#include "LTexture.hpp"
class Block: public LTexture {
  public:
    Block();
    Block(SDL_Renderer* gRenderer, std::string path);
  private:
};
#endif // BLOCKCLASS__
