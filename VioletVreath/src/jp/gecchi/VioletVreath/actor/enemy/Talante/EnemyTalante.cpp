#include "EnemyTalante.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT    ,
    PROG_MOVE01_1,
    PROG_MOVE01_2,
    PROG_MOVE01_3,
    PROG_MOVE01_4,
    PROG_FINISH  ,
    PROG_BANPEI,
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
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    Z_ok_ = Y_ok_ = false;
}

void EnemyTalante::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyTalante::initialize() {
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setRollFaceAngVelo(5000);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
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
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    pVecDriver->setMvAcce(0);
    pVecDriver->setMvVelo(4000);
    pVecDriver->forceMvVeloRange(50000);
    getProgress()->reset(PROG_INIT);
}

void EnemyTalante::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }

        case PROG_MOVE01_1: {
            //������Ƃ��̂܂ܐ^�������i��
            if (pProg->hasJustChanged()) {
            }
            if (pProg->getFrame() > 60) {
                pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_2: {
            if (pProg->hasJustChanged()) {
            }
            if (Z_ok_ == false && pMyShip->_z - PX_C(5) <= _z && _z <= pMyShip->_z + PX_C(5)) {
                //Z���W������
                Z_ok_ = true;
                pVecDriver->addMvVelo(2000);
                if (pMyShip->_y <= _y) {
                    //�^���֐܂��
                    pVecDriver->turnRzRyMvAngTo(D270ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�^��֐܂��
                    pVecDriver->turnRzRyMvAngTo(D90ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_y - PX_C(5) <= _y && _y <= pMyShip->_y + PX_C(5)) {
                //Y���W������
                Y_ok_ = true;
                pVecDriver->addMvVelo(2000);
                if (pMyShip->_z <= _z) {
                    //���̎��@�̕����܂��
                    pVecDriver->turnRzRyMvAngTo(D0ANG, D90ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //��O�̎��@�̕����܂��
                    pVecDriver->turnRzRyMvAngTo(D0ANG, D270ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (pVecDriver->isTurningMvAng() == false) {
                if (Y_ok_ && Z_ok_) {
                    //Z���WY���W�������玟�̓�����
                    pProg->changeNext();
                } else if (pProg->getFrame() >= 480) {
                    //Z���WY���W���킸�Ƃ���莞�ԂŎ��̓�����
                    pProg->changeNext();
                }
            }
            break;
        }

        case PROG_MOVE01_3: {
            if (pProg->hasJustChanged()) {
                //X�������ɓ���
                if (pMyShip->_x <= _x) {
                    //���֐܂��
                    pVecDriver->turnRzRyMvAngTo(D180ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�E�֐܂��
                    pVecDriver->turnRzRyMvAngTo(D0ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (pVecDriver->isTurningMvAng() == false) {
                pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_4: {
            if (pProg->hasJustChanged()) {
                pVecDriver->setMvAcce(300);//�����J�n
            }
            break;
        }

    }
    pVecDriver->behave();

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


