#include "stdafx.h"
#include "actor/MgrActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace Mogera;
using GgafLib::CollisionChecker3D;

MgrActor::MgrActor(const char* prm_name) :
        GgafLib::DefaultMeshActor(prm_name, "Guruguru") { //Guruguru.x が参照される。
}

void MgrActor::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(40));
    setHitAble(true);
    //座標設定
    position(0, 0, 0); //(0,0,0) は画面の中心
    //黒衣AにキャラのZ軸回転の角速度を設定(毎フレーム2度)
    _pKurokoA->setFaceAngVelo(AXIS_Z, D_ANG(2));
}

void MgrActor::processBehavior() {
    _pKurokoA->behave(); //黒衣Aを活動させる（Z軸回転する）
}

MgrActor::~MgrActor() {
}
