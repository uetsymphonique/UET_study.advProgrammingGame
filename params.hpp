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
using std::vector;
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;
const int NUM_OF_LEVELS = 8;
const int TIME_BETWEEN_2LEVELS = 6000;
bool checkCollision( SDL_Rect a, SDL_Rect b ) ;
bool checkCollisionCircleWithRect(SDL_Rect a_roto,SDL_Rect b_stato);
struct SDL_PairRect{
    SDL_Rect rect1;
    SDL_Rect rect2;
};
#endif // PARAMS__

