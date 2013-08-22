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

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


#define PROG_CHANGE_AS_P(P1, C1, P2, C2, P3, C3, P4, C4, P5, C5, P6, C6, P7, C7, P8, C8) do { \
int r = RND(1,100); \
if (r <= (P1)) { \
    _pProg->change(C1); \
} else if ( (P1) < r && r <= ((P1)+(P2)) ) { \
    _pProg->change(C2); \
} else if ( ((P1)+(P2)) < r && r <= ((P1)+(P2)+(P3)) ) { \
    _pProg->change(C3);  \
} else if ( ((P1)+(P2)+(P3)) < r && r <= ((P1)+(P2)+(P3)+(P4)) ) { \
    _pProg->change(C4);  \
} else if ( ((P1)+(P2)+(P3)+(P4)) < r && r <= ((P1)+(P2)+(P3)+(P4)+(P5)) ) { \
    _pProg->change(C5);  \
} else if ( ((P1)+(P2)+(P3)+(P4)+(P5)) < r && r <= ((P1)+(P2)+(P3)+(P4)+(P5)+(P6)) ) { \
    _pProg->change(C6);  \
} else if ( ((P1)+(P2)+(P3)+(P4)+(P5)+(P6)) < r && r <= ((P1)+(P2)+(P3)+(P4)+(P5)+(P6)+(P7)) ) { \
    _pProg->change(C7);  \
} else if ( ((P1)+(P2)+(P3)+(P4)+(P5)+(P6)+(P7)) < r && r <= ((P1)+(P2)+(P3)+(P4)+(P5)+(P6)+(P7)+(P8)) ) { \
    _pProg->change(C8);  \
} \
} while(0)


