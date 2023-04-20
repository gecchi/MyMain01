#include "EnemyTalante.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT    ,
    PHASE_MOVE01_1,
    PHASE_MOVE01_2,
    PHASE_MOVE01_3,
    PHASE_MOVE01_4,
    PHASE_FINISH  ,
    PHASE_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
};

EnemyTalante::EnemyTalante(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Talante", StatusReset(EnemyErmione)) {
    _class_name = "EnemyTalante";
    pDepo_shot_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");     //����
    Z_ok_ = Y_ok_ = false;
}

void EnemyTalante::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyTalante::initialize() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->linkFaceAngByMvAng(true);
    pLocoVehicle->setRollFaceAngVelo(5000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyTalante::config(
        GgafCore::ActorDepository* prm_pDepo_shot
        ) {
    pDepo_shot_ = prm_pDepo_shot;
}

void EnemyTalante::onActive() {
    getStatus()->reset();
    setHitAble(true);
    Z_ok_ = Y_ok_ = false;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setMvAcce(0);
    pLocoVehicle->setMvVelo(4000);
    pLocoVehicle->forceMvVeloRange(50000);
    getPhase()->reset(PHASE_INIT);
}

void EnemyTalante::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }

        case PHASE_MOVE01_1: {
            //������Ƃ��̂܂ܐ^�������i��
            if (pPhase->hasJustChanged()) {
            }
            if (pPhase->getFrame() > 60) {
                pPhase->changeNext(); //���̓�����
            }
            break;
        }

        case PHASE_MOVE01_2: {
            if (pPhase->hasJustChanged()) {
            }
            if (Z_ok_ == false && pMyShip->_z - PX_C(5) <= _z && _z <= pMyShip->_z + PX_C(5)) {
                //Z���W������
                Z_ok_ = true;
                pLocoVehicle->addMvVelo(2000);
                if (pMyShip->_y <= _y) {
                    //�^���֐܂��
                    pLocoVehicle->turnRzRyMvAngTo(D270ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�^��֐܂��
                    pLocoVehicle->turnRzRyMvAngTo(D90ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_y - PX_C(5) <= _y && _y <= pMyShip->_y + PX_C(5)) {
                //Y���W������
                Y_ok_ = true;
                pLocoVehicle->addMvVelo(2000);
                if (pMyShip->_z <= _z) {
                    //���̎��@�̕����܂��
                    pLocoVehicle->turnRzRyMvAngTo(D0ANG, D90ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //��O�̎��@�̕����܂��
                    pLocoVehicle->turnRzRyMvAngTo(D0ANG, D270ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (pLocoVehicle->isTurningMvAng() == false) {
                if (Y_ok_ && Z_ok_) {
                    //Z���WY���W�������玟�̓�����
                    pPhase->changeNext();
                } else if (pPhase->getFrame() >= 480) {
                    //Z���WY���W���킸�Ƃ���莞�ԂŎ��̓�����
                    pPhase->changeNext();
                }
            }
            break;
        }

        case PHASE_MOVE01_3: {
            if (pPhase->hasJustChanged()) {
                //X�������ɓ���
                if (pMyShip->_x <= _x) {
                    //���֐܂��
                    pLocoVehicle->turnRzRyMvAngTo(D180ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�E�֐܂��
                    pLocoVehicle->turnRzRyMvAngTo(D0ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (pLocoVehicle->isTurningMvAng() == false) {
                pPhase->changeNext(); //���̓�����
            }
            break;
        }

        case PHASE_MOVE01_4: {
            if (pPhase->hasJustChanged()) {
                pLocoVehicle->setMvAcce(300);//�����J�n
            }
            break;
        }

    }
    pLocoVehicle->behave();

    //getSeTransmitter()->behave();
}

void EnemyTalante::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyTalante::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    if (getActiveFrame() < 30 && (pOther->lookUpKind() & KIND_CHIKEI)) {
         //�o��30�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
         return;
    }

    bool was_destroyed = UTIL::performEnemyHit(this, pOther);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyTalante::onInactive() {
}

EnemyTalante::~EnemyTalante() {
}


