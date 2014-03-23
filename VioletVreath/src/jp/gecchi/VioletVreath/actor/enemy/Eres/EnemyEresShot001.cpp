#include "stdafx.h"
#include "EnemyEresShot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEresShot001::EnemyEresShot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyEresShot001)) {
    _class_name = "EnemyEresShot001";
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

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(ERESSHOT001_SE_EXPLOSION, "WAVE_EXPLOSION_002");
}

void EnemyEresShot001::initialize() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(veloTop_, veloBottom_);
    pKuroko->relateFaceWithMvAng(true);

    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
}

void EnemyEresShot001::onActive() {
    _pStatus->reset();

    //�o����
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(velo1st_);
    pKuroko->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyEresShot001::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    GgafDxKuroko* pKuroko = getKuroko();
    //�����]���J�n
    if (getActiveFrame() == frame_TurnBegin_) {
        pKuroko->turnMvAngTwd(P_MYSHIP,
                              angVelo_Turn_, 0,
                              TURN_CLOSE_TO, true);
        pKuroko->setMvAcce(iMoveAcce_2nd_);
    }

    //�����]���I��
    if (getActiveFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        pKuroko->setRzRyMvAngVelo(0,0);
        pKuroko->_mv_ang_ry_target_flg = false;
        pKuroko->_mv_ang_rz_target_flg = false;
    }

    //behaveUvFlip();
    //���W�ɔ��f
    pKuroko->behave();
    //getSeTx()->behave();
}

void EnemyEresShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEresShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�����Ƀq�b�g�G�t�F�N�g
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //��������
        UTIL::activateExplosionEffectOf(this);
        getSeTx()->play3D(ERESSHOT001_SE_EXPLOSION);

        sayonara();
    }
}

void EnemyEresShot001::onInactive() {
    sayonara();
}

EnemyEresShot001::~EnemyEresShot001() {
}
