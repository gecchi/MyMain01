#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


Planet001::Planet001(const char* prm_name) :
        DefaultMeshActor(prm_name, "Planet001", nullptr) {
    _class_name = "Planet001";
    setHitAble(false);
    setZEnable(true);        //Zバッファは考慮
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND-3);
    drawAnyFar(true);//遠くても表示

    //大気圏エフェクトスプライト
    pAtmosphere_ = NEW Planet001Atmosphere("P001ATMOS");
    addSubLast(pAtmosphere_);
}

void Planet001::onCreateModel() {
}

void Planet001::initialize() {
    //setAlpha(0.99);
    _X = (GgafDxUniverse::_X_gone_right*10);
    _pScaler->setScale(1000*1000);
    _pKurokoA->setFaceAng(AXIS_Z, D90ANG - D_ANG(30));
    _pKurokoA->setFaceAng(AXIS_Y, D45ANG);
    _pKurokoA->setFaceAngVelo(AXIS_X, 500); //自転の速さ

    pAtmosphere_->_pScaler->setScale(_pScaler->_scale[0]);
    pAtmosphere_->locateWith(this);
}
void Planet001::processBehavior() {
    //巨大オブジェクト移動テスト
//    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
//        _X += PX_C(100);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_U)) {
//        _X -= PX_C(100);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_8)) {
//        _Y += PX_C(100);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_J)) {
//        _Y -= PX_C(100);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_9)) {
//        _Z += PX_C(100);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_K)) {
//        _Z -= PX_C(100);
//    }
//
//    if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pScaler->addScale(10000);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_L)) {
//        _pScaler->addScale(-10000);
//    }
//
//    if (GgafDxInput::isPushedDownKey(DIK_O)) {
//        _TRACE_("Planet001  "<<_X<<","<<_Y<<","<<_Z);
//    }
    //_X = _X - PX_C(1);
    _pScaler->behave();
    _pKurokoA->behave();

    pAtmosphere_->_pScaler->setScale(_pScaler->_scale[0]);
    pAtmosphere_->locateWith(this);
}

Planet001::~Planet001() {
}

