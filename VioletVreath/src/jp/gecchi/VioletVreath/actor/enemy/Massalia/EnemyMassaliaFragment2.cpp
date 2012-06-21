#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment2::EnemyMassaliaFragment2(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassaliaFragment2)) {
    _pSeTx->useSe(1);
    _pSeTx->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}

void EnemyMassaliaFragment2::onCreateModel() {
}

void EnemyMassaliaFragment2::initialize() {
    setHitAble(true);
    setScaleR(0.1);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(30));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyMassaliaFragment2::onActive() {
    //ステータスリセット
    UTIL::resetEnemyMassaliaFragment2Status(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment2::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaFragment2::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaFragment2::onHit(GgafActor* prm_pOtherActor) {
    effectFlush(2); //フラッシュ
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTx->play3D(0);
        if (pExplo001) {
            pExplo001->locateWith(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();
        //断片の断片の断片出現
        DepositoryConnection* pCon = connectDepositoryManager("DpCon_MassaliaFragment3", this);
        GgafActorDepository* pDepo = pCon->fetch();
        for (int i = 0; i < R_EnemyMassalia_ShotWay; i++) {
            EnemyMassaliaFragment3* p = (EnemyMassaliaFragment3*)(pDepo->dispatch());
            if (p) {
                p->locateWith(this);
                p->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
                p->_pKurokoA->setMvVelo(p->_pKurokoA->_veloMv/2); //半分のスピードへ
                p->_pKurokoA->addRyMvAng(RND(D_ANG(-45), D_ANG(+45)));
                p->_pKurokoA->addRzMvAng(RND(D_ANG(-45), D_ANG(+45)));
            }
        }
        pCon->close();
    }
}


void EnemyMassaliaFragment2::onInactive() {
    sayonara();
}


EnemyMassaliaFragment2::~EnemyMassaliaFragment2() {
}
