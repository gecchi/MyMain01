#include "VreathItem.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/core/util/Status.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_DRIFT      , //通常移動状態
    PHASE_ATTACH     , //吸着中(未吸着)状態
    PHASE_ABSORB     , //吸着中(吸着済)状態
    PHASE_BANPEI,
};

VreathItem::VreathItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset)
               : VvItemActor<GgafLib::DefaultMassMeshActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "VreathItem";
    effectBlendOne(); //加算合成するTechnique指定
    useZBufferDrawing(true);        //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    pLocusVehicle->linkFaceAngByMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    setHitAble(true, false); //画面外当たり判定は無効
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 400000);
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(0, "SE_GET_ITEM_001");
}

void VreathItem::initialize() {
}

void VreathItem::onActive() {
    // _x, _y, _z は発生元座標に設定済み
    setHitAble(true, false);
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    pCoordVehicle->forceVeloXYZRange(-30000, 30000);
    pCoordVehicle->setXYZZero();
    pCoordVehicle->setAcceXYZZero();
    pCoordVehicle->stopGravitationMvSequence();

    //初期方向設定
    MyShip* pMyShip = pMYSHIP;
//    //散らばり範囲正方形１辺の長さ
//    int scattered_renge    = pChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
//    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->forceMvVeloRange(0, 20000);
    double vX, vY, vZ;
    UTIL::getNormalizedVector(
            pMyShip->_x - _x,
            pMyShip->_y - _y,
            pMyShip->_z - _z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    pLocusVehicle->setMvAngTwd( (coord)(_x + (vX * d) + RND(-r, +r)),
                              (coord)(_y + (vY * d) + RND(-r, +r)),
                              (coord)(_z + (vZ * d) + RND(-r, +r)) );
    pLocusVehicle->setMvVelo(2000);
    pLocusVehicle->setMvAcce(100);

    getPhase()->reset(PHASE_DRIFT);
    _sx = _sy = _sz = 1000;
}

void VreathItem::processBehavior() {
    //通常移動
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == PHASE_DRIFT) {
        //TractorMagic発動中はPHASE_ATTACHへ移行
        if (getTractorMagic()->is_tracting_) {
            effectFlush(6); //フラッシュ
            setHitAble(false);
            pPhase->change(PHASE_ATTACH);
        }
        //あるいは onHit() で PHASE_ATTACH 状態変化するのを待つ
    }

    //自機と当たり判定がヒットし、自機に向かう動き
    if (pPhase->getCurrent() == PHASE_ATTACH) {
        MyShip* pMyShip = pMYSHIP;
        if (pPhase->hasJustChanged()) {
            //自機に引力で引き寄せられるような動き設定
            pCoordVehicle->setVeloXYZ(pLocusVehicle->_vX * pLocusVehicle->_velo_mv,
                                     pLocusVehicle->_vY * pLocusVehicle->_velo_mv,
                                     pLocusVehicle->_vZ * pLocusVehicle->_velo_mv );
            pCoordVehicle->execGravitationMvSequenceTwd(pMyShip, PX_C(20), 200, PX_C(100));
            pLocusVehicle->stop();
        }

        //かつ自機近辺に到達？
        if (ABS(pMyShip->_x - _x) < 20000 &&
            ABS(pMyShip->_y - _y) < 20000 &&
            ABS(pMyShip->_z - _z) < 20000 ) {

            kDX_ = pMyShip->_x - _x;
            kDY_ = pMyShip->_y - _y;
            kDZ_ = pMyShip->_z - _z;
            pPhase->change(PHASE_ABSORB); //吸着吸収へ
        }

    }

    //自機近辺に到達し、吸着、吸収中の動き
    if (pPhase->getCurrent() == PHASE_ABSORB) {
        MyShip* pMyShip = pMYSHIP;
        if (pPhase->hasJustChanged()) {
            pCoordVehicle->setXYZZero();
            pCoordVehicle->setAcceXYZZero();
            pCoordVehicle->stopGravitationMvSequence();
        }
        _x = pMyShip->_x + kDX_;
        _y = pMyShip->_y + kDY_;
        _z = pMyShip->_z + kDZ_;
        _sx -= 100;
        _sy -= 100;
        _sz -= 100;
        if (_sx < 5) {
            getSeXmtr()->play(0);
            pPhase->changeNothing();
            sayonara(); //終了
        }
        pMyShip->getStatus()->plus(STAT_Stamina, 1);
    }
    pLocusVehicle->behave();
    pCoordVehicle->behave();
}

void VreathItem::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
//    //通常移動
//    if (pPhase->getCurrent() == PHASE_DRIFT) {
//        //onHit() で状態変化するのを待つ
//    }
//
//    //自機と当たり判定がヒット時
//    if (pPhase->getCurrent() == PHASE_ATTACH) {
//
//    }
//
//    //自機に吸着し、吸収中の動き
//    if (pPhase->getCurrent() == PHASE_ABSORB) {
//    }
}

void VreathItem::onInactive() {
}

void VreathItem::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == PHASE_DRIFT && (prm_pOppHitChecker->_kind & KIND_MY_BODY))  {
        setHitAble(false);
        pPhase->change(PHASE_ATTACH);
    }
}

VreathItem::~VreathItem() {
}

