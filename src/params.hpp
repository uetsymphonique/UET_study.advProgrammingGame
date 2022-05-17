#ifndef PARAMS__
#define PARAMS__
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <numeric>
#include <random>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <fstream>
using std::vector;
using namespace std;
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;
const int NUM_OF_LEVELS = 10;
const int TIME_BETWEEN_2LEVELS = 4000;
enum TYPE_CHOICE{
    INSTRUCTION,
    ENTERGAME,
    RANKING,
    NUM_OF_CHOICES_IN_MENU
};
enum TYPE_BLOCK {
    BLOCK1,
    BLOCK2,
    BLOCK3,
    BLOCK4,
    BLOCK1LONG,
    BLOCK2LONG,
    BLOCK3LONG,
    BLOCK4LONG,
    BLOCK1LONGR,
    BLOCK2LONGR,
    BLOCK3LONGR,
    BLOCK4LONGR,
    NUM_OF_TYPES_BLOCK
};
enum TYPE_ICE {
    ICEMINI,
    ICELONG,
    ICEBIG,
    NUM_OF_TYPES_ICE
};
enum TYPE_WIND{
    WIND200HIGH,WIND300HIGH,
    WIND200LOW,WIND300LOW,
    WIND200HIGHR,WIND300HIGHR,
    WIND200LOWR,WIND300LOWR,
    WIND200HIGH_VFLIP,WIND200HIGH_HFLIP,
    NUM_OF_TYPES_WIND
};
struct SDL_FloatRect {
    double x;
    double y;
    double w;
    double h;
    SDL_FloatRect(){};
    SDL_FloatRect(double _x, double _y, double _w, double _h) {
        x = _x;
        y = _y;
        h = _h;
        w = _w;
    }
    double getTop() {
        return y;
    }
    double getBottom() {
        return y + h;
    }
    double getLeft() {
        return x;
    }
    double getRight() {
        return x + w;
    }

};
bool checkCollision( SDL_FloatRect a, SDL_Rect b ) ;
bool checkCollisionCircleWithRect(SDL_Rect a_roto, SDL_Rect b_stato);
struct SDL_PairRect {
    SDL_Rect rect1;
    SDL_Rect rect2;
};
#endif // PARAMS__

