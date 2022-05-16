#include "Swamp.hpp"
Swamp::Swamp(): LTexture() {};
void Swamp::rotateSwamp(){
    countRotate++;
    if(countRotate == 6){
        mAngle = int(mAngle+90)%360;
        countRotate = 0;
    }
}