EnemyDuna::EnemyDuna(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Duna", STATUS(EnemyDuna)) {
    _class_name = "EnemyDuna";
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    setScaleR(0.3);
    useProgress(PROG_CLOSE);
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
    MyShip* pMyShip = P_MYSHIP;
    switch (_pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             _pAFader->setAlpha(0);
             _pKurokoA->relateMvFaceAng(false);
             _pKurokoA->keepOnTurningFaceAngTwd(pMyShip,
                                                D_ANG(2), 0, TURN_CLOSE_TO,false);
             _pKurokoA->setMvVelo(RF_EnemyDuna_MvVelo(G_RANK));
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
             _X -= PX_C(30);
             if (_X  < pMyShip->_X + PX_C(400)) {
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
                 _pKurokoA->relateMvFaceAng(true);
                 PROG_CHANGE_AS_P( 0, PROG_MOVE_LARGE_UP_SEMIARC_CW,
                                  25, PROG_MOVE_LARGE_UP_SEMIARC_CCW,
                                  25, PROG_MOVE_LARGE_DOWN_SEMIARC_CW,
                                   0, PROG_MOVE_LARGE_DOWN_SEMIARC_CCW,
                                   0, PROG_MOVE_SMALL_UP_SEMIARC_CW,
                                  25, PROG_MOVE_SMALL_UP_SEMIARC_CCW,
                                  25, PROG_MOVE_SMALL_DOWN_SEMIARC_CW,
                                   0, PROG_MOVE_SMALL_DOWN_SEMIARC_CCW );
             }
             break;
         }
         case PROG_MOVE_LARGE_UP_SEMIARC_CW: {
             //↑→↓ 大きな上半円弧の時計回り (X座標は正の方向移動）
             if (_pProg->isJustChanged()) {
                 //まず開始状態の↑方向に向く
                 _pKurokoA->turnRzRyMvAngTo(D90ANG, 0, D_ANG(20), 0, TURN_CLOSE_TO, false);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //円弧移動
                 _pKurokoA->turnRzRyMvAngTo(D90ANG-D180ANG, 0, D_ANG(2), 0, TURN_CLOCKWISE, false);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 PROG_CHANGE_AS_P(25, PROG_MOVE_LARGE_UP_SEMIARC_CW,
                                  25, PROG_MOVE_LARGE_UP_SEMIARC_CCW,
                                  25, PROG_MOVE_LARGE_DOWN_SEMIARC_CW,
                                  25, PROG_MOVE_LARGE_DOWN_SEMIARC_CCW,
                                  25, PROG_MOVE_SMALL_UP_SEMIARC_CW,
                                  25, PROG_MOVE_SMALL_UP_SEMIARC_CCW,
                                  25, PROG_MOVE_SMALL_DOWN_SEMIARC_CW,
                                  25, PROG_MOVE_SMALL_DOWN_SEMIARC_CCW );
             }
             break;
         }

         case PROG_MOVE_LARGE_UP_SEMIARC_CCW: {
             //↑←↓ 大きな上半円弧の反時計回り (X座標は負の方向移動）
             if (_pProg->isJustChanged()) {
                 //まず開始状態の↑方向に向く
                 _pKurokoA->turnRzRyMvAngTo(D90ANG, 0, D_ANG(20), 0, TURN_CLOSE_TO, false);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //円弧移動
                 _pKurokoA->turnRzRyMvAngTo(D90ANG+D180ANG, 0, D_ANG(2), 0, TURN_COUNTERCLOCKWISE, false);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 PROG_CHANGE_AS_P( 0, PROG_MOVE_LARGE_UP_SEMIARC_CW,
                                   0, PROG_MOVE_LARGE_UP_SEMIARC_CCW,
                                  20, PROG_MOVE_LARGE_DOWN_SEMIARC_CW,
                                  20, PROG_MOVE_LARGE_DOWN_SEMIARC_CCW,
                                  20, PROG_MOVE_SMALL_UP_SEMIARC_CW,
                                   0, PROG_MOVE_SMALL_UP_SEMIARC_CCW,
                                  20, PROG_MOVE_SMALL_DOWN_SEMIARC_CW,
                                  20, PROG_MOVE_SMALL_DOWN_SEMIARC_CCW );
             }
             break;
         }
         case PROG_MOVE_LARGE_DOWN_SEMIARC_CW: {
             //↓←↑ 大きな下半円弧の時計回り (X座標は負の方向移動）
             if (_pProg->isJustChanged()) {
                 //まず開始状態の↓方向に向く
                 _pKurokoA->turnRzRyMvAngTo(-D90ANG, 0, D_ANG(20), 0, TURN_CLOSE_TO, false);
                 nprog_ = 0;
             }
             if (nprog_ == 0 && !_pKurokoA->isTurningMvAng()) {
                 //円弧移動
                 _pKurokoA->turnRzRyMvAngTo(-D90ANG-D180ANG, 0, D_ANG(2), 0, TURN_CLOCKWISE, false);
                 nprog_ = 1;
             }
             if (nprog_ == 1 && !_pKurokoA->isTurningMvAng()) {
                 PROG_CHANGE_AS_P( 0, PROG_MOVE_LARGE_UP_SEMIARC_CW,
                                   0, PROG_MOVE_LARGE_UP_SEMIARC_CCW,
                                  20, PROG_MOVE_LARGE_DOWN_SEMIARC_CW,
                                  20, PROG_MOVE_LARGE_DOWN_SEMIARC_CCW,
                                  20, PROG_MOVE_SMALL_UP_SEMIARC_CW,
                                   0, PROG_MOVE_SMALL_UP_SEMIARC_CCW,
                                  20, PROG_MOVE_SMALL_DOWN_SEMIARC_CW,
                                  20, PROG_MOVE_SMALL_DOWN_SEMIARC_CCW );
             }
             break;
         }
         default:
             break;
     }

    _pKurokoA->behave();
    _pMorpher->behave();
    _pAFader->behave();
//_TRACE_("EnemyDuna f:"<<getBehaveingFrame()<<"  pProg="<<_pProg->get()<<"   X,Y,Z="<<_X<<","<<_Y<<","<<_Z<<" ");
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
