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
    //コマ送り
    if (VB_UI->isPushedDown(VB_BUTTON7)) {
        pGAMESCENE->_is_frame_advance = true;
    }

    //一時停止してい状態
    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
    if (GgafDx9Input::isBeingPressedKey(DIK_V)) {
        //V＋方向で注視点操作
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
        //C＋方向でカメラ操作
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            pCAM->_Y += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            pCAM->_Y -= 8000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            pCAM->_X += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            pCAM->_X -= 8000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            pCAM->_Z += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            pCAM->_Z -= 8000;
        } else {
        }
    }

}
PauseCamWorker::~PauseCamWorker() {
}
