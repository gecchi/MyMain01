#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot002::Shot002(const char* prm_name) : DefaultMeshSetActor(prm_name, "16/Flora") {
    _class_name = "Shot002";
    MyStgUtil::resetShot002Status(_pStatus);
    _my_frame = 0;
}

void Shot002::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -50000, -50000, -50000, 50000, 50000, 50000);
    useSe1("break_glass01");
}

void Shot002::onActive() {
    MyStgUtil::resetShot002Status(_pStatus);
    setHitAble(true);
    _pScaler->setScale(300);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setMvVelo(8000*_RANK_);
    _pMover->setFaceAngVelo(AXIS_X, 1000*_RANK_);
    _my_frame = 0;
}

void Shot002::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    if (_my_frame == 70) {
        _pMover->execTagettingMvAngSequence(pMYSHIP,
                                                   3000, 0,
                                                   TURN_CLOSE_TO);
    }

    if (_my_frame > 70 && _pMover->_mv_ang_ry_target_flg == false && _pMover->_mv_ang_rz_target_flg == false) {
        _pMover->execTagettingMvAngSequence(
                    GameGlobal::_pMyShip,
                    100, 0,
                    TURN_CLOSE_TO);
    }
    //座標に反映
    _pMover->behave();
    _pScaler->behave();
    _my_frame++;
}

void Shot002::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot002::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        playSe1();
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        inactivate();
    }
}

Shot002::~Shot002() {
}
