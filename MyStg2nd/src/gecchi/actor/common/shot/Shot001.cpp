#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Shot001::Shot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot001)) {
    _class_name = "Shot001";
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
    _pSplLineCon = (SplineLineConnection*)(P_GOD->_pSpl3DManager->connect("SpCon_HAN")); //�X�v���C����`
    _pSplSeq = NEW FixedVelocitySplineSequence(_pKurokoA, _pSplLineCon->use(), 10000); //�ړ����x�Œ�
}

void Shot001::initialize() {
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    _pScaler->setScale(2000);
    _pScaler->forceScaleRange(2000, 3000);
}

void Shot001::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setMvVelo(R_Shot001_MvVelo);    //�ړ����x
    _pKurokoA->setFaceAngVelo(AXIS_X, R_Shot001_AngVelo); //������݋
    _pSplSeq->exec(RELATIVE_DIRECTION);
    _pScaler->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //���W�ɔ��f
    _pSplSeq->behave(); //�X�v���C���ړ���U�镑��
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
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
        }

        sayonara();
    }

    //_pSeTransmitter->behave();
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    DELETE_IMPOSSIBLE_NULL(_pSplSeq);
    _pSplLineCon->close();
}
