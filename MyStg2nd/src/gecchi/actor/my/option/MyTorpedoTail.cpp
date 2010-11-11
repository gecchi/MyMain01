
#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyTorpedoTail::MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pMyTorpedo) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001") {
    _class_name = "MyTorpedoTail";
    _pMyTorpedo = prm_pMyTorpedo;
}

void MyTorpedoTail::initialize() {
    setHitAble(false); //“–‚½‚è”»’è–³‚µ
    _SX = _SY = _SZ = 6*1000;
    setAlpha(0.3);
    _fBoundingSphereRadius = 5.0f;

}

void MyTorpedoTail::onActive() {
    HomingLaserChip::onActive();
}
void MyTorpedoTail::onInactive() {
    HomingLaserChip::onInactive();
}
void MyTorpedoTail::processBehaviorHeadChip() {

    setCoordinateBy(_pMyTorpedo);
    setRotationBy(_pMyTorpedo);
}

MyTorpedoTail::~MyTorpedoTail() {

}

