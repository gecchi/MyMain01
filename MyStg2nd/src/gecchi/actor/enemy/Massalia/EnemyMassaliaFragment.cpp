#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

EnemyMassaliaFragment::EnemyMassaliaFragment(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "MassaliaFragment", STATUS(EnemyMassaliaFragment)) {
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
}

void EnemyMassaliaFragment::onCreateModel() {
}

void EnemyMassaliaFragment::initialize() {
    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, PX2CO(50));
    _pKurokoA->setFaceAngVelo(DEG2ANG(0), DEG2ANG(10), DEG2ANG(0));
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

        //�A�C�e���o��
        Item* pItem = (Item*)P_COMMON_SCENE->_pDP_MagicPointItem001->dispatch();
        if (pItem) {
            pItem->locateAs(this);
        }
    }
}


void EnemyMassaliaFragment::onInactive() {
    sayonara();
}


EnemyMassaliaFragment::~EnemyMassaliaFragment() {
}
