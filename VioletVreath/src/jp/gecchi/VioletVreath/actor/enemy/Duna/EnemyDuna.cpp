#include "stdafx.h"
#include "EnemyDuna.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"

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
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    effectBlendOne(); //加算合成
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
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

//    if (_pProg->isJustChanged()) {
//        _TRACE_("EnemyDuna::"<<_pProg->getFromProgOnChange()<<"→"<<_pProg->get()<<"");
//    }

    MyShip* pMyShip = P_MYSHIP;
    if (_pProg->isJustChanged()) {
        _pKurokoB->execGravitationMvSequenceTwd(pMyShip, PX_C(3), 30, PX_C(1));
    }

    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            _pKurokoA->relateFaceWithMvAng(false);
            _pKurokoA->keepOnTurningFaceAngTwd(pMyShip,
                                               D_ANG(2), 0, TURN_CLOSE_TO,false);
            //_pKurokoA->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
                         _pKurokoA->setMvVelo(PX_C(6));
            _pKurokoA->setRzRyMvAng(0, D90ANG);
            _pKurokoA->setRzMvAngVelo(D_ANG(12));
            _pKurokoA->setRzMvAngAcce(D_ANG(0.05));
            _pMorpher->setWeight(0.0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
         case PROG_ENTRY_EFFECT: {
             if (_pProg->getFrameInProgress() == 60) {
                 _pAFader->fadeLinerUntil(1.0, 60);
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
                 _pKurokoA->turnRzRyMvAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO,false);
                 _pKurokoA->turnRzRyFaceAngTo(0, D180ANG, D_ANG(5), 0, TURN_CLOSE_TO,false);
             }
             if (!_pKurokoA->isTurningMvAng() && !_pKurokoA->isTurningFaceAng()) {
                 _pKurokoA->relateFaceWithMvAng(true);
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

         //  直前の移動が
         //
         //      | ↑        ↓ |        |↑  ↓|
         //       ＼          ／    or    ＼←／
         //         ＼  ←  ／              ￣
         //           ￣￣￣
         //  だった場合
         //             →
         //           ＿＿＿                         →
         //         ／  ←  ＼                       ＿
         //       ／          ＼                   ／←＼
         //   ↑ | ↓        ↑ | ↓           ↑ |↓  ↑| ↓
         //   �@             �A                �D      �E
         //
         //
         //   �C             �B                �G      �F
         //   ↓ | ↑        ↓ |  ↑          ↓ |↑  ↓| ↑
         //       ＼          ／                   ＼←／
         //         ＼  ←  ／                       ￣
         //           ￣￣￣                         →
         //             →
         //
         //  �@ ・・・ PROG_MOVE_ORDER_LARGE_SEMIARC_CW       順方向、  大円弧移動、時計回り
         //  �A ・・・ PROG_MOVE_ORDER_LARGE_SEMIARC_CCW      順方向、  大円弧移動、半時計回り
         //  �B ・・・ PROG_MOVE_REV_LARGE_SEMIARC_CW         方向反転、大円弧移動、時計回り
         //  �C ・・・ PROG_MOVE_REV_LARGE_SEMIARC_CCW        方向反転、大円弧移動、半時計回り
         //  �D ・・・ PROG_MOVE_ORDER_SMALL_SEMIARC_CW       順方向、  小円弧移動、時計回り
         //  �E ・・・ PROG_MOVE_ORDER_SMALL_SEMIARC_CCW      順方向、  小円弧移動、半時計回り
         //  �F ・・・ PROG_MOVE_REV_SMALL_SEMIARC_CW         方向反転、小円弧移動、時計回り
         //  �G ・・・ PROG_MOVE_REV_SMALL_SEMIARC_CCW        方向反転、小円弧移動、半時計回り

         case PROG_MOVE_ORDER_LARGE_SEMIARC_CW: {  //�@
             if (_pProg->isJustChanged()) {
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //�@の次の動作
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
                 //円弧移動
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //�Aの次の動作
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
                 //まず開始状態の真裏方向に向く
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //円弧移動
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //�Bの次の動作
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
                 //まず開始状態の真裏方向に向く
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //円弧移動
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          LARGE_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //�Cの次の動作
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
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //�Dの次の動作
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
                 //円弧移動
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
             }
             if (!_pKurokoA->isTurningMvAng()) {
                 //�Eの次の動作
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
                 //まず開始状態の真裏方向に向く
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //円弧移動
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv - SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_CLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //�Fの次の動作
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
                 //まず開始状態の真裏方向に向く
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + D180ANG,
                                          REV_TURN_ANGVELO, 0, TURN_CLOSE_TO);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //円弧移動
                 _pKurokoA->turnRzMvAngTo(_pKurokoA->_angRzMv + SEMIARC_ANG,
                                          SMALL_SEMIARC_ANGVELO, 0, TURN_COUNTERCLOCKWISE);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 //�Gの次の動作
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

    _pKurokoA->behave();
    _pKurokoB->behave();
    _pMorpher->behave();
    _pAFader->behave();
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
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyDuna::onInactive() {
}

void EnemyDuna::onDispatchedShot(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index) {
    prm_pActor->activateDelay(prm_way_index*5 + 1); //activate 上書き。num_fire_*5 の 5 と同じ値にすること
}

EnemyDuna::~EnemyDuna() {
}
