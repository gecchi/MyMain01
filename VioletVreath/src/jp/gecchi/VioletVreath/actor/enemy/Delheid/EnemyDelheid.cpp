#include "EnemyDelheid.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT,
    PHASE_CURVE_MOVING,
    PHASE_AFTER_LEAD,
    PHASE_AFTER_LEAD_MOVING,
    PHASE_BANPEI,
};
enum {
    PHASE2_WAIT,
    PHASE2_OPEN,
    PHASE2_SHOT,
    PHASE2_CLOSE,
    PHASE2_BANPEI,
};
enum {
    MPH_CLOSE,
    MPH_OPEN,
};
enum {
    SE_UNDAMAGED,
};

EnemyDelheid::EnemyDelheid(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Delheid", StatusReset(EnemyDelheid)) {
    _class_name = "EnemyDelheid";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_UNDAMAGED, "SE_ENEMY_UNDAMAGED_001");
    pPhase2_ = createAnotherPhase();
    shot_begin_frame_ = 0;
    pVehicleLeader_ = nullptr;
    pDepoShot_ = nullptr;
}

void EnemyDelheid::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}
//��������_was_paused_flg�H�H�H

//void EnemyDelheid::nextFrame() {
//    DefaultMassMorphMeshActor::nextFrame();
//    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
//        pProg2_->update();
//    }
//}
void EnemyDelheid::processNextFrame() {
    DefaultMassMorphMeshActor::processNextFrame();

//    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
    if (_is_active_in_the_tree_flg) {
        pPhase2_->update();
    }
}

void EnemyDelheid::config(GgafDx::CurveManufacture* prm_pCurveManufacture,
                          GgafCore::ActorDepository* prm_pDepoShot  ) {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
    pVehicleLeader_ = createCurveVehicleLeader(prm_pCurveManufacture);
    pDepoShot_ = prm_pDepoShot;
}

void EnemyDelheid::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    setScaleR(0.3);
}

void EnemyDelheid::onActive() {
    if (pVehicleLeader_ == nullptr) {
        throwCriticalException("EnemyDelheid�̓X�v���C���K�{�ł�config���ĉ������Bthis="<<NODE_INFO);
    }
    getStatus()->reset();
    setHitAble(true);
    getMorpher()->reset();
    getPhase()->reset(PHASE_INIT);
    pPhase2_->reset(PHASE2_WAIT);
}

void EnemyDelheid::processBehavior() {
    MyShip* pMyShip = pMYSHIP;

    //�ړ��̃t�F�[�Y------------------------------
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, 3); //�ō��łR�񃋁[�v����\��
            getLocusVehicle()->setMvAcce(0);
            getLocusVehicle()->keepOnTurningFaceAngTwd(pMYSHIP,
                                                    D_ANG(1), 0, TURN_CLOSE_TO, false);
            pPhase->changeNext();
            break;
        }
        case PHASE_CURVE_MOVING: {
            if (pPhase->hasJustChanged()) {
            }
            //processJudgement() �� pVehicleLeader_->isFinished() �����҂�
            break;
        }

        //�S�[���̃A���T�i�����Ȃ��ꍇ�A���̌�̈ړ�
        case PHASE_AFTER_LEAD: {
            //processJudgement() �� pVehicleLeader_->isFinished() �����҂�
            break;
        }
        case PHASE_AFTER_LEAD_MOVING: {
            //����2�񂾂������J�[�u�ړ����I�������̓���
            //isOutOfSpacetime() �����҂�
            break;
        }
    }

    //�V���b�g���˂̃t�F�[�Y-----------------------------------
    switch (pPhase2_->getCurrent()) {
        case PHASE2_WAIT: {
            //open_shot() �҂��E�E�E
            break;
        }
        case PHASE2_OPEN: {
            if (pPhase2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 1.1, 0, 0.001);
            }
            if (!getMorpher()->isTransitioning()) {
                setMorphWeight(MPH_OPEN, 1.0);
                pPhase2_->changeNext();
            }
            break;
        }

        case PHASE2_SHOT: {
            if (pPhase2_->hasJustChanged()) {
                shot_begin_frame_ = RND(120, 240);
            }
            if (pPhase2_->hasArrivedFrameAt(shot_begin_frame_)) {
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
            if (pPhase2_->hasArrivedFrameAt(240)) {
                pPhase2_->changeNext();
            }
            break;
        }
        case PHASE2_CLOSE: {
            if (pPhase2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 0.0, 0, -0.01);
            }
            if (!getMorpher()->isTransitioning()) {
                pPhase2_->changeNothing();
            }

            break;
        }
    }
    //-----------------------------------------------
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->_angvelo_face[AXIS_X] = pLocusVehicle->_velo_mv/2;
    pVehicleLeader_->behave(); //�J�[�u�ړ�����悤��Driver�𑀍�
    pLocusVehicle->behave();
    getMorpher()->behave();
}

void EnemyDelheid::processSettlementBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_CURVE_MOVING: {
            if (pVehicleLeader_->_cnt_loop >= 2) {
                if (((FormationDelheid*)getFormation())->pAlisana_goal) {
                    //�S�[�������݂���ꍇ�A�P���[�v�ł���Ȃ�B
                    pPhase->changeNothing();
                    sayonara();
                } else {
                    pPhase->change(PHASE_AFTER_LEAD);
                }
            }
            break;
        }

        //�S�[���̃A���T�i�����Ȃ��ꍇ�A���̌�̈ړ�
        case PHASE_AFTER_LEAD: {
            if (pVehicleLeader_->isFinished()) {
                //�J�[�u�ړ����I������ꍇ
                pPhase->change(PHASE_AFTER_LEAD_MOVING);
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

void EnemyDelheid::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    if (getMorphWeight(MPH_OPEN) > 0.1) {
        bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
        if (is_stamina_zero) {
            //�j�󂳂ꂽ��(�X�^�~�i <= 0)
            sayonara();
        } else {
            //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        }
    } else {
        //�J���ĂȂ��̂œ�����Ȃ�
        getSeXmtr()->play3D(SE_UNDAMAGED);
    }
}

void EnemyDelheid::onInactive() {
}

void EnemyDelheid::open_shot() {
    pPhase2_->change(PHASE2_OPEN);
}

EnemyDelheid::~EnemyDelheid() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
    GGAF_DELETE(pPhase2_);
}

