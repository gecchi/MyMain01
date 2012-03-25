#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment3::EnemyMassaliaFragment3(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Massalia", STATUS(EnemyMassaliaFragment3)) {
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyMassaliaFragment3::onCreateModel() {
}

void EnemyMassaliaFragment3::initialize() {
    setHitAble(true);
    setScaleR(0.04);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(20));
    _pKurokoA->setFaceAngVelo(DEG2ANG(0), DEG2ANG(10), DEG2ANG(0));
}

void EnemyMassaliaFragment3::onActive() {
    //�X�e�[�^�X���Z�b�g
    MyStgUtil::resetEnemyMassaliaFragment3Status(_pStatus);
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
    changeEffectTechniqueInterim("Flush", 2); //�t���b�V��
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        setHitAble(false); //���ł����ꍇ�A����t���[�����̈ȍ~�̏����Ńq�b�g�����Ȃ����߁i�d�v�j
        sayonara();
        //�A�C�e���o��
        Item* pItem = (Item*)P_COMMON_SCENE->pDP_MagicPointItem001_->dispatch();
        if (pItem) {
            pItem->locateAs(this);
        }
    }
}


void EnemyMassaliaFragment3::onInactive() {
    sayonara();
}


EnemyMassaliaFragment3::~EnemyMassaliaFragment3() {
}