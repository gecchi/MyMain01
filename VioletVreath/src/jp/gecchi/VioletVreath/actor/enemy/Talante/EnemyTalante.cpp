#include "stdafx.h"
#include "EnemyTalante.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTalante::EnemyTalante(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Talante", STATUS(EnemyTalante)) {
    _class_name = "EnemyTalante";
    pDepo_Shot_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
    Z_ok_ = Y_ok_ = false;
    useProgress(PROG_BANPEI);
}

void EnemyTalante::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyTalante::initialize() {
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->relateFaceWithMvAng(true);
    pKuroko->setFaceAngVelo(AXIS_X, 5000);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyTalante::config(
        GgafCore::GgafActorDepository* prm_pDepo_Shot
        ) {
    pDepo_Shot_ = prm_pDepo_Shot;
}

void EnemyTalante::onActive() {
    getStatus()->reset();
    setHitAble(true);
    Z_ok_ = Y_ok_ = false;
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvAcce(0);
    pKuroko->setMvVelo(4000);
    pKuroko->forceMvVeloRange(50000);
    getProgress()->reset(PROG_INIT);
}

void EnemyTalante::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }

        case PROG_MOVE01_1: {
            //������Ƃ��̂܂ܐ^�������i��
            if (pProg->isJustChanged()) {
            }
            if (pProg->getFrameInProgress() > 60) {
                pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_2: {
            if (pProg->isJustChanged()) {
            }
            if (Z_ok_ == false && pMyShip->_z - PX_C(5) <= _z && _z <= pMyShip->_z + PX_C(5)) {
                //Z���W������
                Z_ok_ = true;
                pKuroko->addMvVelo(2000);
                if (pMyShip->_y <= _y) {
                    //�^���֐܂��
                    pKuroko->turnRzRyMvAngTo(D270ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�^��֐܂��
                    pKuroko->turnRzRyMvAngTo(D90ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (Y_ok_ == false && pMyShip->_y - PX_C(5) <= _y && _y <= pMyShip->_y + PX_C(5)) {
                //Y���W������
                Y_ok_ = true;
                pKuroko->addMvVelo(2000);
                if (pMyShip->_z <= _z) {
                    //���̎��@�̕����܂��
                    pKuroko->turnRzRyMvAngTo(D0ANG, D90ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //��O�̎��@�̕����܂��
                    pKuroko->turnRzRyMvAngTo(D0ANG, D270ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }

            if (pKuroko->isTurningMvAng() == false) {
                if (Y_ok_ && Z_ok_) {
                    //Z���WY���W�������玟�̓�����
                    pProg->changeNext();
                } else if (pProg->getFrameInProgress() >= 480) {
                    //Z���WY���W���킸�Ƃ���莞�ԂŎ��̓�����
                    pProg->changeNext();
                }
            }
            break;
        }

        case PROG_MOVE01_3: {
            if (pProg->isJustChanged()) {
                //X�������ɓ���
                if (pMyShip->_x <= _x) {
                    //���֐܂��
                    pKuroko->turnRzRyMvAngTo(D180ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                } else {
                    //�E�֐܂��
                    pKuroko->turnRzRyMvAngTo(D0ANG, D0ANG,
                                               D_ANG(8), 0, TURN_ANTICLOSE_TO, false);
                }
            }
            if (pKuroko->isTurningMvAng() == false) {
                pProg->changeNext(); //���̓�����
            }
            break;
        }

        case PROG_MOVE01_4: {
            if (pProg->isJustChanged()) {
                pKuroko->setMvAcce(300);//�����J�n
            }
            break;
        }

    }
    pKuroko->behave();

    //getSeTx()->behave();
}

void EnemyTalante::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyTalante::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() < 30 && (pOther->getKind() & KIND_CHIKEI)) {
         //�o��30�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
         return;
    }

    bool was_destroyed = UTIL::proceedEnemyHit(this, pOther);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyTalante::onInactive() {
}

EnemyTalante::~EnemyTalante() {
}


