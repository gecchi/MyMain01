#include "stdafx.h"
#include "MyWave001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

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

    _pKuroko->setRzMvAngVelo(0);
    //_pKuroko->setFaceAngVelo(AXIS_Z, 2*1000);
    //_pKuroko->setRzMvAng(0);
    //setRzFaceAng(0);
    _pKuroko->setMvVelo(20000);

    _pColliChecker->makeCollision(7);
    _pColliChecker->setColliAAB(0,  -10000,  -10000,  -10000,   10000,   10000,   10000, true, true, true);
    _pColliChecker->setColliAAB(1,  -10000, -140000,  -10000,   10000, -120000,   10000, true, true, true);
    _pColliChecker->setColliAAB(2,  -10000,  120000,  -10000,   10000,  140000,   10000, true, true, true);
    _pColliChecker->setColliAAB(3, -140000,  -10000,  -10000, -120000,   10000,   10000, true, true, true);
    _pColliChecker->setColliAAB(4,  120000,  -10000,  -10000,  140000,   10000,   10000, true, true, true);
    _pColliChecker->setColliAAB(5,  -10000,  -10000, -140000,   10000,   10000, -120000, true, true, true);
    _pColliChecker->setColliAAB(6,  -10000,  -10000,  120000,   10000,   10000,  140000, true, true, true);


    //	_pColliChecker->pHitAreaBoxs_->setLine(0, -20000, 20000, 20000, 20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(1, 20000, 20000, 20000, -20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(2, 20000, -20000, -20000, -20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(3, -20000, -20000, -20000, 20000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(4, 30000, 30000, -30000, -30000, true);
    //	_pColliChecker->pHitAreaBoxs_->setLine(5, -30000, 30000, 30000, -30000, true);
    //
    pScaler_->forceRange(1000,20000);
    //setAlpha(0.2);

    setHitAble(true);

}

void MyWave001::processBehavior() {
    if (onChangeToActive()) {
        //出現時共通処理
        setScale(1000);
        pScaler_->transitionLinerStep(100000,100);
        pScaler_->behave();
        setHitAble(true);
        positionAs(P_MYSHIP);
        setRzFaceAng(P_MYSHIP->_rz);
        setRyFaceAng(P_MYSHIP->_ry);
        _pKuroko->setRzRyMvAng(P_MYSHIP->_rz,
                                P_MYSHIP->_ry);
        //		_x = P_MYSHIP->_x;
        //		_y = P_MYSHIP->_y;
        //		_z = P_MYSHIP->_z;
    } else {
        //通常処理
        //behaveUvFlip();
        //座標に反映
        pScaler_->behave();
        _pKuroko->behave();
    }
}

void MyWave001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }

}

/*
 bool MyWave001::processHitChkLogic(GgafDxGeometricActor* prm_pOtherActor) {
 return false;
 }
 */

void MyWave001::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("MyWave001::onHit ショットがヒットしました");
    //_TRACE_("MyWave001ヒットしました。("<<_x<<","<<_y<<")");
    sayonara();
}

void MyWave001::onInactive() {
}

MyWave001::~MyWave001() {
    GGAF_DELETE(pScaler_);
}
