#include "EnemyOzartia.h"

#include "EnemyOzartiaShot01.h"
#include "EnemyOzartiaLaserChip01.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"

#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG1_INIT   ,
    PROG1_ENTRY  ,
    PROG1_STAY   ,
    PROG1_MV_POS0 ,
    PROG1_MV_POS1 ,
    PROG1_MV_POS2 ,
    PROG1_MV_POS3 ,
    PROG1_MV_POS4 ,
    PROG1_MV_POS5 ,
    PROG1_MOVE_START ,
    PROG1_MOVING ,
    PROG1_SP_MV01 ,
    PROG1_LEAVE ,
    PROG_BANPEI1_,
};
enum {
    PROG2_WAIT ,
    PROG2_SHOT01_01 ,
    PROG2_SHOT01_02 ,
    PROG2_SHOT02 ,
    PROG2_SHOT03 ,
    PROG2_SHOT04 ,
    PROG2_BANPEI,
};
enum {
    MPH_CLOSE  ,
    MPH_SHOT01 ,
    MPH_SHOT02 ,
    MPH_SHOT03 ,
    MPH_SHOT04 ,
};
enum {
    SE_ENTRY,
    SE_DAMAGED ,
    SE_UNDAMAGED,
    SE_EXPLOSION,
    SE_SHOT01 ,
    SE_SHOT02 ,
    SE_SHOT03 ,
    SE_SHOT04 ,
};


#define D_MOVE (PX_C(500))
#define ASOBI (RND(-30,30))
EnemyOzartia::EnemyOzartia(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Ozartia", StatusReset(EnemyOzartia)) {
    _class_name = "EnemyOzartia";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pProg2_ = createProgress();
    is_hit_ = false;
    pDepo_shot01_ = nullptr;
    pDepo_shot02_ = nullptr;
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyOzartia01_TTT");
    pVehicleLeader01_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
//    //�o���A�u���b�N
//    pDepo_shot01_ = NEW GgafCore::ActorDepository("Depo_OzartiaBlock");
//    for (int i = 0; i < 9; i++) {
//        std::string name = "EnemyOzartiaShot01["+XTOS(i)+"]";
//        pDepo_shot01_->put(NEW EnemyOzartiaShot01(name.c_str()));
//        Sleep(1);
//    }
//    appendGroupChild(pDepo_shot01_);
//
//    pDepo_shot02_ = NEW LaserChipDepository("MyRotLaser");
//    pDepo_shot02_->config(60, 1, nullptr); //Halia�͒e�؂�t���[����1�ɂ��Ȃ��ƃp�N�p�N�����Ⴂ�܂��B
//    EnemyOzartiaLaserChip01* pChip;
//    for (int i = 0; i < 65; i++) { //���[�U�[�X�g�b�N
//        std::string name = "EnemyOzartiaLaserChip01["+XTOS(i)+"]";
//        pChip = NEW EnemyOzartiaLaserChip01(name.c_str());
//        pChip->setSource(this); //�ʒu��������
//        pDepo_shot02_->put(pChip);
//    }
//    appendGroupChild(pDepo_shot02_);
    faceto_ship_ = false;
    effectBlendOne(); //���Z����
}

void EnemyOzartia::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyOzartia::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->forceMvVeloRange(PX_C(1), PX_C(30));
    pVecVehicle->linkFaceAngByMvAng(false); //�Ɨ�
    setHitAble(false);
}

void EnemyOzartia::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG1_INIT);
    pProg2_->reset(PROG2_WAIT);
    faceto_ship_ = false;
}

