#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MagicPointItem::MagicPointItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat)
               : Item(prm_name, prm_model, prm_pStat) {
    _class_name = "MagicPointItem";
    effectBlendOne(); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setAlpha(0.9);

    _pKurokoA->setFaceAngVelo(D_ANG(3), D_ANG(5), D_ANG(7));
    _pKurokoA->relateMvFaceAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    useProgress(PROG_ABSORB);
    setHitAble(true, false); //画面外当たり判定は無効
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 400000);
    _pSeTx->set(0, "WAVE_GET_ITEM_001");
}

void MagicPointItem::initialize() {
}

void MagicPointItem::onActive() {
    // _X, _Y, _Z は発生元座標に設定済み
    setHitAble(true, false);

    _pKurokoB->forceVxyzMvVeloRange(-30000, 30000);
    _pKurokoB->setZeroVxyzMvVelo();
    _pKurokoB->setZeroVxyzMvAcce();
    _pKurokoB->stopGravitationMvSequence();

    //初期方向設定
    MyShip* pMyShip = P_MYSHIP;
//    //散らばり範囲正方形１辺の長さ
//    int scattered_renge    = _pColliChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
//    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
////    int scattered_distance = scattered_renge/2 + 400000;
//    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。

    _pKurokoA->forceMvVeloRange(0, 20000);
    float vX, vY, vZ;
    UTIL::getNormalizeVector(
            pMyShip->_X - _X,
            pMyShip->_Y - _Y,
            pMyShip->_Z - _Z,
            vX, vY, vZ);
    int d = PX_C(200);
    int r = PX_C(75);
    _pKurokoA->setMvAngTwd( (coord)(_X + (vX * d) + RND(-r, +r)),
                            (coord)(_Y + (vY * d) + RND(-r, +r)),
                            (coord)(_Z + (vZ * d) + RND(-r, +r)) );
    _pKurokoA->setMvVelo(2000);
    _pKurokoA->setMvAcce(100);

    _pProg->reset(PROG_DRIFT);
    _SX = _SY = _SZ = 1000;
}

void MagicPointItem::processBehavior() {
    //通常移動
    if (_pProg->get() == PROG_DRIFT) {
        //TractorMagic発動中はPROG_ATTACHへ移行
        if (getTractorMagic()->is_tracting_) {
            effectFlush(6); //フラッシュ
            setHitAble(false);
            _pProg->change(PROG_ATTACH);
        }
        //あるいは onHit() で PROG_ATTACH 状態変化するのを待つ
    }

    //自機と当たり判定がヒットし、自機に向かう動き
    if (_pProg->get() == PROG_ATTACH) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pProg->isJustChanged()) {
            //自機に引力で引き寄せられるような動き設定
            _pKurokoB->setVxyzMvVelo(_pKurokoA->_vX*_pKurokoA->_veloMv,
                                     _pKurokoA->_vY*_pKurokoA->_veloMv,
                                     _pKurokoA->_vZ*_pKurokoA->_veloMv);
            _pKurokoB->execGravitationMvSequenceTwd(pMyShip,
                                                    PX_C(30), 100, 60000);
            _pKurokoA->setMvVelo(0);
            _pKurokoA->setMvAcce(0);
        }

        //かつ自機近辺に到達？
        if (ABS(pMyShip->_X - _X) < 20000 &&
            ABS(pMyShip->_Y - _Y) < 20000 &&
            ABS(pMyShip->_Z - _Z) < 20000 )
        {
            kDX_ = pMyShip->_X - _X;
            kDY_ = pMyShip->_Y - _Y;
            kDZ_ = pMyShip->_Z - _Z;
            _pProg->change(PROG_ABSORB); //吸着吸収へ
        }

    }

    //自機近辺に到達し、吸着、吸収中の動き
    if (_pProg->get() == PROG_ABSORB) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pProg->isJustChanged()) {
            _pKurokoB->setZeroVxyzMvVelo();
            _pKurokoB->setZeroVxyzMvAcce();
            _pKurokoB->stopGravitationMvSequence();
        }
        _X = pMyShip->_X + kDX_;
        _Y = pMyShip->_Y + kDY_;
        _Z = pMyShip->_Z + kDZ_;
        _SX -= 100;
        _SY -= 100;
        _SZ -= 100;
        if (_SX < 5) {
            _pSeTx->play(0);
            _pProg->changeNothing();
            sayonara(); //終了
        }
        pMyShip->mp_.inc(1);
    }
    _pKurokoA->behave();
    _pKurokoB->behave();
}

void MagicPointItem::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
//    //通常移動
//    if (_pProg->get() == PROG_DRIFT) {
//        //onHit() で状態変化するのを待つ
//    }
//
//    //自機と当たり判定がヒット時
//    if (_pProg->get() == PROG_ATTACH) {
//
//    }
//
//    //自機に吸着し、吸収中の動き
//    if (_pProg->get() == PROG_ABSORB) {
//    }
}

void MagicPointItem::onInactive() {
}

void MagicPointItem::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト


    if (_pProg->get() == PROG_DRIFT && (pOther->getKind() & KIND_MY_BODY))  {
        setHitAble(false);
        _pProg->change(PROG_ATTACH);
    }

}

MagicPointItem::~MagicPointItem() {
}
