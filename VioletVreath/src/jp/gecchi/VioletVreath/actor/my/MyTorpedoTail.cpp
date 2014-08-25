#include "MyTorpedoTail.h"

#include "MyTorpedo.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyTorpedoTail::MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pTorpedo) :
        HomingLaserChip(prm_name, "StraeaLaserChip001", nullptr) {
    _class_name = "MyTorpedoTail";
    pTorpedo_ = prm_pTorpedo;
}

void MyTorpedoTail::initialize() {
    setHitAble(false); //“–‚½‚è”»’è–³‚µ
    _sx = _sy = _sz = R_SC(6);
    setAlpha(0.3);
    _bounding_sphere_radius = 5.0f;
}

void MyTorpedoTail::onActive() {
    HomingLaserChip::onActive();
}

void MyTorpedoTail::onInactive() {
    HomingLaserChip::onInactive();
}

void MyTorpedoTail::processBehaviorHeadChip() {
    positionAs(pTorpedo_);
    setFaceAngAs(pTorpedo_);
}

MyTorpedoTail::~MyTorpedoTail() {
}

