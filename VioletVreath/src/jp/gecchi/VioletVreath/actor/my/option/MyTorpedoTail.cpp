
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyTorpedoTail::MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pMyTorpedo) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001", NULL) {
    _class_name = "MyTorpedoTail";
    pMyTorpedo_ = prm_pMyTorpedo;
}

void MyTorpedoTail::initialize() {
    setHitAble(false); //�����蔻�薳��
    _SX = _SY = _SZ = R2SC(6);
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

    locateAs(pMyTorpedo_);
    rotateWith(pMyTorpedo_);
}

MyTorpedoTail::~MyTorpedoTail() {

}
