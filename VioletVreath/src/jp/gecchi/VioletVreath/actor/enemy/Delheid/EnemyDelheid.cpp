#include "EnemyDelheid.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/Checker.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT,
    PROG_CURVE_MOVING,
    PROG_AFTER_LEAD,
    PROG_AFTER_LEAD_MOVING,
    PROG_BANPEI,
};
enum {
    PROG2_WAIT,
    PROG2_OPEN,
    PROG2_SHOT,
    PROG2_CLOSE,
    PROG2_BANPEI,
};
enum {
    MPH_CLOSE,
    MPH_OPEN,
};
enum {
    SE_DAMAGED  ,
    SE_UNDAMAGED,
    SE_EXPLOSION,
};

EnemyDelheid::EnemyDelheid(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Delheid_1", StatusReset(EnemyDelheid)) {
    _class_name = "EnemyDelheid";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pProg2_ = createProgress();
    shot_begin_frame_ = 0;
    pDriverLeader_ = nullptr;
    pDepoShot_ = nullptr;
}

void EnemyDelheid::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDelheid::nextFrame() {
    DefaultMassMorphMeshActor::nextFrame();
    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
        pProg2_->update();
    }
}

void EnemyDelheid::config(GgafDx::CurveManufacture* prm_pCurveManufacture,
                          GgafCore::ActorDepository* prm_pDepoShot  ) {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
    pDriverLeader_ = createCurveDriverLeader(prm_pCurveManufacture);
    pDepoShot_ = prm_pDepoShot;
}

void EnemyDelheid::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    setScaleR(0.3);
}

void EnemyDelheid::onActive() {
    if (pDriverLeader_ == nullptr) {
        throwCriticalException("EnemyDelheid�̓X�v���C���K�{�ł�config���ĉ������Bthis="<<NODE_INFO);
    }
    getStatus()->reset();
    setHitAble(true);
    getMorpher()->reset();
    getProgress()->reset(PROG_INIT);
    pProg2_->reset(PROG2_WAIT);
}

void EnemyDelheid::processBehavior() {
    MyShip* pMyShip = pMYSHIP;

    //�ړ��̏�ԑJ��------------------------------
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pDriverLeader_->start(RELATIVE_COORD_DIRECTION, 3); //�ō��łR�񃋁[�v����\��
            getVecDriver()->setMvAcce(0);
            getVecDriver()->keepOnTurningFaceAngTwd(pMYSHIP,
                                                    D_ANG(1), 0, TURN_CLOSE_TO, false);
            pProg->changeNext();
            break;
        }
        case PROG_CURVE_MOVING: {
            if (pProg->hasJustChanged()) {
            }
            //processJudgement() �� pDriverLeader_->isFinished() �����҂�
            break;
        }

        //�S�[���̃A���T�i�����Ȃ��ꍇ�A���̌�̈ړ�
        case PROG_AFTER_LEAD: {
            //processJudgement() �� pDriverLeader_->isFinished() �����҂�
            break;
        }
        case PROG_AFTER_LEAD_MOVING: {
            //����2�񂾂������J�[�u�ړ����I�������̓���
            //isOutOfSpacetime() �����҂�
            break;
        }
    }

    //�V���b�g���˂̏�ԑJ��-----------------------------------
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            //open_shot() �҂��E�E�E
            break;
        }
        case PROG2_OPEN: {
            if (pProg2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 1.1, 0, 0.001);
            }
            if (!getMorpher()->isTransitioning()) {
                setMorphWeight(MPH_OPEN, 1.0);
                pProg2_->changeNext();
            }
            break;
        }

        case PROG2_SHOT: {
            if (pProg2_->hasJustChanged()) {
                shot_begin_frame_ = RND(120, 240);
            }
            if (pProg2_->hasArrivedAt(shot_begin_frame_)) {
                UTIL::shotWay002(
                       this,
                       pDepoShot_,
                       PX_C(20),     //r
                       5,            //way��
                       D_ANG(10),    //way��way�̊Ԋu
                       PX_C(5),      //�������x
                       100,          //�����x
                       2,            //way�̃Z�b�g��
                       0,            //�Z�b�g�ƃZ�b�g�̊Ԋu�t���[��
                       0.8f,         //�Z�b�g�����ɔ����������x������
                       nullptr
                     );
            }
            if (pProg2_->hasArrivedAt(240)) {
                pProg2_->changeNext();
            }
            break;
        }
        case PROG2_CLOSE: {
            if (pProg2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 0.0, 0, -0.01);
            }
            if (!getMorpher()->isTransitioning()) {
                pProg2_->changeNothing();
            }

            break;
        }
    }
    //-----------------------------------------------
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->_angvelo_face[AXIS_X] = pVecDriver->_velo_mv/2;
    pDriverLeader_->behave(); //�J�[�u�ړ�����悤��Driver�𑀍�
    pVecDriver->behave();
    getMorpher()->behave();
}

void EnemyDelheid::processSettlementBehavior() {
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_CURVE_MOVING: {
            if (pDriverLeader_->_cnt_loop >= 2) {
                if (((FormationDelheid*)getFormation())->pAlisana_goal) {
                    //�S�[�������݂���ꍇ�A�P���[�v�ł���Ȃ�B
                    pProg->changeNothing();
                    sayonara();
                } else {
                    pProg->change(PROG_AFTER_LEAD);
                }
            }
            break;
        }

        //�S�[���̃A���T�i�����Ȃ��ꍇ�A���̌�̈ړ�
        case PROG_AFTER_LEAD: {
            if (pDriverLeader_->isFinished()) {
                //�J�[�u�ړ����I������ꍇ
                pProg->change(PROG_AFTER_LEAD_MOVING);
            }
            break;
        }
    }
    DefaultMassMorphMeshActor::processSettlementBehavior();
}

void EnemyDelheid::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDelheid::onHit(const GgafCore::Actor* prm_pOtherActor) {
    if (getMorphWeight(MPH_OPEN) > 0.1) {
        bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //�j�󂳂ꂽ��(�X�^�~�i <= 0)
            getSeTransmitter()->play3D(SE_EXPLOSION);
            sayonara();
        } else {
            //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
            getSeTransmitter()->play3D(SE_DAMAGED);
        }
    } else {
        //�J���ĂȂ��̂œ�����Ȃ�
        getSeTransmitter()->play3D(SE_UNDAMAGED);
    }
}

void EnemyDelheid::onInactive() {
}

void EnemyDelheid::open_shot() {
    pProg2_->change(PROG2_OPEN);
}

EnemyDelheid::~EnemyDelheid() {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
    GGAF_DELETE(pProg2_);
}

