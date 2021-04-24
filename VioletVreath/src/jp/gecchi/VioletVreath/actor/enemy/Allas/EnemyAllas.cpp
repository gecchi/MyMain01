#include "EnemyAllas.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

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
    pDriverLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
}

void EnemyAllas::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyAllas::initialize() {
    setHitAble(true);
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->setFaceAngVelo(AXIS_Z, -7000);
    pVecDriver->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAllas::onActive() {
    if (pDriverLeader_ == nullptr) {
        throwCriticalException("EnemyAllas�̓X�v���C���K�{�ł�config���ĉ�����");
    }

    getStatus()->reset();
   iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
   getProgress()->change(1);
}

void EnemyAllas::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    //�y�p�^�[��1�F�X�v���C���ړ��z
    if (pProg->hasJustChangedTo(1)) {
        pDriverLeader_->start(ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
    }
    if (pProg->get() == 1) {
        //�X�v���C���ړ��I���҂�
        if (pDriverLeader_->isFinished()) {
            pProg->changeNext(); //���̃p�^�[����
        }
    }

    switch (iMovePatternNo_) {
        case 0:  //�y�p�^�[���O�F�X�v���C���ړ��J�n�z
            if (pDriverLeader_) {
                pDriverLeader_->start(ABSOLUTE_COORD); //�X�v���C���ړ����J�n(1:���W����)
            }
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 1:  //�y�p�^�[���P�F�X�v���C���ړ��I���҂��z
            if (pDriverLeader_) {
                //�X�v���C���ړ��L��
                if (pDriverLeader_->isFinished()) {
                    iMovePatternNo_++; //�X�v���C���ړ����I�������玟�̍s���p�^�[����
                }
            } else {
                //�X�v���C���ړ�����
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
                        pActor_shot->getVecDriver()->setRzRyMvAng(paAng_way[i], D90ANG);
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
            pVecDriver->turnMvAngTwd(pMYSHIP->_x, _y, pMYSHIP->_z,
                                    2000, 0,
                                    TURN_CLOSE_TO, true);
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 3:   //�y�s���p�^�[���R�z

            break;
        default:
            break;
    }

    if (pDriverLeader_) {
        pDriverLeader_->behave(); //�X�v���C���ړ���U�镑��
    }
    pVecDriver->behave();
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

EnemyAllas::~EnemyAllas() {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
}