void EnemyOzartia::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    //�{�̈ړ��n�̏��� �������� --->
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG1_INIT: {
            setHitAble(false);
            setAlpha(0);
            pVecVehicle->setMvAngTwd(pMyShip);
            pProg->changeNext();
            break;
        }
        case PROG1_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                 getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->change(PROG1_STAY);
            }
            break;
        }
        case PROG1_STAY: {
            if (pProg->hasJustChanged()) {
                faceto_ship_ = true;
                pVecVehicle->setMvAcce(0);
                pVecVehicle->turnMvAngTwd(pMyShip, D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (is_hit_ || pProg->hasArrivedAt(4*60)) {
                //�q�b�g���邩�A���΂炭�{�[���Ƃ��Ă�ƈړ��J�n
                pProg->changeProbab(18, PROG1_MV_POS0,
                                    16, PROG1_MV_POS1,
                                    16, PROG1_MV_POS2,
                                    16, PROG1_MV_POS3,
                                    16, PROG1_MV_POS4,
                                    18, PROG1_MV_POS5 );
            }
            break;
        }
        //////////// �ʏ�ړ��挈�� ////////////
        case PROG1_MV_POS0: {
            //���@�̐��ʕt�߂�
            posMvTarget_.set(pMyShip->_x + D_MOVE + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z          + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS1: {
            //���@�̏�
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y + D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS2: {
            //���@�̉E
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z - D_MOVE + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS3: {
            //���@�̉�
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y - D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS4: {
            //���@�̍�
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z + D_MOVE + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS5: {
            //���@�̌��
            posMvTarget_.set(pMyShip->_x - D_MOVE + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z          + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        //////////// �ʏ�ړ��J�n ////////////
        case PROG1_MOVE_START: {
            if (pProg->hasJustChanged()) {
                //�^�[��
                faceto_ship_ = false;
                pVecVehicle->setMvVeloBottom();
                pVecVehicle->setMvAcce(10); //�����ɉ���
                pVecVehicle->turnMvAngTwd(&posMvTarget_, D_ANG(2), 0, TURN_CLOSE_TO, false);
            }
            if (!pVecVehicle->isTurningMvAng()) {
                //�^�[��������ړ���
                pProg->change(PROG1_MOVING);
            }
            break;
        }
        case PROG1_MOVING: {
            if (pProg->hasJustChanged()) {
                //���@�̐��ʕt�߂փX�C�[���ƍs���܂�
                pVecVehicle->asstMv()->slideByVd(pVecVehicle->getMvVeloTop(), UTIL::getDistance(this, &posMvTarget_),
                                       0.3, 0.7, pVecVehicle->getMvVeloBottom(), true);
            }
            if (!pVecVehicle->asstMv()->isSliding()) {
                //����������I��
                pProg->change(PROG1_STAY);
            }
            break;
        }
        //////////// ����ړ��J�n ////////////
        case PROG1_SP_MV01: {
            if (pProg->hasJustChanged()) {
                pVecVehicle->setMvAngTwd(pMyShip);
                pVehicleLeader01_->start(RELATIVE_COORD_DIRECTION, 10); //10��
            }
            if (pVehicleLeader01_->isFinished()) {
                pProg->change(PROG1_STAY);
            }
            break;
        }
        //////////// ���Ԑ؂�ޏo ////////////
        case PROG1_LEAVE: {
            if (pProg->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
                sayonara();
                pProg->changeNothing(); //�����܂��I
            }
            break;
        }
        default :
            break;
    }
    //<-- �{�̈ړ��n�̏��� �����܂�

    //////////////////////////////////////////////////////////////////////

    //�V���b�g���ˌn���� �������� --->
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            if (pProg2_->hasJustChanged()) {
            }
            break;
        }
        case PROG2_SHOT01_01: {
            if (pProg2_->hasJustChanged()) {
                faceto_ship_ = true;
                getMorpher()->transitionLinearUntil(MPH_SHOT01, 1.0, 120);
            }
            if (pProg2_->hasArrivedAt(120)) {
                pProg2_->change(PROG2_SHOT01_02);
            }
            break;
        }
        default :
            break;
    }
    pProg2_->update();
    //<-- �V���b�g���ˌn���� �����܂�

    if (faceto_ship_) {
        //���@�������[�h
        if (!pVecVehicle->isTurningFaceAng()) {
            pVecVehicle->turnFaceAngTwd(pMyShip, D_ANG(5), 0, TURN_CLOSE_TO, false);
        }
    } else {
        //�i�s�����������[�h
        if (!pVecVehicle->isTurningFaceAng()) {
            pVecVehicle->turnRzRyFaceAngTo(pVecVehicle->_rz_mv,pVecVehicle->_ry_mv,
                                          D_ANG(2), 0, TURN_CLOSE_TO, false);
        }
    }

    pAlphaFader->behave();
    pVehicleLeader01_->behave();
    pVecVehicle->behave();
    is_hit_ = false;
}

void EnemyOzartia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOzartia::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
    is_hit_ = true;
}

void EnemyOzartia::onInactive() {
    sayonara();
}

EnemyOzartia::~EnemyOzartia() {
    GGAF_DELETE(pVehicleLeader01_);
    pConn_pCurveManuf_->close();
    GGAF_DELETE(pProg2_);
}

