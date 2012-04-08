#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassalia::EnemyMassalia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassalia)) {
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}

void EnemyMassalia::onCreateModel() {
}

void EnemyMassalia::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(100));
    _pKurokoA->setFaceAngVelo(D_ANG(1), D_ANG(2), D_ANG(3));
    setScaleR(0.5);
}

void EnemyMassalia::onActive() {
    //ステータスリセット
    MyStgUtil::resetEnemyMassaliaStatus(_pStatus);
    setHitAble(true);
    static DWORD appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static DWORD appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    _pKurokoA->setMvAng(0, D180ANG);
    _pKurokoA->addRyMvAng(RND(D_ANG(-5), D_ANG(+5)));
    _pKurokoA->addRzMvAng(RND(D_ANG(-5), D_ANG(+5)));
}

void EnemyMassalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassalia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    changeEffectTechniqueInterim("Flush", 2); //フラッシュ
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locatedBy(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();
        //断片出現
        DepositoryConnection* pCon = connectDepositoryManager("DpCon_MassaliaFragment", this);
        GgafActorDepository* pDepo = pCon->fetch();
        for (int i =0; i < R_EnemyMassalia_ShotWay; i++) {
            EnemyMassaliaFragment* p = (EnemyMassaliaFragment*)(pDepo->dispatch());
            if (p) {
                p->locatedBy(this);
                p->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
                p->_pKurokoA->setMvVelo(p->_pKurokoA->_veloMv/2); //半分のスピードへ
                p->_pKurokoA->addRyMvAng(RND(D_ANG(-45), D_ANG(+45)));
                p->_pKurokoA->addRzMvAng(RND(D_ANG(-45), D_ANG(+45)));
            }
        }
        pCon->close();
    }
}


void EnemyMassalia::onInactive() {
    sayonara();
}


EnemyMassalia::~EnemyMassalia() {
}
