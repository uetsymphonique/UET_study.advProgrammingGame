#include "Swamp.hpp"
Swamp::Swamp(): LTexture() {};
Swamp::rotateSwamp(){
    countRotate++;
    if(countRotate == 6){
        mAngle = int(mAngle+90)%360;
        countRotate = 0;
    }
}
