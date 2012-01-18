#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EnemyMassaliaFragment2::EnemyMassaliaFragment2(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassaliaFragment2)) {
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyMassaliaFragment2::onCreateModel() {
}

void EnemyMassaliaFragment2::initialize() {
    setHitAble(true);
    setScaleR(0.1);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(30));
    _pKurokoA->setFaceAngVelo(DEG2ANG(0), DEG2ANG(10), DEG2ANG(0));
}

void EnemyMassaliaFragment2::onActive() {
    //�X�e�[�^�X���Z�b�g
    MyStgUtil::resetEnemyMassaliaFragment2Status(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment2::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaFragment2::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaFragment2::onHit(GgafActor* prm_pOtherActor) {
    changeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //���ł����ꍇ�A����t���[�����̈ȍ~�̏����Ńq�b�g�����Ȃ����߁i�d�v�j
        sayonara();
        //�f�Ђ̒f�Ђ̒f�Џo��
        DepositoryConnection* pCon = connectToDepositoryManager("DpCon_MassaliaFragment3", this);
        GgafActorDepository* pDepo = pCon->use();
        for (int i = 0; i < R_EnemyMassalia_ShotWay; i++) {
            EnemyMassaliaFragment3* p = (EnemyMassaliaFragment3*)(pDepo->dispatch());
            if (p) {
                p->locateAs(this);
                p->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
                p->_pKurokoA->setMvVelo(p->_pKurokoA->_veloMv/2); //�����̃X�s�[�h��
                p->_pKurokoA->addRyMvAng(RND(DEG2ANG(-45), DEG2ANG(+45)));
                p->_pKurokoA->addRzMvAng(RND(DEG2ANG(-45), DEG2ANG(+45)));
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
