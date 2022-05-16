#ifndef PAIRTELEPORTS
#define PAIRTELEPORTS
#include "Vec2d.hpp"
class PairTeleports {
  private:
    Vec2d posTele1;
    Vec2d posTele2;
    int typeTele;
  public:
    const int TELE_WIDTH = 18;
    const int TELE_HEIGHT = 18;
    PairTeleports(double x1 = 0.0, double y1 = 0.0, double x2 = 0.0, double y2=0.0,int typeTele = 0);
};

#endif // PAIRTELEPORTS
