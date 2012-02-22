#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Planet001::Planet001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001", NULL) {
    _class_name = "Planet001";
    setHitAble(false);
    setZEnable(true);        //Zバッファは考慮
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND-2);
    setFarRate(0.999);
}
void Planet001::onCreateModel() {
}

void Planet001::initialize() {
    //setAlpha(0.99);
    _X = (GgafDxUniverse::_X_goneRight*1);
    _pScaler->setScale(1000*1000);
    //_pKurokoA->setFaceAng(AXIS_Z, DEG2ANG(-30));
    _pKurokoA->setFaceAngVelo(AXIS_Y, 10);
}
void Planet001::processBehavior() {
    //巨大オブジェクトテスト
    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
        _X += PX2CO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_U)) {
        _X -= PX2CO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_8)) {
        _Y += PX2CO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_J)) {
        _Y -= PX2CO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_9)) {
        _Z += PX2CO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_K)) {
        _Z -= PX2CO(100);
    }

    if (GgafDxInput::isBeingPressedKey(DIK_0)) {
        _pScaler->addScale(10000);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_L)) {
        _pScaler->addScale(-10000);
    }

    if (GgafDxInput::isPushedDownKey(DIK_O)) {
        _TRACE_("Planet001  "<<_X<<","<<_Y<<","<<_Z);
    }
    //_X = _X - PX2CO(1);
    _pScaler->behave();
    _pKurokoA->behave();
}

Planet001::~Planet001() {
}

