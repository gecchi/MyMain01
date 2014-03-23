#include "stdafx.h"
#include "EffectLaserRefraction001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLaserRefraction001::EffectLaserRefraction001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "EffectLaserRefraction001", nullptr) {
    _class_name = "EffectLaserRefraction001";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void EffectLaserRefraction001::initialize() {
//    _pUvFlipper->setFlipPtnRange(0, 63);
    setHitAble(false);
}

void EffectLaserRefraction001::onActive() {
    //_pUvFlipper->setActivePtnToTop();
    //_pUvFlipper->exec(FLIP_ORDER_LOOP, 1); //パラパラアニメ無し
    setAlpha(0.5);
    setScale(R_SC(6));
    getKuroko()->setFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
}

void EffectLaserRefraction001::processBehavior() {
    addScale(100);

    //_pUvFlipper->behave();
    getKuroko()->behave();
    pScaler_->behave();
}

void EffectLaserRefraction001::processJudgement() {
//    if (_alpha < 0) {
//        sayonara();
//    }
}

void EffectLaserRefraction001::onInactive() {
}

EffectLaserRefraction001::~EffectLaserRefraction001() {
    GGAF_DELETE(pScaler_);
}
