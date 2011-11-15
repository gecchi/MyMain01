#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


Planets001::Planets001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planets001", NULL) {
    _class_name = "Planets001";
    setHitAble(false);
    setZEnable(true);        //Zバッファは考慮
    setZWriteEnable(false);  //Zバッファは書き込み無し
}
void Planets001::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void Planets001::initialize() {
    setAlpha(0.99);
    _X = GgafDxUniverse::_X_goneRight * 10;
    _SX = _SY = _SZ = 100 * 10 * 1000;
    _pKurokoA->setFaceAng(AXIS_Z, DEG2ANG(-30));
    _pKurokoA->setFaceAngVelo(AXIS_Y, 100);
}
void Planets001::processBehavior() {
    //巨大オブジェクトテスト
    if (GgafDxInput::isBeingPressedKey(DIK_O)) {
        _X += PX2CO(300);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_Y)) {
        _X -= PX2CO(300);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_U)) {
        _pScaler->addScale(5000);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
        _pScaler->addScale(-5000);
    }
    _X = _X - PX2CO(50);
    _pScaler->behave();
    _pKurokoA->behave();
}

bool Planets001::isOutOfUniverse() {
    return false;
}

Planets001::~Planets001() {
}

