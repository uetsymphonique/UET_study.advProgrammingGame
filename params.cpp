#include "params.hpp"
//int checkCollision( SDL_Rect a, SDL_Rect b ) {
//    //The sides of the rectangles
//    int leftA, leftB;
//    int rightA, rightB;
//    int topA, topB;
//    int bottomA, bottomB;
//
//    //Calculate the sides of rect A
//    leftA = a.x;
//    rightA = a.x + a.w;
//    topA = a.y;
//    bottomA = a.y + a.h;
//
//    //Calculate the sides of rect B
//    leftB = b.x;
//    rightB = b.x + b.w;
//    topB = b.y;
//    bottomB = b.y + b.h;
//
//    //If any of the sides from A are outside of B
//    if( bottomA <= topB ) {
//        return 0;
//    }
//
//    if( topA >= bottomB ) {
//        return 0;
//    }
//
//    if( rightA <= leftB ) {
//        return 0;
//    }
//
//    if( leftA >= rightB ) {
//        return 0;
//    }
//
//    //If none of the sides from A are outside B
//    int arr;
//    if(rightA>leftB||leftA<rightB){
//        arr = 2;
//    }
//    if(bottomA>topB||topA<bottomB){
//        arr = 1;
//    }
//    return arr;
//}
