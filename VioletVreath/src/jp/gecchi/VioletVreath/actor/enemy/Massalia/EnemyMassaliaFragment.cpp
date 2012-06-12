#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment::EnemyMassaliaFragment(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassaliaFragment)) {
    _pSeTx->useSe(1);
    _pSeTx->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyMassaliaFragment::onCreateModel() {
}

void EnemyMassaliaFragment::initialize() {
    setHitAble(true);
    setScaleR(0.3);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(50));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyMassaliaFragment::onActive() {
    //�X�e�[�^�X���Z�b�g
    MyStgUtil::resetEnemyMassaliaFragmentStatus(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaFragment::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaFragment::onHit(GgafActor* prm_pOtherActor) {
    effectFlush(2); //�t���b�V��
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTx->play3D(0);
        if (pExplo001) {
            pExplo001->locatedBy(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //���ł����ꍇ�A����t���[�����̈ȍ~�̏����Ńq�b�g�����Ȃ����߁i�d�v�j
        sayonara();
        //�f�Ђ̒f�Џo��
        DepositoryConnection* pCon = connectDepositoryManager("DpCon_MassaliaFragment2", this);
        GgafActorDepository* pDepo = pCon->fetch();
        for (int i =0; i < R_EnemyMassalia_ShotWay; i++) {
            EnemyMassaliaFragment2* p = (EnemyMassaliaFragment2*)(pDepo->dispatch());
            if (p) {
                p->locatedBy(this);
                p->_pKurokoA->takeoverMvFrom(this->_pKurokoA);
                p->_pKurokoA->setMvVelo(p->_pKurokoA->_veloMv/2); //�����̃X�s�[�h��
                p->_pKurokoA->addRyMvAng(RND(D_ANG(-45), D_ANG(+45)));
                p->_pKurokoA->addRzMvAng(RND(D_ANG(-45), D_ANG(+45)));
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
