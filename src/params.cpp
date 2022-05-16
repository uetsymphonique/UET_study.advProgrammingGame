#include "params.hpp"
bool checkCollision( SDL_FloatRect a, SDL_Rect b ) {
    double topB, bottomB, leftB,rightB;
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( a.getBottom() <= topB ) {
        return 0;
    }

    if( a.getTop() >= bottomB) {
        return 0;
    }

    if( a.getRight() <= leftB ) {
        return 0;
    }

    if( a.getLeft() >= rightB ) {
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
