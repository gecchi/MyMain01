#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MagicPointItem001::MagicPointItem001(const char* prm_name)
               : Item(prm_name, "EffectMagic001") {
    _class_name = "MagicPointItem001";
    MyStgUtil::resetMagicPointItem001Status(_pStatus);
    changeEffectTechnique("DestBlendOne"); //加算合成するTechnique指定
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(false);  //Zバッファは書き込み無し
    setAlpha(0.9);

    _pMvNavigator->setFaceAngVelo(AXIS_X, 3*1000);
    _pMvNavigator->setFaceAngVelo(AXIS_Y, 5*1000);
    _pMvNavigator->setFaceAngVelo(AXIS_Z, 7*1000);
    _pMvNavigator->relateFaceAngWithMvAng(true);
    _kDX = _kDY = _kDZ = 0;
}

void MagicPointItem001::initialize() {
    setHitAble(true, false); //画面外当たり判定は無効
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 300000);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "decide1");
    useProgress();
}

void MagicPointItem001::onReset() {

    MyStgUtil::resetMagicPointItem001Status(_pStatus);
    setHitAble(true, false);
    _pMvNavigator->setMvVelo(2000);
    _pMvNavigator->setMvAcce(100);
    _pMvNavigator->forceMvVeloRange(0, 20000);
    _pMvTransporter->forceVxyzMvVeloRange(-20000, 20000);
    _pMvTransporter->setZeroVxyzMvVelo();
    _pMvTransporter->setZeroVxyzMvAcce();
    _pMvTransporter->_gravitation_mv_seq_flg = false;
    _pPrg->set(ITEM_PROG_DRIFT);
    _SX = _SY = _SZ = 1000;
}
void MagicPointItem001::onActive() {
    reset();
    MyShip* pMyShip = P_MYSHIP;
    CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    //散らばり範囲正方形１辺の長さ
    int scattered_renge    = _pCollisionChecker->_pCollisionArea->_papColliPart[0]->_dx; //当たり判定と同等
    //発生地点から、自機への方向への散らばり範囲正方形領域が位置する距離（scattered_distance > (scattered_renge/2) であること)
    int scattered_distance = scattered_renge/2 + 800000;
    //従って、scattered_distance 離れていても、自機は動かなくてもぎりぎり全て回収できる。

    float vX, vY, vZ;
    GgafDx9Util::getNormalizeVector(
            pMyShip->_X - _X,
            pMyShip->_Y - _Y,
            pMyShip->_Z - _Z,
            vX, vY, vZ);

    _pMvNavigator->setMvAng(
            (int)(_X + (vX * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Y + (vY * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))),
            (int)(_Z + (vZ * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2)))
    );
//    _TRACE_("---");
//    _TRACE_("(X,Y,Z)=("<<_X<<","<<_Y<<","<<_Z<<")");
//    _TRACE_("(pMyShip->_X,pMyShip->Y,pMyShip->Z)=("<<pMyShip->_X<<","<<pMyShip->_Y<<","<<pMyShip->_Z<<")");
//    _TRACE_("(vX,vY,vZ)=("<<vX<<","<<vY<<","<<vZ<<")");
//    _TRACE_("scattered_renge="<<scattered_renge<<"");
//    _TRACE_("scattered_distance="<<scattered_distance<<"");
//    _TRACE_("tX="<<(int)(_X + (vX * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))));
//    _TRACE_("tY="<<(int)(_Y + (vY * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))));
//    _TRACE_("tZ="<<(int)(_Z + (vZ * scattered_distance) + (((int)pRndGen->genrand_int32() % scattered_renge) - (scattered_renge/2))));

}

void MagicPointItem001::processBehavior() {
    //TODO:尾を引くように

    //通常移動
    if (_pPrg->get() == ITEM_PROG_DRIFT) {
        //onHit() で状態変化するのを待つ
    }

    //自機と当たり判定がヒットし、自機に向かう動き
    if (_pPrg->get() == ITEM_PROG_ATTACH) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pPrg->isJustChanged()) {
            _pMvTransporter->setVxMvVelo(_pMvNavigator->_vX*_pMvNavigator->_veloMv);
            _pMvTransporter->setVyMvVelo(_pMvNavigator->_vY*_pMvNavigator->_veloMv);
            _pMvTransporter->setVzMvVelo(_pMvNavigator->_vZ*_pMvNavigator->_veloMv);
            _pMvTransporter->execGravitationVxyzMvSequence(pMyShip, 20000, 1000, 50000);
            _pMvNavigator->setMvVelo(0);
            _pMvNavigator->setMvAcce(0);
            _pMvNavigator->setMvVelo(5000);
        }
    }

    //自機に吸着し、吸収中の動き
    if (_pPrg->get() == ITEM_PROG_ABSORB) {
        MyShip* pMyShip = P_MYSHIP;
        if (_pPrg->isJustChanged()) {
            _pMvTransporter->setZeroVxyzMvVelo();
            _pMvTransporter->setZeroVxyzMvAcce();
            _pMvTransporter->stopGravitationVxyzMvSequence();
        }
        _X = pMyShip->_X + _kDX;
        _Y = pMyShip->_Y + _kDY;
        _Z = pMyShip->_Z + _kDZ;
        _SX -= 100;
        _SY -= 100;
        _SZ -= 100;
        if (_SX < 5) {
            _pSeTransmitter->playImmediately(0);
            _pPrg->change(ITEM_PROG_NOTIONG);
            sayonara(); //終了
        }
        P_MYSHIP_SCENE->_pEnagyBar->_amount.inc(1);
    }
    _pMvNavigator->behave();
    _pMvTransporter->behave();
}

void MagicPointItem001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
    //通常移動
    if (_pPrg->get() == ITEM_PROG_DRIFT) {
        //onHit() で状態変化するのを待つ
    }

    //自機と当たり判定がヒットし、自機に向かう動き
    if (_pPrg->get() == ITEM_PROG_ATTACH) {
        MyShip* pMyShip = P_MYSHIP;
        if (abs(pMyShip->_X - _X) < 20000 &&
            abs(pMyShip->_Y - _Y) < 20000 &&
            abs(pMyShip->_Z - _Z) < 20000 ) {
            //自機に吸着した
            _kDX = pMyShip->_X - _X;
            _kDY = pMyShip->_Y - _Y;
            _kDZ = pMyShip->_Z - _Z;
            _pPrg->change(ITEM_PROG_ABSORB);
        }
    }

    //自機に吸着し、吸収中の動き
    if (_pPrg->get() == ITEM_PROG_ABSORB) {
    }
}

void MagicPointItem001::onInactive() {
}

void MagicPointItem001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト


    if (_pPrg->get() == ITEM_PROG_DRIFT && pOther->getKind() & KIND_MY_BODY)  {
        setHitAble(false);
        _pPrg->change(ITEM_PROG_ATTACH);
    }

}

MagicPointItem001::~MagicPointItem001() {
}
