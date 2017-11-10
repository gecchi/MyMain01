#include "ScoreItem.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

ScoreItem::ScoreItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat)
               : Item(prm_name, prm_model, prm_pStat) {
    _class_name = "ScoreItem";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnableDraw(true);        //描画時、Zバッファ値は考慮される
    setZWriteEnable(false);  //自身のZバッファを書き込みしない
    setAlpha(0.9);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_X, D_ANG(3));
    pKuroko->setFaceAngVelo(AXIS_Y, D_ANG(5));
    pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(7));
    pKuroko->linkFaceAngByMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    useProgress(PROG_BANPEI);
    setHitAble(true, false); //画面外当たり判定は無効
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 400000);
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_GET_ITEM_001");
}

void ScoreItem::initialize() {
}

void ScoreItem::onActive() {
    // _x, _y, _z は発生元座標に設定済み
    setHitAble(true, false);
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    pAxesMover->forceVxyzMvVeloRange(-30000, 30000);
    pAxesMover->setZeroVxyzMvVelo();
    pAxesMover->setZeroVxyzMvAcce();
    pAxesMover->stopGravitationMvSequence();

    //初期方向設定
    MyShip* pMyShip = pMYSHIP;
//    //散らばり範囲正方形１辺の長さ
//    int scattered_renge    = pChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
//    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(0, 20000);
    float vX, vY, vZ;
    UTIL::getNormalizedVector(
            pMyShip->_x - _x,
            pMyShip->_y - _y,
            pMyShip->_z - _z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    pKuroko->setMvAngTwd((coord)(_x + (vX * d) + RND(-r, +r)),
                         (coord)(_y + (vY * d) + RND(-r, +r)),
                         (coord)(_z + (vZ * d) + RND(-r, +r)) );
    pKuroko->setMvVelo(2000);
    pKuroko->setMvAcce(100);

    getProgress()->reset(PROG_DRIFT);
    _sx = _sy = _sz = 1000;
}

void ScoreItem::processBehavior() {
    //通常移動
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    GgafProgress* const pProg = getProgress();
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
            pAxesMover->setVxyzMvVelo(pKuroko->_vX * pKuroko->_velo_mv,
                                     pKuroko->_vY * pKuroko->_velo_mv,
                                     pKuroko->_vZ * pKuroko->_velo_mv);
            pAxesMover->execGravitationMvSequenceTwd(pMyShip,
                                                    PX_C(20), 200, PX_C(100));
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
            pAxesMover->setZeroVxyzMvVelo();
            pAxesMover->setZeroVxyzMvAcce();
            pAxesMover->stopGravitationMvSequence();
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
        G_SCORE += 100;
    }
    pKuroko->behave();
    pAxesMover->behave();
}

void ScoreItem::processJudgement() {
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

void ScoreItem::onInactive() {
}

void ScoreItem::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト

    GgafProgress* const pProg = getProgress();
    if (pProg->get() == PROG_DRIFT && (pOther->lookUpKind() & KIND_MY_BODY))  {
        setHitAble(false);
        pProg->change(PROG_ATTACH);
    }

}

ScoreItem::~ScoreItem() {
}
