#include "stdafx.h"
#include "MyTorpedoBlast.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyTorpedoBlast::MyTorpedoBlast(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "MyTorpedoBlast",STATUS(MyTorpedoBlast)) {
    _class_name = "MyTorpedoBlast";
    pScaler_ = NEW GgafDxScaler(this);
    effectBlendOne(); //加算合成するTechnique指定
    setAlpha(0.3);
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
}

void MyTorpedoBlast::initialize() {
    _pColliChecker->makeCollision(1);
    getKuroko()->setFaceAngVelo(D_ANG(0), D_ANG(6), D_ANG(0));
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    //MyTorpedoでreset()が実行される。
    //MyTorpedoBlastは、dispatchForceされるので、
    //onInactive() onActive()での実装を避ける
    _pStatus->reset();
    _pColliChecker->setColliSphere(0, PX_C(10));
    getKuroko()->setMvVelo(0);
    setScale(R_SC(1));
    pScaler_->forceRange(R_SC(1), R_SC(400));
    pScaler_->beat(120, 120/2, 0, 120/2, 1); //1回膨らんでしぼむ
}

void MyTorpedoBlast::processBehavior() {
    if (!pScaler_->isTransitioning()) {
        sayonara();//膨らんでしぼむが終了時
    } else {
        _pColliChecker->setColliSphere(0, _sx); //当たり判定も変化
        getKuroko()->behave();
        pScaler_->behave();
    }
}

void MyTorpedoBlast::processJudgement() {
}

void MyTorpedoBlast::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ヒットしても消滅しません
    int sta = UTIL::calcMyStamina(this, pOther);
}

MyTorpedoBlast::~MyTorpedoBlast() {
    GGAF_DELETE(pScaler_);
}
