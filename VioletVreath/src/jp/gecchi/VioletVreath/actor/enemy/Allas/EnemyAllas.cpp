#include "EnemyAllas.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};

EnemyAllas::EnemyAllas(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Allas", StatusReset(EnemyAllas)) {
    _class_name = "EnemyAllas";
    iMovePatternNo_ = 0;
    pVehicleLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");     //����
}

void EnemyAllas::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyAllas::initialize() {
    setHitAble(true);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setFaceAngVelo(AXIS_Z, -7000);
    pVecVehicle->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAllas::onActive() {
    if (pVehicleLeader_ == nullptr) {
        throwCriticalException("EnemyAllas�̓X�v���C���K�{�ł�config���ĉ�����");
    }

    getStatus()->reset();
   iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
   getPhase()->change(1);
}

void EnemyAllas::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    //�y�p�^�[��1�F�J�[�u�ړ��z
    if (pPhase->hasJustChangedTo(1)) {
        pVehicleLeader_->start(ABSOLUTE_COORD); //�J�[�u�ړ����J�n(1:���W����)
    }
    if (pPhase->getCurrent() == 1) {
        //�J�[�u�ړ��I���҂�
        if (pVehicleLeader_->isFinished()) {
            pPhase->changeNext(); //���̃p�^�[����
        }
    }

    switch (iMovePatternNo_) {
        case 0:  //�y�p�^�[���O�F�J�[�u�ړ��J�n�z
            if (pVehicleLeader_) {
                pVehicleLeader_->start(ABSOLUTE_COORD); //�J�[�u�ړ����J�n(1:���W����)
            }
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 1:  //�y�p�^�[���P�F�J�[�u�ړ��I���҂��z
            if (pVehicleLeader_) {
                //�J�[�u�ړ��L��
                if (pVehicleLeader_->isFinished()) {
                    iMovePatternNo_++; //�J�[�u�ړ����I�������玟�̍s���p�^�[����
                }
            } else {
                //�J�[�u�ړ�����
                iMovePatternNo_++; //�����Ɏ��̍s���p�^�[����
            }
            break;

        case 2:  //�y�p�^�[���Q�F���ˏ�V���b�g���˂Ǝ��@�֕����]���z
            if (pDepo_shot_) {
                //���ˏ�V���b�g
                int way = RF_EnemyAllas_ShotWay(G_RANK); //�V���b�gWAY��
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDx::FigureActor* pActor_shot;
                for (int i = 0; i < way; i++) {
                    pActor_shot = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
                    if (pActor_shot) {
                        pActor_shot->setPositionAt(this);
                        pActor_shot->getVecVehicle()->setRzRyMvAng(paAng_way[i], D90ANG);
                        pActor_shot->activate();
                    }
                }
                GGAF_DELETEARR(paAng_way);
                //�V���b�g���˃G�t�F�N�g
                if (pDepo_effect_) {
                    GgafDx::FigureActor* pTestActor_Shot = (GgafDx::FigureActor*)pDepo_effect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->setPositionAt(this);
                    }
                }
            }
//            //���@�֕����]��
            pVecVehicle->turnMvAngTwd(pMYSHIP->_x, _y, pMYSHIP->_z,
                                    2000, 0,
                                    TURN_CLOSE_TO, true);
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 3:   //�y�s���p�^�[���R�z

            break;
        default:
            break;
    }

    if (pVehicleLeader_) {
        pVehicleLeader_->behave(); //�J�[�u�ړ�����悤��Driver�𑀍�
    }
    pVecVehicle->behave();
    //getSeTransmitter()->behave();
}

void EnemyAllas::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyAllas::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyAllas::onInactive() {
    sayonara();
}

void EnemyAllas::config(
        GgafDx::CurveManufacture* prm_pCurveManufacture,
        GgafCore::ActorDepository* prm_pDepo_shot,
        GgafCore::ActorDepository* prm_pDepo_shotEffect
        ) {
    //�J�[�u�ړ��v���O�����ݒ�
    pVehicleLeader_ = createCurveVehicleLeader(prm_pCurveManufacture);
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}

EnemyAllas::~EnemyAllas() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
