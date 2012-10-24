#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot001::Shot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot001)) {
    _class_name = "Shot001";
    _pSeTxer->set(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
    pSplLineCon_ = (SplineLineConnection*)(P_GOD->pSpl3DManager_->connect("SpConn_HAN")); //�X�v���C����`
    pSplSeq_ = NEW FixedVelocitySplineSequence(_pKurokoA, pSplLineCon_->fetch(), 10000); //�ړ����x�Œ�
}

void Shot001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    _pScaler->setScale(2000);
    _pScaler->forceScaleRange(2000, 3000);
}

void Shot001::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setMvVelo(RR_Shot001_MvVelo(_RANK_));    //�ړ����x
    _pKurokoA->setFaceAngVelo(AXIS_X, RR_Shot001_AngVelo(_RANK_)); //������݋
    pSplSeq_->exec(SplineSequence::RELATIVE_DIRECTION);
    _pScaler->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //���W�ɔ��f
    pSplSeq_->behave(); //�X�v���C���ړ���U�镑��
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
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        _pSeTxer->play3D(0);
        if (pExplo001) {
            pExplo001->locateWith(this);
        }

        sayonara();
    }

    //_pSeTxer->behave();
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    DELETE_IMPOSSIBLE_NULL(pSplSeq_);
    pSplLineCon_->close();
}
