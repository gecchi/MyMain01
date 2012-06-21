#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment3::EnemyMassaliaFragment3(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassaliaFragment3)) {
    _pSeTx->useSe(1);
    _pSeTx->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyMassaliaFragment3::onCreateModel() {
}

void EnemyMassaliaFragment3::initialize() {
    setHitAble(true);
    setScaleR(0.04);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(20));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyMassaliaFragment3::onActive() {
    //�X�e�[�^�X���Z�b�g
    UTIL::resetEnemyMassaliaFragment3Status(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment3::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pKurokoA->behave();
}

void EnemyMassaliaFragment3::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyMassaliaFragment3::onHit(GgafActor* prm_pOtherActor) {
    effectFlush(2); //�t���b�V��
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTx->play3D(0);
        if (pExplo001) {
            pExplo001->locateWith(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //���ł����ꍇ�A����t���[�����̈ȍ~�̏����Ńq�b�g�����Ȃ����߁i�d�v�j
        sayonara();
        //�A�C�e���o��
        Item* pItem = employFromCommon(MagicPointItem001);
        if (pItem) {
            pItem->locateWith(this);
        }
    }
}


void EnemyMassaliaFragment3::onInactive() {
    sayonara();
}


EnemyMassaliaFragment3::~EnemyMassaliaFragment3() {
}
