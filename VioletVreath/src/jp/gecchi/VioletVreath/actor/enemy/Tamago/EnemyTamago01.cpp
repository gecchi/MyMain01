#include "EnemyTamago01.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTamago01::EnemyTamago01(const char* prm_name) :
        VvEnemyActor<SpriteMeshSetActor>(prm_name, "8,tamago", StatusReset(EnemyTamago01)) { //8/������Ƃ��Ȃ��ƃ��j�[�N�ɂȂ�Ȃ�
    _class_name = "EnemyTamago01";
    iMovePatternNo_ = 0;
    pProgram_Tamago01Move_ = nullptr;
    pConn_depo_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;

    pConn_depo_ = connectToDepositoryManager("Shot001");
    //pDepo_shot_ = pConn_depo_->peek();
    pDepo_shot_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_EXPLOSION_001");
}

void EnemyTamago01::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyTamago01::initialize() {
    setHitAble(true);
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setRollFaceAngVelo(1000);
    pVecDriver->setMvAngTwd(900000, 300000, 300000);
    pVecDriver->setMvVelo(3000);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
//    pChecker->setColliAAPrism_Cube(0, 200000,POS_PRISM_ZX_PP);
//        pChecker->setColliAAPrism_WHD(0,0,0,300000,100000,200000,100000,POS_PRISM_YZ_PN);

    //�q�b�g���Ȃ����R��T���I�I
//      pChecker->setColliAAPrism_WHD(0,20000,-30000,50000,
//                                                90000,140000,60000,POS_PRISM_XY_NN);
//
//      pChecker->setColliAAPrism_WHD(1,-20000,-30000,-50000,
//                                                 60000,90000,140000,POS_PRISM_ZX_PP);

//    pChecker->setColliAABox_WHD(0,20000,-30000,50000,
//                                              90000,140000,60000);
    pChecker->setColliAACube(0, 50000);


    //pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _x = -50000;
    _y = 200000;
    _z = 100000;
    setScale(1000);
}

void EnemyTamago01::onActive() {
    getStatus()->reset();
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->start(ABSOLUTE_COORD); //�J�[�u�ړ����v���O�������Ă���
    }

//    getUvFlipper()->locatePatternNo(16, 1/16.0, 1/16.0);
//    getUvFlipper()->exec(FLIP_ORDER_LOOP, 5);
//    getUvFlipper()->setFlipPtnRange(0, 16*16-1);
//    getUvFlipper()->setActivePtn(0);
    iMovePatternNo_ = 0;
}

void EnemyTamago01::processBehavior() {

//    if (GgafDx::Input::isPressedKey(DIK_Q)) {
//        addScale(500);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_W)) {
//        addScale(-500);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_1)) {
//        pModel->getTexBlinker()->->addScale(2000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_2)) {
//        pModel->getTexBlinker()->->addScale(-2000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_3)) {
//        pModel->getTexBlinker()->->transitionAcceUntil(3000, 0, 3);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_4)) {
//        pModel->getTexBlinker()->->transitionLinearLoop(20, -1);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_5)) {
//        pModel->getTexBlinker()->->transitionLinearLoop(10, 5);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_6)) {
//        pModel->getTexBlinker()->->beat(20, 2 ,5, -1);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_7)) {
//        pModel->getTexBlinker()->->stopImmed();
//    }
//    if (GgafDx::Input::isPressedKey(DIK_0)) {
//        pModel->getTexBlinker()->->setScaleToBottom();
//    }
    GgafDx::VecDriver* const pVecDriver = getVecDriver();

    if (iMovePatternNo_ == 0) {
        //�J�[�u�ړ���
        if (pProgram_Tamago01Move_ && pProgram_Tamago01Move_->isFinished()) {
            iMovePatternNo_++; //�J�[�u�ړ����I�������玟�̍s���p�^�[����
        }
    }

    if (iMovePatternNo_ == 1) {
        //�J�[�u�ړ��I����
        pVecDriver->turnMvAngTwd(pMYSHIP->_x+800000, pMYSHIP->_y, pMYSHIP->_z,
                                            2000, 0,
                                            TURN_CLOSE_TO, false);
        iMovePatternNo_++; //���̍s���p�^�[����
    }

    if (iMovePatternNo_ == 2) {
        iMovePatternNo_++;
    }

    if (iMovePatternNo_ == 3) {

    }
    if (getBehaveingFrame() % 30U == 0) {
        pVecDriver->turnMvAngTwd(pMYSHIP,
                                2000,0,TURN_CLOSE_TO, false);

        if (pDepo_shot_) {
            //���ˏ�V���b�g����
            int way = 8;
            angle* paAng_way = NEW angle[way];
            angle target_RzRy_Rz, target_RzRy_Ry;
            UTIL::convVectorToRzRy(pMYSHIP->_x - _x, pMYSHIP->_y - _y, pMYSHIP->_z - _z,
                                   target_RzRy_Rz, target_RzRy_Ry);
            angle target_RyRz_Ry, target_RyRz_Rz;
            UTIL::convRzRyToRyRz(target_RzRy_Rz, target_RzRy_Ry, target_RyRz_Ry, target_RyRz_Rz);
            UTIL::getWayAngle2D(target_RyRz_Ry, way, 10000, paAng_way);
            GgafDx::FigureActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
                if (pActor) {
                    pActor->getVecDriver()->linkFaceAngByMvAng(true);
                    pActor->getVecDriver()->setRzRyMvAng_by_RyRz(paAng_way[i], target_RyRz_Rz);
                    pActor->setPositionAt(this);
                }
            }
            GGAF_DELETEARR(paAng_way);
            //�V���b�g���˃G�t�F�N�g
            if (pDepo_effect_) {
                pActor = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
                if (pActor) {
                    pActor->setPositionAt(this);
                }
            }
        }

    }
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->behave();
    }
    pVecDriver->behave();
    getScaler()->behave();
    getUvFlipper()->behave();
    //getSeTransmitter()->behave();
}

void EnemyTamago01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyTamago01::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(0);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyTamago01::onInactive() {
}

EnemyTamago01::~EnemyTamago01() {
    pConn_depo_->close();
    GGAF_DELETE_NULLABLE(pProgram_Tamago01Move_);
}
