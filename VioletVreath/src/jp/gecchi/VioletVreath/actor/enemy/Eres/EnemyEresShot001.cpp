#include "EnemyEresShot001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    ERESSHOT001_SE_EXPLOSION,
};

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

    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(ERESSHOT001_SE_EXPLOSION, "WAVE_EXPLOSION_002");
}

void EnemyEresShot001::initialize() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(veloTop_, veloBottom_);
    pKuroko->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
    setHitAble(true);
}

void EnemyEresShot001::onActive() {
    getStatus()->reset();

    //�o����
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(velo1st_);
    pKuroko->setMvAcce(iMoveAcce_1st_);

    setHitAble(true);
}

void EnemyEresShot001::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    //�����]���J�n
    if (getActiveFrame() == frame_TurnBegin_) {
        pKuroko->turnMvAngTwd(pMYSHIP,
                              angVelo_Turn_, 0,
                              TURN_CLOSE_TO, true);
        pKuroko->setMvAcce(iMoveAcce_2nd_);
    }

    //�����]���I��
    if (getActiveFrame() == frame_TurnBegin_ + frame_TurnInterval_) {
        pKuroko->setRzRyMvAngVelo(0,0);
        pKuroko->_is_targeting_ry_mv = false;
        pKuroko->_is_targeting_rz_mv = false;
    }

    //behaveUvFlip();
    //���W�ɔ��f
    pKuroko->behave();
    //getSeTransmitter()->behave();
}

void EnemyEresShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEresShot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(ERESSHOT001_SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyEresShot001::onInactive() {
    sayonara();
}

EnemyEresShot001::~EnemyEresShot001() {
}
