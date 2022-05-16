#ifndef SWAMPCLASS__
#define SWAMPCLASS__
#include "LTexture.hpp"
class Swamp: public LTexture {
  public:
    Swamp();
    void rotateSwamp();
  private:
    int countRotate = 0;
};
#endif // SWAMPCLASS__
