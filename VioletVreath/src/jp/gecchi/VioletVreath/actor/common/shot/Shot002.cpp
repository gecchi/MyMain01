#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot002::Shot002(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot002)) {
    _class_name = "Shot002";
    my_frame_ = 0;
    _pSeTx->set(0, "WAVE_EXPLOSION_002");
}

void Shot002::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -50000, -50000, -50000, 50000, 50000, 50000);
}

void Shot002::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pScaler->setScale(2000);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setMvVelo(RR_Shot002_MvVelo(_RANK_));
    _pKurokoA->setFaceAngVelo(AXIS_X, RR_Shot002_AngVelo(_RANK_));
    my_frame_ = 0;
}

void Shot002::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    if (my_frame_ == 70) {
        _pKurokoA->execTurnMvAngSequence(P_MYSHIP,
                                           3000, 0,
                                           TURN_CLOSE_TO);
    }

    if (my_frame_ > 70 && _pKurokoA->_mv_ang_ry_target_flg == false && _pKurokoA->_mv_ang_rz_target_flg == false) {
        _pKurokoA->execTurnMvAngSequence(
                    P_MYSHIP,
                    100, 0,
                    TURN_CLOSE_TO);
    }
    //座標に反映
    _pKurokoA->behave();
    _pScaler->behave();
    _pSeTx->behave();
    my_frame_++;
}

void Shot002::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot002::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //・・・ココにヒットされたエフェクト
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊された場合
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTx->play3D(0);
        if (pExplo001) {
            pExplo001->locateWith(this);
        }
        sayonara();
    }
}

Shot002::~Shot002() {

}
