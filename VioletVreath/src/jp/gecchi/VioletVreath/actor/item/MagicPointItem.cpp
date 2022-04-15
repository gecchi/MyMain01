#include "MagicPointItem.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/GeoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/item/Item.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_DRIFT      , //通常移動状態
    PROG_ATTACH     , //吸着中(未吸着)状態
    PROG_ABSORB     , //吸着中(吸着済)状態
    PROG_BANPEI,
};
enum {
    SE_GET_ITEM ,
};

MagicPointItem::MagicPointItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset)
               : Item(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "MagicPointItem";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    pVecVehicle->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    pVecVehicle->linkFaceAngByMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    setHitAble(true, false); //画面外当たり判定は無効
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 400000);
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_GET_ITEM, "SE_GET_ITEM_001");
}

void MagicPointItem::initialize() {
}

void MagicPointItem::onActive() {
    // _x, _y, _z は発生元座標に設定済み
    setHitAble(true, false);
    GgafDx::GeoVehicle* const pGeoVehicle = getGeoVehicle();
    pGeoVehicle->forceVeloXYZRange(-30000, 30000);
    pGeoVehicle->setXYZZero();
    pGeoVehicle->setAcceXYZZero();
    pGeoVehicle->stopGravitationMvSequence();

    //初期方向設定
    MyShip* pMyShip = pMYSHIP;
//    //散らばり範囲正方形１辺の長さ
//    int scattered_renge    = pChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
//    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    pVecVehicle->forceMvVeloRange(0, 20000);
    float vX, vY, vZ;
    UTIL::getNormalizedVector(
            pMyShip->_x - _x,
            pMyShip->_y - _y,
            pMyShip->_z - _z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    pVecVehicle->setMvAngTwd( (coord)(_x + (vX * d) + RND(-r, +r)),
                          (coord)(_y + (vY * d) + RND(-r, +r)),
                          (coord)(_z + (vZ * d) + RND(-r, +r)) );
    pVecVehicle->setMvVelo(2000);
    pVecVehicle->setMvAcce(100);

    getProgress()->reset(PROG_DRIFT);
    _sx = _sy = _sz = 1000;
}

void MagicPointItem::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafDx::GeoVehicle* const pGeoVehicle = getGeoVehicle();
    GgafCore::Progress* const pProg = getProgress();
    //通常移動
    if (pProg->get() == PROG_DRIFT) {
        //TractorMagic発動中はPROG_ATTACHへ移行
        if (getTractorMagic()->is_tracting_) {
            effectFlush(6); //フラッシュ
            setHitAble(false);
            pProg->change(PROG_ATTACH);
        }
        //あるいは onHit() で PROG_ATTACH 状態変化するのを待つ
    }

    //自機と当たり判定がヒットし、自機に向かう動き
    if (pProg->get() == PROG_ATTACH) {
        MyMagicEnergyCore* pE = pMyShip->pMyMagicEnergyCore_;
        if (pProg->hasJustChanged()) {
            //自機に引力で引き寄せられるような動き設定
            pGeoVehicle->setVeloXYZ(pVecVehicle->_vX * pVecVehicle->_velo_mv,
                                     pVecVehicle->_vY * pVecVehicle->_velo_mv,
                                     pVecVehicle->_vZ * pVecVehicle->_velo_mv);
            pGeoVehicle->execGravitationMvSequenceTwd(pE,
                                                    PX_C(50), 300, PX_C(300));
            pVecVehicle->stop();
        }

        //かつ自機近辺に到達？
        if (ABS(pE->_x - _x) < PX_C(20) &&
            ABS(pE->_y - _y) < PX_C(20) &&
            ABS(pE->_z - _z) < PX_C(20) )
        {
            kDX_ = pE->_x - _x;
            kDY_ = pE->_y - _y;
            kDZ_ = pE->_z - _z;
            pProg->change(PROG_ABSORB); //吸着吸収へ
        }
    }

    //自機近辺に到達し、吸着、吸収中の動き
    if (pProg->get() == PROG_ABSORB) {
        MyMagicEnergyCore* pE = pMyShip->pMyMagicEnergyCore_;
        if (pProg->hasJustChanged()) {
            pGeoVehicle->setXYZZero();
            pGeoVehicle->setAcceXYZZero();
            pGeoVehicle->stopGravitationMvSequence();
        }
        _x = pE->_x + kDX_;
        _y = pE->_y + kDY_;
        _z = pE->_z + kDZ_;
        addScale(-100);
        pMyShip->mp_ += 12; //ここ調整！

        if (_sx < 100) {
            getSeTransmitter()->play(SE_GET_ITEM);
            pProg->changeNothing();
            sayonara(); //終了
        }
    }
    pVecVehicle->behave();
    pGeoVehicle->behave();
}

void MagicPointItem::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
//    //通常移動
//    if (pProg->get() == PROG_DRIFT) {
//        //onHit() で状態変化するのを待つ
//    }
//
//    //自機と当たり判定がヒット時
//    if (pProg->get() == PROG_ATTACH) {
//
//    }
//
//    //自機に吸着し、吸収中の動き
//    if (pProg->get() == PROG_ABSORB) {
//    }
}

void MagicPointItem::onInactive() {
}

void MagicPointItem::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト

    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == PROG_DRIFT && (pOther->lookUpKind() & KIND_MY_BODY))  {
        setHitAble(false);
        pProg->change(PROG_ATTACH);
    }
}

MagicPointItem::~MagicPointItem() {
}

