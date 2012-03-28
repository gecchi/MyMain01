#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    ITEM_PROG_NOTIONG = 1, //何もしていない状態
    ITEM_PROG_DRIFT      , //通常移動状態
    ITEM_PROG_ATTACH     , //吸着中(未吸着)状態
    ITEM_PROG_ABSORB     , //吸着中(吸着済)状態
};


MagicPointItem::MagicPointItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat)
               : Item(prm_name, prm_model, prm_pStat) {
    _class_name = "MagicPointItem";
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setAlpha(0.9);

    _pKurokoA->setFaceAngVelo(AXIS_X, DEG2ANG(3));
    _pKurokoA->setFaceAngVelo(AXIS_Y, DEG2ANG(5));
    _pKurokoA->setFaceAngVelo(AXIS_Z, DEG2ANG(7));
    _pKurokoA->relateFaceAngWithMvAng(true);
    kDX_ = kDY_ = kDZ_ = 0;
    useProgress();
    setHitAble(true, false); //画面外当たり判定は無効
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 400000);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "decide1");
}

void MagicPointItem::initialize() {
}

void MagicPointItem::onActive() {
    setHitAble(true, false);
    _pKurokoA->setMvVelo(2000);
    _pKurokoA->setMvAcce(100);
    _pKurokoA->forceMvVeloRange(0, 20000);
    _pKurokoB->forceVxyzMvVeloRange(-30000, 30000);
    _pKurokoB->setZeroVxyzMvVelo();
    _pKurokoB->setZeroVxyzMvAcce();
    _pKurokoB->stopGravitationMvSequence();
    _pProg->set(ITEM_PROG_DRIFT);
    _SX = _SY = _SZ = 1000;

    //初期方向設定
    MyShip* pMyShip = P_MYSHIP;
    GgafCore::CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    //散らばり範囲正方形１辺の長さ
    int scattered_renge    = _pColliChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
    int scattered_distance = scattered_renge/2 + 400000;
    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。

    float vX, vY, vZ;
    GgafDxUtil::getNormalizeVector(
            pMyShip->_X - _X,
            pMyShip->_Y - _Y,
            pMyShip->_Z - _Z,
            vX, vY, vZ);

    _pKurokoA->setMvAng(
            (int)(_X + (vX * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Y + (vY * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Z + (vZ * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2)))
    );
}

void MagicPointItem::processBehavior() {
    //通常移動
    if (_pProg->get() == ITEM_PROG_DRIFT) {
        //TractorMagic発動中はITEM_PROG_ATTACHへ移行
        if (getTractorMagic()->is_tracting_) {
            changeEffectTechniqueInterim("Flush", 6); //フラッシュ
            setHitAble(false);
            _pProg->change(ITEM_PROG_ATTACH);
        }
        //あるいは onHit() で ITEM_PROG_ATTACH 状態変化するのを待つ
    }

    //自機と当たり判定がヒットし、自機に向かう動き
    if (_pProg->get() == ITEM_PROG_ATTACH) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pProg->isJustChanged()) {
            //自機に引力で引き寄せられるような動き設定
            _pKurokoB->setVxMvVelo(_pKurokoA->_vX*_pKurokoA->_veloMv);
            _pKurokoB->setVyMvVelo(_pKurokoA->_vY*_pKurokoA->_veloMv);
            _pKurokoB->setVzMvVelo(_pKurokoA->_vZ*_pKurokoA->_veloMv);
            _pKurokoB->execGravitationMvSequence(pMyShip, P2C(30), 100, 60000);
            _pKurokoA->setMvVelo(0);
            _pKurokoA->setMvAcce(0);
        }

        //かつ自機近辺に到達？
        if (abs(pMyShip->_X - _X) < 20000 &&
            abs(pMyShip->_Y - _Y) < 20000 &&
            abs(pMyShip->_Z - _Z) < 20000 ) {

            kDX_ = pMyShip->_X - _X;
            kDY_ = pMyShip->_Y - _Y;
            kDZ_ = pMyShip->_Z - _Z;
            _pProg->change(ITEM_PROG_ABSORB); //吸着吸収へ
        }

    }

    //自機近辺に到達し、吸着、吸収中の動き
    if (_pProg->get() == ITEM_PROG_ABSORB) {
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
            _pSeTransmitter->play(0);
            _pProg->change(ITEM_PROG_NOTIONG);
            sayonara(); //終了
        }
        P_MYSHIP_SCENE->pMagicMeter_->pEnagyBar_->pAmount_->inc(1);
    }
    _pKurokoA->behave();
    _pKurokoB->behave();
}

void MagicPointItem::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
//    //通常移動
//    if (_pProg->get() == ITEM_PROG_DRIFT) {
//        //onHit() で状態変化するのを待つ
//    }
//
//    //自機と当たり判定がヒット時
//    if (_pProg->get() == ITEM_PROG_ATTACH) {
//
//    }
//
//    //自機に吸着し、吸収中の動き
//    if (_pProg->get() == ITEM_PROG_ABSORB) {
//    }
}

void MagicPointItem::onInactive() {
}

void MagicPointItem::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト


    if (_pProg->get() == ITEM_PROG_DRIFT && (pOther->getKind() & KIND_MY_BODY))  {
        setHitAble(false);
        _pProg->change(ITEM_PROG_ATTACH);
    }

}

MagicPointItem::~MagicPointItem() {
}
