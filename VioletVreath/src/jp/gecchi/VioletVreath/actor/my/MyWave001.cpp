#include "MyWave001.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

MyWave001::MyWave001(const char* prm_name) :
        DefaultMeshActor(prm_name, "wave") {
    _class_name = "MyWave001";
}

void MyWave001::initialize() {
    //exec(FLIP_OSCILLATE_LOOP, 2);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRzMvAngVelo(0);
    //_pLocusVehicle->setFaceAngVelo(AXIS_Z, 2*1000);
    //_pLocusVehicle->setRzMvAng(0);
    //setRzFaceAng(0);
    pLocusVehicle->setMvVelo(20000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(7);
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
    getScaler()->setRange(1000,20000);
    //setAlpha(0.2);

    setHitAble(true);

}

void MyWave001::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::Scaler* const pScaler = getScaler();

    if (hasJustChangedToActive()) {
        //出現時共通処理
        setScale(1000);
        pScaler->transitionLinearStep(100000,100);
        pScaler->behave();
        setHitAble(true);
        setPositionAt(pMYSHIP);
        setRzFaceAng(pMYSHIP->_rz);
        setRyFaceAng(pMYSHIP->_ry);
        pLocusVehicle->setRzRyMvAng(pMYSHIP->_rz, pMYSHIP->_ry);
        //		_x = pMYSHIP->_x;
        //		_y = pMYSHIP->_y;
        //		_z = pMYSHIP->_z;
    } else {
        //通常処理
        //behaveUvFlip();
        //座標に反映
        pScaler->behave();
        pLocusVehicle->behave();
    }
}

void MyWave001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }

}


void MyWave001::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    //_TRACE_(FUNC_NAME<<" ショットがヒットしました");
    //_TRACE_("MyWave001ヒットしました。("<<_x<<","<<_y<<")");
    sayonara();
}

void MyWave001::onInactive() {
}

MyWave001::~MyWave001() {
}
