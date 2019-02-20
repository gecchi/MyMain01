#include "VreathItem.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/Trucker.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/core/util/Status.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_DRIFT      , //通常移動状態
    PROG_ATTACH     , //吸着中(未吸着)状態
    PROG_ABSORB     , //吸着中(吸着済)状態
    PROG_BANPEI,
};

VreathItem::VreathItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset)
               : Item(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "VreathItem";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    pKuroko->linkFaceAngByMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    setHitAble(true, false); //画面外当たり判定は無効
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 400000);
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_GET_ITEM_001");
}

void VreathItem::initialize() {
}

void VreathItem::onActive() {
    // _x, _y, _z は発生元座標に設定済み
    setHitAble(true, false);
    GgafDx::Trucker* const pTrucker = getTrucker();
    pTrucker->forceVxyzMvVeloRange(-30000, 30000);
    pTrucker->setZeroVxyzMvVelo();
    pTrucker->setZeroVxyzMvAcce();
    pTrucker->stopGravitationMvSequence();

    //初期方向設定
    MyShip* pMyShip = pMYSHIP;
//    //散らばり範囲正方形１辺の長さ
//    int scattered_renge    = pChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
//    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(0, 20000);
    float vX, vY, vZ;
    UTIL::getNormalizedVector(
            pMyShip->_x - _x,
            pMyShip->_y - _y,
            pMyShip->_z - _z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    pKuroko->setMvAngTwd( (coord)(_x + (vX * d) + RND(-r, +r)),
                          (coord)(_y + (vY * d) + RND(-r, +r)),
                          (coord)(_z + (vZ * d) + RND(-r, +r)) );
    pKuroko->setMvVelo(2000);
    pKuroko->setMvAcce(100);

    getProgress()->reset(PROG_DRIFT);
    _sx = _sy = _sz = 1000;
}

void VreathItem::processBehavior() {
    //通常移動
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafDx::Trucker* const pTrucker = getTrucker();
    GgafCore::Progress* const pProg = getProgress();
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
        MyShip* pMyShip = pMYSHIP;
        if (pProg->hasJustChanged()) {
            //自機に引力で引き寄せられるような動き設定
            pTrucker->setVxyzMvVelo(pKuroko->_vX * pKuroko->_velo_mv,
                                     pKuroko->_vY * pKuroko->_velo_mv,
                                     pKuroko->_vZ * pKuroko->_velo_mv );
            pTrucker->execGravitationMvSequenceTwd(pMyShip, PX_C(20), 200, PX_C(100));
            pKuroko->stopMv();
        }

        //かつ自機近辺に到達？
        if (ABS(pMyShip->_x - _x) < 20000 &&
            ABS(pMyShip->_y - _y) < 20000 &&
            ABS(pMyShip->_z - _z) < 20000 ) {

            kDX_ = pMyShip->_x - _x;
            kDY_ = pMyShip->_y - _y;
            kDZ_ = pMyShip->_z - _z;
            pProg->change(PROG_ABSORB); //吸着吸収へ
        }

    }

    //自機近辺に到達し、吸着、吸収中の動き
    if (pProg->get() == PROG_ABSORB) {
        MyShip* pMyShip = pMYSHIP;
        if (pProg->hasJustChanged()) {
            pTrucker->setZeroVxyzMvVelo();
            pTrucker->setZeroVxyzMvAcce();
            pTrucker->stopGravitationMvSequence();
        }
        _x = pMyShip->_x + kDX_;
        _y = pMyShip->_y + kDY_;
        _z = pMyShip->_z + kDZ_;
        _sx -= 100;
        _sy -= 100;
        _sz -= 100;
        if (_sx < 5) {
            getSeTransmitter()->play(0);
            pProg->changeNothing();
            sayonara(); //終了
        }
        pMyShip->getStatus()->plus(STAT_Stamina, 1);
    }
    pKuroko->behave();
    pTrucker->behave();
}

void VreathItem::processJudgement() {
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

void VreathItem::onInactive() {
}

void VreathItem::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト

    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == PROG_DRIFT && (pOther->lookUpKind() & KIND_MY_BODY))  {
        setHitAble(false);
        pProg->change(PROG_ATTACH);
    }
}

VreathItem::~VreathItem() {
}

