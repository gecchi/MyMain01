#include "EnemyRis.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyRis::EnemyRis(const char* prm_name)
      : VvEnemyActor<DefaultMeshSetActor>(prm_name, "Ris", StatusReset(EnemyRis)) {
    _class_name = "EnemyRis";
    iMovePatternNo_ = 0;
    pVehicleLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
}

void EnemyRis::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.5, 0.9);
    pModel->getTexBlinker()->setRange(0.5, 2.0);
    pModel->getTexBlinker()->beat(60, 3, 0, 57, -1);
}

void EnemyRis::initialize() {
    setHitAble(true);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setRollFaceAngVelo(5000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void EnemyRis::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0; //�s���p�^�[�����Z�b�g
}

void EnemyRis::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    switch (iMovePatternNo_) {
        case 0:  //�y�p�^�[���O�F�J�[�u�ړ��J�n�z
            if (pVehicleLeader_) {
                pVehicleLeader_->start(ABSOLUTE_COORD); //�J�[�u�ړ����J�n
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
                int way = RF_EnemyRis_ShotWay(G_RANK); //�V���b�gWAY��
                UTIL::shotWay004(_x, _y, _z,
                                 D180ANG, D0ANG,
                                 pDepo_shot_,
                                 PX_C(20), way, D_ANG(120),
                                 0, 0,  //�V���b�g���ő��x��ݒ�
                                 1, 0, 1.0,
                                 nullptr );
                //�V���b�g���˃G�t�F�N�g
                if (pDepo_effect_) {
                    GgafDx::FigureActor* pTestActor_Shot = (GgafDx::FigureActor*)pDepo_effect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->setPositionAt(this);
                    }
                }
            }
            //���@�֕����]��
            pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                  3000, 0,
                                  TURN_CLOSE_TO, true);
            iMovePatternNo_++; //���̍s���p�^�[����
            break;

        case 3:  //�y�s���p�^�[���R�F���@�փO���b�Ƌt��]�ŕ����]���J�n�z
            if (_z-10000 < pMYSHIP->_z && pMYSHIP->_z < _z+10000) {
                //���@��Z�����ڋ߂�����O���b�Ƌt��]�ŕ����]��
                pLocusVehicle->turnMvAngTwd(MyShip::lim_x_behaind_ - 500000 , _y, _z,
                                      10000, 0,
                                      TURN_CLOSE_TO, true);
                pLocusVehicle->setMvAcce(100);
                iMovePatternNo_++;
            } else {
                //���@��Z�����ڋ߂���܂ő҂�
            }
            break;
        default:
            break;
    }


    if (pVehicleLeader_) {
        pVehicleLeader_->behave(); //�J�[�u�ړ�����悤��Driver�𑀍�
    }
    pLocusVehicle->behave();
    //getSeXmtr()->behave();
}

void EnemyRis::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyRis::onInactive() {
    sayonara();
}

EnemyRis::~EnemyRis() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
