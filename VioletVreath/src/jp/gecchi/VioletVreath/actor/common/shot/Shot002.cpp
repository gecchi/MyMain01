#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot002::Shot002(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot002)) {
    _class_name = "Shot002";
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
}

void Shot002::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    if (getActivePartFrame() == 70) {
        _pKurokoA->execTurnMvAngSequenceTwd(P_MYSHIP,
                                            3000, 0,
                                            TURN_CLOSE_TO, true);
    }

    if (getActivePartFrame() > 70 && !_pKurokoA->isRunnigTurnMvAngSequence()) {
        _pKurokoA->execTurnMvAngSequenceTwd(P_MYSHIP,
                                            100, 0,
                                            TURN_CLOSE_TO, true);
    }
    //座標に反映
    _pKurokoA->behave();
    _pScaler->behave();
    _pSeTx->behave();
}

void Shot002::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot002::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false); //以降同一フレーム内でヒットさせない。
        UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現
        _pSeTx->play3D(0);
        if (pOther->getKind() & KIND_MY) { //自機側に撃たれて消滅の場合は
            UTIL::activateItemOf(this); //アイテム出現
        }
        sayonara();
    }
}

Shot002::~Shot002() {

}
