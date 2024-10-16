#include "MyTorpedoTail.h"

#include "MyTorpedo.h"



using namespace GgafLib;
using namespace VioletVreath;

MyTorpedoTail::MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pTorpedo) :
        HomingLaserChip(prm_name, "StraeaLaserChip001") {
    _class_name = "MyTorpedoTail";
    pTorpedo_ = prm_pTorpedo;
}

void MyTorpedoTail::initialize() {
    setHitAble(false); //当たり判定無し
    setScaleR(5.0);
    setAlpha(0.3);
}

void MyTorpedoTail::onActive() {
    HomingLaserChip::onActive();
}

void MyTorpedoTail::onInactive() {
    HomingLaserChip::onInactive();
}

void MyTorpedoTail::processBehaviorHeadChip() {
    setPositionAt(pTorpedo_);
    setFaceAngAs(pTorpedo_);
}

void MyTorpedoTail::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

MyTorpedoTail::~MyTorpedoTail() {
}

