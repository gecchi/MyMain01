#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PauseCamWorker::PauseCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "PauseCamWorker";
}
void PauseCamWorker::initialize() {
}

void PauseCamWorker::processBehavior() {
    //ƒRƒ}‘—‚è
    if (VB_UI->isPushedDown(VB_BUTTON7)) {
        P_GAME_SCENE->_is_frame_advance = true;
    }

    //ˆêŽž’âŽ~‚µ‚Ä‚¢ó‘Ô
    GgafDx9CameraViewPoint* pVP = P_CAM->_pViewPoint;
    if (GgafDx9Input::isBeingPressedKey(DIK_V)) {
        //V{•ûŒü‚Å’Ž‹“_‘€ì
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            pVP->_Y += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            pVP->_Y -= 8000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            pVP->_X += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            pVP->_X -= 8000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            pVP->_Z += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            pVP->_Z -= 8000;
        } else {
        }
    } else if (GgafDx9Input::isBeingPressedKey(DIK_C)) {
        //C{•ûŒü‚ÅƒJƒƒ‰‘€ì
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            P_CAM->_Y += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            P_CAM->_Y -= 8000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            P_CAM->_X += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            P_CAM->_X -= 8000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            P_CAM->_Z += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            P_CAM->_Z -= 8000;
        } else {
        }
    }

}
PauseCamWorker::~PauseCamWorker() {
}
