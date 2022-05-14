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
const int NUM_OF_LEVELS = 7;
const int TIME_BETWEEN_2LEVELS = 4000;
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

