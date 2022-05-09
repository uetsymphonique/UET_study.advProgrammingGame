#ifndef HOLECLASS__
#define HOLECLASS__
#include "params.hpp"
#include "LTexture.hpp"
#include "Vec2d.hpp"
class Hole: public LTexture {
  private:
  public:
    Hole();
    Hole(int mW, int mH, SDL_Texture* mT);
};
#endif // HOLECLASS__
