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
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //���Z����
    setScaleR(0.3);
    useProgress(PROG_BANPEI);
}

void EnemyDuna::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyDuna::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyDuna::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyDuna::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

//    if (_pProg->isJustChanged()) {
//        _TRACE_("EnemyDuna::"<<_pProg->getFromProgOnChange()<<"��"<<_pProg->get()<<"");
//    }

    MyShip* pMyShip = P_MYSHIP;
    if (_pProg->isJustChanged()) {
        pAxsMver_->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            pAFader_->setAlpha(0);
            _pKuroko->relateFaceWithMvAng(false);
            _pKuroko->keepOnTurningFaceAngTwd(pMyShip,
                                               D_ANG(2), 0, TURN_CLOSE_TO,false);
            //_pKuroko->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
                         _pKuroko->setMvVelo(PX_C(6));
            _pKuroko->setRzRyMvAng(0, D90ANG);
            _pKuroko->setRzMvAngVelo(D_ANG(12));
            _pKuroko->setRzMvAngAcce(D_ANG(0.05));
            _pMorpher->setWeight(0.0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
         case PROG_ENTRY_EFFECT: {
             if (_pProg->getFrameInProgress() == 60) {
                 pAFader_->fadeLinerUntil(1.0, 60);
             }
             if (getAlpha() > 0.5) {
                 setHitAble(true);
                 _pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE01: {
             if (_pProg->isJustChanged()) {
             }
             _x -= PX_C(10);
             if (_x  < pMyShip->_x + PX_C(1000)) {
                 _pProg->changeNext();
             }
             break;
         }
         case PROG_ENTRY_MOVE02: {
             if (_pProg->isJustChanged()) {
                 _pKuroko->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO,false);
                 _pKuroko->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO,false);
             }
             if (!_pKuroko->isTurningMvAng() && !_pKuroko->isTurningFaceAng()) {
                 _pKuroko->relateFaceWithMvAng(true);
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv - SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!_pKuroko->isTurningMvAng()) {
                 //�@�̎��̓���
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 //�~�ʈړ�
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv + SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!_pKuroko->isTurningMvAng()) {
                 //�A�̎��̓���
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv - D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv - SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKuroko->isTurningMvAng()) {
                 //�B�̎��̓���
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv + SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKuroko->isTurningMvAng()) {
                 //�C�̎��̓���
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv - SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!_pKuroko->isTurningMvAng()) {
                 //�D�̎��̓���
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 //�~�ʈړ�
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv + SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!_pKuroko->isTurningMvAng()) {
                 //�E�̎��̓���
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv - D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv - SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKuroko->isTurningMvAng()) {
                 //�F�̎��̓���
                 _pProg->changeProbab(
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
             if (_pProg->isJustChanged()) {
                 //�܂��J�n��Ԃ̐^�������Ɍ���
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKuroko->isTurningMvAng()) {
                 //�~�ʈړ�
                 _pKuroko->turnRzMvAngTo(_pKuroko->_angRzMv + SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKuroko->isTurningMvAng()) {
                 //�G�̎��̓���
                 _pProg->changeProbab(
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

    _pKuroko->behave();
    pAxsMver_->behave();
    _pMorpher->behave();
    pAFader_->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pProg="<<_pProg->get()<<"   X,Y,Z="<<_x<<","<<_y<<","<<_z<<" ");
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
        _pSeTx->play3D(SE_EXPLOSION);
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
