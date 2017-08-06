#include "MyWave001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyWave001::MyWave001(const char* prm_name) :
        DefaultMeshActor(prm_name, "wave", nullptr) {
    _class_name = "MyWave001";
    pScaler_ = NEW GgafDxScaler(this);
}

void MyWave001::initialize() {
    //exec(FLIP_OSCILLATE_LOOP, 2);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRzMvAngVelo(0);
    //_pKuroko->setFaceAngVelo(AXIS_Z, 2*1000);
    //_pKuroko->setRzMvAng(0);
    //setRzFaceAng(0);
    pKuroko->setMvVelo(20000);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(7);
    pChecker->setColliAABox(0,  -10000,  -10000,  -10000,   10000,   10000,   10000, true, true, true);
    pChecker->setColliAABox(1,  -10000, -140000,  -10000,   10000, -120000,   10000, true, true, true);
    pChecker->setColliAABox(2,  -10000,  120000,  -10000,   10000,  140000,   10000, true, true, true);
    pChecker->setColliAABox(3, -140000,  -10000,  -10000, -120000,   10000,   10000, true, true, true);
    pChecker->setColliAABox(4,  120000,  -10000,  -10000,  140000,   10000,   10000, true, true, true);
    pChecker->setColliAABox(5,  -10000,  -10000, -140000,   10000,   10000, -120000, true, true, true);
    pChecker->setColliAABox(6,  -10000,  -10000,  120000,   10000,   10000,  140000, true, true, true);


    //	pChecker->pHitAreaBoxs_->setLine(0, -20000, 20000, 20000, 20000, true);
    //	pChecker->pHitAreaBoxs_->setLine(1, 20000, 20000, 20000, -20000, true);
    //	pChecker->pHitAreaBoxs_->setLine(2, 20000, -20000, -20000, -20000, true);
    //	pChecker->pHitAreaBoxs_->setLine(3, -20000, -20000, -20000, 20000, true);
    //	pChecker->pHitAreaBoxs_->setLine(4, 30000, 30000, -30000, -30000, true);
    //	pChecker->pHitAreaBoxs_->setLine(5, -30000, 30000, 30000, -30000, true);
    //
    pScaler_->setRange(1000,20000);
    //setAlpha(0.2);

    setHitAble(true);

}

void MyWave001::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    if (hasJustChangedToActive()) {
        //出現時共通処理
        setScale(1000);
        pScaler_->transitionLinearStep(100000,100);
        pScaler_->behave();
        setHitAble(true);
        setPositionAt(P_MYSHIP);
        setRzFaceAng(P_MYSHIP->_rz);
        setRyFaceAng(P_MYSHIP->_ry);
        pKuroko->setRzRyMvAng(P_MYSHIP->_rz, P_MYSHIP->_ry);
        //		_x = P_MYSHIP->_x;
        //		_y = P_MYSHIP->_y;
        //		_z = P_MYSHIP->_z;
    } else {
        //通常処理
        //behaveUvFlip();
        //座標に反映
        pScaler_->behave();
        pKuroko->behave();
    }
}

void MyWave001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }

}

/*
 bool MyWave001::processHitChkLogic(GgafDxGeometricActor* prm_pOtherActor) {
 return false;
 }
 */

void MyWave001::onHit(const GgafActor* prm_pOtherActor) {
    //_TRACE_(FUNC_NAME<<" ショットがヒットしました");
    //_TRACE_("MyWave001ヒットしました。("<<_x<<","<<_y<<")");
    sayonara();
}

void MyWave001::onInactive() {
}

MyWave001::~MyWave001() {
    GGAF_DELETE(pScaler_);
}
