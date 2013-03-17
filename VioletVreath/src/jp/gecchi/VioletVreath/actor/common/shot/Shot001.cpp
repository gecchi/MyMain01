#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot001::Shot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot001)) {
    _class_name = "Shot001";
    _pSeTx->set(0, "WAVE_EXPLOSION_002");
    pSplLineCon_ = (SplineLineConnection*)(P_GOD->pSpl3DManager_->connect("SpConn_HAN")); //スプライン定義
    pSplSeq_ = NEW FixedVelocitySplineSequence(_pKurokoA, pSplLineCon_->fetch(), 10000); //移動速度固定
}

void Shot001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    _pScaler->setScale(2000);
    _pScaler->forceScaleRange(2000, 3000);
}

void Shot001::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setMvVelo(RR_Shot001_MvVelo(_RANK_));    //移動速度
    _pKurokoA->setFaceAngVelo(AXIS_X, RR_Shot001_AngVelo(_RANK_)); //きりもみ具合
    pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION);
    _pScaler->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //座標に反映
    pSplSeq_->behave(); //スプライン移動を振る舞い
    _pKurokoA->behave();
    _pScaler->behave();
}

void Shot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot001::onHit(GgafActor* prm_pOtherActor) {
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

    //_pSeTx->behave();
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    GGAF_DELETE(pSplSeq_);
    pSplLineCon_->close();
}
