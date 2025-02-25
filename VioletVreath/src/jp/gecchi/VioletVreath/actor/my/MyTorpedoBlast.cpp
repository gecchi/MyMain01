#include "MyTorpedoBlast.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

MyTorpedoBlast::MyTorpedoBlast(const char* prm_name) :
        VvMyActor<DefaultMeshSetActor>(prm_name, "MyTorpedoBlast", StatusReset(MyTorpedoBlast)) {
    _class_name = "MyTorpedoBlast";
    effectBlendOne(); //加算合成するTechnique指定
    setAlpha(0.3);
    useZBufferDrawing(true);        //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false);  //自身のZバッファを書き込みしない
}

void MyTorpedoBlast::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    getLocusVehicle()->setRollPitchYawFaceAngVelo(D_ANG(0), D_ANG(0), D_ANG(6));
    setHitAble(true);
}

void MyTorpedoBlast::onReset() {
    //MyTorpedoでreset()が実行される。
    //MyTorpedoBlastは、dispatchForceされるので、
    //onInactive() onActive()での実装を避ける
    getStatus()->reset();
    getWorldCollisionChecker()->setColliSphere(0, PX_C(10));
    getLocusVehicle()->setMvVelo(0);
    setScale(R_SC(1));
    GgafDx::Scaler* const pScaler = getScaler();
    pScaler->setRange(R_SC(1), R_SC(400));
    pScaler->beat(120, 120/2, 0, 120/2, 1); //1回膨らんでしぼむ
}

void MyTorpedoBlast::processBehavior() {
    GgafDx::Scaler* const pScaler = getScaler();
    if (!pScaler->isTransitioning()) {
        sayonara();//膨らんでしぼむが終了時
    } else {
        getWorldCollisionChecker()->setColliSphere(0, _sx); //当たり判定も変化
        getLocusVehicle()->behave();
        pScaler->behave();
    }
}

void MyTorpedoBlast::processJudgement() {
}

void MyTorpedoBlast::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)(prm_pOppHitChecker->_pActor);
    //ヒットしても消滅しません
    int sta = calcStamina(pOther);
}

MyTorpedoBlast::~MyTorpedoBlast() {
}
