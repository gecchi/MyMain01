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
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_WORLDBOUND-3);
    viewAlsoForcesFar(true);//遠くても表示

    //大気圏エフェクトスプライト
    pAtmosphere_ = NEW Planet001Atmosphere("P001ATMOS");
    addSubLast(pAtmosphere_);
}

void Planet001::onCreateModel() {
}

void Planet001::initialize() {
    //setAlpha(0.99);
    _X = (GgafDxUniverse::_X_goneRight*10);
    _pScaler->setScale(1000*1000);
    _pKurokoA->setFaceAng(AXIS_Z, D90ANG - DANG(30));
    _pKurokoA->setFaceAng(AXIS_Y, D45ANG);
    _pKurokoA->setFaceAngVelo(AXIS_X, 20); //自転の速さ

    pAtmosphere_->_pScaler->setScale(_pScaler->_scale[0]);
    pAtmosphere_->locatedBy(this);
}
void Planet001::processBehavior() {
    //巨大オブジェクトテスト
    if (GgafDxInput::isBeingPressedKey(DIK_I)) {
        _X += PXCO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_U)) {
        _X -= PXCO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_8)) {
        _Y += PXCO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_J)) {
        _Y -= PXCO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_9)) {
        _Z += PXCO(100);
    }
    if (GgafDxInput::isBeingPressedKey(DIK_K)) {
        _Z -= PXCO(100);
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
    //_X = _X - PXCO(1);
    _pScaler->behave();
    _pKurokoA->behave();

    pAtmosphere_->_pScaler->setScale(_pScaler->_scale[0]);
    pAtmosphere_->locatedBy(this);
}

Planet001::~Planet001() {
}

