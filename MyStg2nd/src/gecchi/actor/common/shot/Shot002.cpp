#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot002::Shot002(const char* prm_name) : DefaultMeshSetActor(prm_name, "Flora") {
    _class_name = "Shot002";
    MyStgUtil::resetShot002Status(_pStatus);
    _my_frame = 0;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
}

void Shot002::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    MyStgUtil::resetShot002Status(_pStatus);
    setHitAble(true);
    _pScaler->setScale(2000);
    _pMvNavigator->relateFaceAngWithMvAng(true);
    _pMvNavigator->setMvVelo(8000+_RANK_*8000);
    _pMvNavigator->setFaceAngVelo(AXIS_X, 1000+_RANK_*1000);
    _my_frame = 0;
}

void Shot002::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    if (_my_frame == 70) {
        _pMvNavigator->execTurnMvAngSequence(P_MYSHIP,
                                                   3000, 0,
                                                   TURN_CLOSE_TO);
    }

    if (_my_frame > 70 && _pMvNavigator->_mv_ang_ry_target_flg == false && _pMvNavigator->_mv_ang_rz_target_flg == false) {
        _pMvNavigator->execTurnMvAngSequence(
                    P_MYSHIP,
                    100, 0,
                    TURN_CLOSE_TO);
    }
    //座標に反映
    _pMvNavigator->behave();
    _pScaler->behave();
    _pSeTransmitter->behave();
    _my_frame++;
}

void Shot002::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot002::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}

Shot002::~Shot002() {

}
