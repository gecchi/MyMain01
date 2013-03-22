#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCeresShot001::EnemyCeresShot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyCeresShot001)) {
    _class_name = "EnemyCeresShot001";
    inactivateTree();

    /** �o�����̏��� */
    velo1st_ = 13000;
    /** �o�����̉����x�i���Œx���Ȃ�j */
    iMoveAcce_1st_ = -150;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    frame_TurnBegin_ = 60;
    /** �ړ����x��� */
    veloTop_ = 30000;
    /** �Œ�ۏ؈ړ����x */
    veloBottom_ = 0;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    frame_TurnInterval_ = 400;
    /** �����]�����̊p���x�A���O���l(���̒l) */
    angVelo_Turn_ = 7000;
    /** �����]�����J�n�iframe_TurnBegin_�j����Đݒ肳�������x */
    iMoveAcce_2nd_ = 100;
    _pSeTx->set(CERESSHOT001_SE_EXPLOSION, "WAVE_EXPLOSION_002");
}

void EnemyCeresShot001::initialize() {
    _pKurokoA->forceMvVeloRange(veloTop_, veloBottom_);
    _pKurokoA->relateMvFaceAng(true);

    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyCeresShot001::onActive() {
    _pStatus->reset();

    //�o����
    _pKurokoA->setMvVelo(velo1st_);
    _pKurokoA->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyCeresShot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //�����]���J�n
    if (getActivePartFrame() == frame_TurnBegin_) {

        _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                angVelo_Turn_, 0,
                                TURN_CLOSE_TO,true);
        _pKurokoA->setMvAcce(iMoveAcce_2nd_);
    }

    //�����]���I��
    if (getActivePartFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        _pKurokoA->setRzRyMvAngVelo(0);
        _pKurokoA->_mv_ang_ry_target_flg = false;
        _pKurokoA->_mv_ang_rz_target_flg = false;
    }

    //behaveUvFlip();
    //���W�ɔ��f
    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemyCeresShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyCeresShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(CERESSHOT001_SE_EXPLOSION);

        sayonara();
    }
}

void EnemyCeresShot001::onInactive() {
    sayonara();
}

EnemyCeresShot001::~EnemyCeresShot001() {
}
