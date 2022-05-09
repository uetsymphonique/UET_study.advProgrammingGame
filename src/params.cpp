#include "params.hpp"
bool checkCollision( SDL_Rect a, SDL_Rect b ) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB ) {
        return 0;
    }

    if( topA >= bottomB ) {
        return 0;
    }

    if( rightA <= leftB ) {
        return 0;
    }

    if( leftA >= rightB ) {
        return 0;
    }

    //If none of the sides from A are outside B
    return 1;
}
bool checkCollisionCircleWithRect(SDL_Rect a_roto, SDL_Rect b_stato) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a_roto.x;
    rightA = a_roto.x + a_roto.w;
    topA = a_roto.y;
    bottomA = a_roto.y + a_roto.h;

    //Calculate the sides of rect B
    leftB = b_stato.x;
    rightB = b_stato.x + b_stato.w;
    topB = b_stato.y;
    bottomB = b_stato.y + b_stato.h;

    double centerAx = (rightA + leftA) / 2.0;
    double centerAy = (topA + bottomA) / 2.0;

    if( centerAy <= topB ) {
        return 0;
    }

    if( centerAy >= bottomB ) {
        return 0;
    }

    if( centerAx <= leftB ) {
        return 0;
    }

    if( centerAx >= rightB ) {
        return 0;
    }
    return 1;
}
