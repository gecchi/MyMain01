#include "stdafx.h"
#include "EnemyDuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define REV_TURN_ANGVELO (D_ANG(30))
#define LARGE_SEMIARC_ANGVELO (D_ANG(3))
#define SMALL_SEMIARC_ANGVELO (D_ANG(6))
#define SEMIARC_ANG (D_ANG(200))
EnemyDuna::EnemyDuna(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Duna", STATUS(EnemyDuna)) {
    _class_name = "EnemyDuna";
    pAFader_ = NEW GgafDxAlphaFader(this);
    pAxsMver_ = NEW GgafDxAxesMover(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //���Z����
    setScaleR(0.3);
    useProgress(PROG_BANPEI);
}

void EnemyDuna::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDuna::initialize() {
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyDuna::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyDuna::processBehavior() {
    //���Z�����N�|�C���g������
    UTIL::updateEnemyRankPoint(this);

//    if (pProg->isJustChanged()) {
//        _TRACE_("EnemyDuna::"<<pProg->getFromProgOnChange()<<"��"<<pProg->get()<<"");
//    }

    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    if (pProg->isJustChanged()) {
        pAxsMver_->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pKuroko->relateFaceWithMvAng(false);
            pKuroko->keepOnTurningFaceAngTwd(pMyShip,
                                             D_ANG(2), 0, TURN_CLOSE_TO,false);
            //pKuroko->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
            pKuroko->setMvVelo(PX_C(6));
            pKuroko->setRzRyMvAng(0, D90ANG);
            pKuroko->setRzMvAngVelo(D_ANG(12));
            pKuroko->setRzMvAngAcce(D_ANG(0.05));
            setMorphWeight(0.0);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
         case PROG_ENTRY_EFFECT: {
             if (pProg->getFrameInProgress() == 60) {
                 pAFader_->transitionLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE01: {
             if (pProg->isJustChanged()) {
             }
             _x -= PX_C(10);
             if (_x  < pMyShip->_x + PX_C(1000)) {
                 pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE02: {
             if (pProg->isJustChanged()) {
                 pKuroko->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
                 pKuroko->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO, false);
             }
             if (!pKuroko->isTurningMvAng() && !pKuroko->isTurningFaceAng()) {
                 pKuroko->relateFaceWithMvAng(true);
                 pProg->changeProbab(
                              0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,
                             25, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW,
                             25, PROG_MOVE_REV_LARGE_SEMIARC_CW,
                              0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,
                              0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,
                             25, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW,
                             25, PROG_MOVE_REV_SMALL_SEMIARC_CW,
                              0, PROG_MOVE_REV_SMALL_SEMIARC_CCW
                         );
             }
             break;
         }

         //  ���O�̈ړ���
         //
         //      | ��        �� |        |��  ��|
         //       �_          �^    or    �_���^
         //         �_  ��  �^              �P
         //           �P�P�P
         //  �������ꍇ
         //             ��
         //           �Q�Q�Q                         ��
         //         �^  ��  �_                       �Q
         //       �^          �_                   �^���_
         //   �� | ��        �� | ��           �� |��  ��| ��
         //   �@             �A                �D      �E
         //
         //
         //   �C             �B                �G      �F
         //   �� | ��        �� |  ��          �� |��  ��| ��
         //       �_          �^                   �_���^
         //         �_  ��  �^                       �P
         //           �P�P�P                         ��
         //             ��
         //
         //  �@ �E�E�E PROG_MOVE_ORDER_LARGE_SEMIARC_CW       �������A  ��~�ʈړ��A���v���
         //  �A �E�E�E PROG_MOVE_ORDER_LARGE_SEMIARC_CCW      �������A  ��~�ʈړ��A�����v���
         //  �B �E�E�E PROG_MOVE_REV_LARGE_SEMIARC_CW         �������]�A��~�ʈړ��A���v���
         //  �C �E�E�E PROG_MOVE_REV_LARGE_SEMIARC_CCW        �������]�A��~�ʈړ��A�����v���
         //  �D �E�E�E PROG_MOVE_ORDER_SMALL_SEMIARC_CW       �������A  ���~�ʈړ��A���v���
         //  �E �E�E�E PROG_MOVE_ORDER_SMALL_SEMIARC_CCW      �������A  ���~�ʈړ��A�����v���
         //  �F �E�E�E PROG_MOVE_REV_SMALL_SEMIARC_CW         �������]�A���~�ʈړ��A���v���
         //  �G �E�E�E PROG_MOVE_REV_SMALL_SEMIARC_CCW        �������]�A���~�ʈړ��A�����v���

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CW: {  //�@
             if (pProg->isJustChanged()) {
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�@�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CCW: { //�A
             if (pProg->isJustChanged()) {
                 //�~�ʈړ�
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�A�̎��̓���
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CW: {  //�B
             if (pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv - SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�B�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_LARGE_SEMIARC_CCW: {  //�C
             if (pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv + SEMIARC_ANG,
                                        LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�C�̎��̓���
                 pProg->changeProbab(
                              10, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                              15, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }





         case PROG_MOVE_ORDER_SMALL_SEMIARC_CW: {  //�D
             if (pProg->isJustChanged()) {
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�D�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }

         case PROG_MOVE_ORDER_SMALL_SEMIARC_CCW: { //�E
             if (pProg->isJustChanged()) {
                 //�~�ʈړ�
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv + SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!pKuroko->isTurningMvAng()) {
                 //�E�̎��̓���
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CW: {  //�F
             if (pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv - D180ANG,
                                        REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv - SEMIARC_ANG,
                                        SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�F�̎��̓���
                 pProg->changeProbab(
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         case PROG_MOVE_REV_SMALL_SEMIARC_CCW: {  //�G
             if (pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 pKuroko->turnRzMvAngTo(pKuroko->_angRzMv + SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !pKuroko->isTurningMvAng()) {
                 //�G�̎��̓���
                 pProg->changeProbab(
                              40, PROG_MOVE_ORDER_LARGE_SEMIARC_CW,  //  �@
                               0, PROG_MOVE_ORDER_LARGE_SEMIARC_CCW, //  �A
                              30, PROG_MOVE_REV_LARGE_SEMIARC_CW,    //  �B
                               0, PROG_MOVE_REV_LARGE_SEMIARC_CCW,   //  �C
                              30, PROG_MOVE_ORDER_SMALL_SEMIARC_CW,  //  �D
                               0, PROG_MOVE_ORDER_SMALL_SEMIARC_CCW, //  �E
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CW,    //  �F
                               0, PROG_MOVE_REV_SMALL_SEMIARC_CCW    //  �G
                         );
             }
             break;
         }
         default:
             break;
     }

    pKuroko->behave();
    pAxsMver_->behave();
    getMorpher()->behave();
    pAFader_->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pProg="<<pProg->get()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
}

void EnemyDuna::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyDuna::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //��j��
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate �㏑���Bnum_fire_*5 �� 5 �Ɠ����l�ɂ��邱��
}

EnemyDuna::~EnemyDuna() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pAxsMver_);
}