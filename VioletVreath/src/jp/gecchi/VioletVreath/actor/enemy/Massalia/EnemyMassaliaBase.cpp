#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaBase::EnemyMassaliaBase(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _pSeTx->useSe(2);
    _pSeTx->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTx->set(SE_EXPLOSION, "bomb1"        , GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}

void EnemyMassaliaBase::onCreateModel() {
}

void EnemyMassaliaBase::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaBase::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaBase::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊時
        setHitAble(false);
        //爆発エフェクト
        GgafDxDrawableActor* pExplo = UTIL::activateExplosionEffect(_pStatus);
        if (pExplo) {
            pExplo->locateWith(this);
            pExplo->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        _pSeTx->play3D(SE_EXPLOSION);
        sayonara();

        //下位クラスの個々の処理
        processStaminaEnd(pOther);
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTx->play3D(SE_DAMAGED);
    }

}

void EnemyMassaliaBase::appearFragment(const char* prm_dp_name) {
    //断片出現
    DepositoryConnection* pCon = connectDepositoryManager(prm_dp_name, this);
    GgafActorDepository* pDepo = pCon->fetch();
    for (int i =0; i < R_EnemyMassalia_ShotWay; i++) {
        EnemyMassaliaBase* pFragment = (EnemyMassaliaBase*)(pDepo->dispatch());
        if (pFragment) {
            pFragment->locateWith(this);
            pFragment->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
            pFragment->_pKurokoA->setMvVelo(pFragment->_pKurokoA->_veloMv/2); //半分のスピードへ
            pFragment->_pKurokoA->addRyMvAng(RND(D_ANG(-45), D_ANG(+45)));
            pFragment->_pKurokoA->addRzMvAng(RND(D_ANG(-45), D_ANG(+45)));
        }
    }
    pCon->close();
}
void EnemyMassaliaBase::onInactive() {
    sayonara();
}


EnemyMassaliaBase::~EnemyMassaliaBase() {
}
