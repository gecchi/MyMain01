#include "MagicPointItem.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/item/Item.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergyCore.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MagicPointItem::MagicPointItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat)
               : Item(prm_name, prm_model, prm_pStat) {
    _class_name = "MagicPointItem";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setAlpha(0.9);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    pKuroko->linkFaceAngByMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    useProgress(PROG_BANPEI);
    setHitAble(true, false); //画面外当たり判定は無効
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 400000);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_GET_ITEM, "WAVE_GET_ITEM_001");
}

void MagicPointItem::initialize() {
}

void MagicPointItem::onActive() {
    // _x, _y, _z は発生元座標に設定済み
    setHitAble(true, false);

    pAxsMver_->forceVxyzMvVeloRange(-30000, 30000);
    pAxsMver_->setZeroVxyzMvVelo();
    pAxsMver_->setZeroVxyzMvAcce();
    pAxsMver_->stopGravitationMvSequence();

    //初期方向設定
    MyShip* pMyShip = P_MYSHIP;
//    //散らばり範囲正方形１辺の長さ
//    int scattered_renge    = pChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
//    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(0, 20000);
    float vX, vY, vZ;
    UTIL::getNormalizeVector(
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

void MagicPointItem::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
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
        if (pProg->isJustChanged()) {
            //自機に引力で引き寄せられるような動き設定
            pAxsMver_->setVxyzMvVelo(pKuroko->_vX * pKuroko->_velo_mv,
                                     pKuroko->_vY * pKuroko->_velo_mv,
                                     pKuroko->_vZ * pKuroko->_velo_mv);
            pAxsMver_->execGravitationMvSequenceTwd(pE,
                                                    PX_C(50), 300, PX_C(300));
            pKuroko->stopMv();
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
        if (pProg->isJustChanged()) {
            pAxsMver_->setZeroVxyzMvVelo();
            pAxsMver_->setZeroVxyzMvAcce();
            pAxsMver_->stopGravitationMvSequence();
        }
        _x = pE->_x + kDX_;
        _y = pE->_y + kDY_;
        _z = pE->_z + kDZ_;
        addScale(-100);
        pMyShip->mp_ += 12; //ここ調整！

        if (_sx < 100) {
            getSeTx()->play(SE_GET_ITEM);
            pProg->changeNothing();
            sayonara(); //終了
        }
    }
    pKuroko->behave();
    pAxsMver_->behave();
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

void MagicPointItem::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト

    GgafProgress* const pProg = getProgress();
    if (pProg->get() == PROG_DRIFT && (pOther->getKind() & KIND_MY_BODY))  {
        setHitAble(false);
        pProg->change(PROG_ATTACH);
    }
}

MagicPointItem::~MagicPointItem() {
    GGAF_DELETE(pAxsMver_);
}

