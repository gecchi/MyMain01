#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment::EnemyMassaliaFragment(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassaliaFragment)) {
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}

void EnemyMassaliaFragment::onCreateModel() {
}

void EnemyMassaliaFragment::initialize() {
    setHitAble(true);
    setScaleR(0.3);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(50));
    _pKurokoA->setFaceAngVelo(DEG2ANG(0), DEG2ANG(10), DEG2ANG(0));
}

void EnemyMassaliaFragment::onActive() {
    //ステータスリセット
    MyStgUtil::resetEnemyMassaliaFragmentStatus(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaFragment::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaFragment::onHit(GgafActor* prm_pOtherActor) {
    changeEffectTechniqueInterim("Flush", 2); //フラッシュ
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();
        //断片の断片出現
        DepositoryConnection* pCon = connectToDepositoryManager("DpCon_MassaliaFragment2", this);
        GgafActorDepository* pDepo = pCon->use();
        for (int i =0; i < R_EnemyMassalia_ShotWay; i++) {
            EnemyMassaliaFragment2* p = (EnemyMassaliaFragment2*)(pDepo->dispatch());
            if (p) {
                p->locateAs(this);
                p->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
                p->_pKurokoA->setMvVelo(p->_pKurokoA->_veloMv/2); //半分のスピードへ
                p->_pKurokoA->addRyMvAng(RND(DEG2ANG(-45), DEG2ANG(+45)));
                p->_pKurokoA->addRzMvAng(RND(DEG2ANG(-45), DEG2ANG(+45)));
            }
        }
        pCon->close();
    }
}


void EnemyMassaliaFragment::onInactive() {
    sayonara();
}


EnemyMassaliaFragment::~EnemyMassaliaFragment() {
}
