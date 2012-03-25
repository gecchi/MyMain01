#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCeresShot001::EnemyCeresShot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyCeresShot001)) {
    _class_name = "EnemyCeresShot001";
    inactivateTree();

    /** �o�����̏��� */
    iMvVelo_1st_ = 13000;
    /** �o�����̉����x�i���Œx���Ȃ�j */
    iMoveAcce_1st_ = -150;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    frame_TurnBegin_ = 60;
    /** �ړ����x��� */
    iMvVelo_Top_ = 30000;
    /** �Œ�ۏ؈ړ����x */
    iMvVelo_Bottom_ = 0;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    frame_TurnInterval_ = 400;
    /** �����]�����̊p���x�A���O���l(���̒l) */
    angVelo_Turn_ = 7000;
    /** �����]�����J�n�iframe_TurnBegin_�j����Đݒ肳�������x */
    iMoveAcce_2nd_ = 100;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "break_glass01", GgafRepeatSeq::nextVal("CH_break_glass01"));
}

void EnemyCeresShot001::initialize() {
    _pKurokoA->forceMvVeloRange(iMvVelo_Top_, iMvVelo_Bottom_);
    _pKurokoA->relateFaceAngWithMvAng(true);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyCeresShot001::onActive() {
    _pStatus->reset();

    //�o����
    _pKurokoA->setMvVelo(iMvVelo_1st_);
    _pKurokoA->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyCeresShot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�����]���J�n
    if (getActivePartFrame() == frame_TurnBegin_) {

        _pKurokoA->execTurnMvAngSequence(P_MYSHIP,
                                                   angVelo_Turn_, 0,
                                                   TURN_CLOSE_TO);
        _pKurokoA->setMvAcce(iMoveAcce_2nd_);
    }

    //�����]���I��
    if (getActivePartFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        _pKurokoA->setRzMvAngVelo(0);
        _pKurokoA->setRyMvAngVelo(0);
        _pKurokoA->_mv_ang_ry_target_flg = false;
        _pKurokoA->_mv_ang_rz_target_flg = false;
    }

    //behaveUvFlip();
    //���W�ɔ��f
    _pKurokoA->behave();
    //_pSeTransmitter->behave();
}

void EnemyCeresShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyCeresShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //�����ɏ��ŃG�t�F�N�g
        _pSeTransmitter->play3D(0);
        setHitAble(false);

        EffectExplosion001* pExplo001 =
                (EffectExplosion001*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }

        sayonara();
    }
}

void EnemyCeresShot001::onInactive() {
    sayonara();
}

EnemyCeresShot001::~EnemyCeresShot001() {
}