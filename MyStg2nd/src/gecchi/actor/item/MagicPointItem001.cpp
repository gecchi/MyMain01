#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MagicPointItem001::MagicPointItem001(const char* prm_name)
               : Item(prm_name, "MagicPointItem001") {
    _class_name = "MagicPointItem001";
    MyStgUtil::resetMagicPointItem001Status(_pStatus);
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
    _pKuroko->setFaceAngVelo(AXIS_X, 3*1000);
    _pKuroko->setFaceAngVelo(AXIS_Y, 5*1000);
    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
}

void MagicPointItem001::initialize() {
    setHitAble(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 200000);
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "yume_ashi_022");
    useProgress(3);
}

void MagicPointItem001::onReset() {
    MyStgUtil::resetMagicPointItem001Status(_pStatus);
    setHitAble(true);
    CmRandomNumberGenerator* pRndGen = CmRandomNumberGenerator::getInstance();
    _pKuroko->setMvAng(
            P_MYSHIP->_X + (pRndGen->genrand_int32() % 300000) - 100000,
            P_MYSHIP->_Y + (pRndGen->genrand_int32() % 300000) - 100000,
            P_MYSHIP->_Z + (pRndGen->genrand_int32() % 300000) - 100000
    );
    _pKuroko->setMvVelo(1000);
    _pKuroko->setMvAcce(100);
    _pKuroko->forceMvVeloRange(0, 20000);
    _pKuroko->forceVxMvVeloRange(-20000, 20000);
    _pKuroko->forceVyMvVeloRange(-20000, 20000);
    _pKuroko->forceVzMvVeloRange(-20000, 20000);
    _pKuroko->setVxMvVelo(0);
    _pKuroko->setVyMvVelo(0);
    _pKuroko->setVzMvVelo(0);
    _pKuroko->setVxMvAcce(0);
    _pKuroko->setVyMvAcce(0);
    _pKuroko->setVzMvAcce(0);
    _pKuroko->_gravitation_mv_seq_flg = false;
    _pProgress->change(0);
}
void MagicPointItem001::onActive() {
//    _pKuroko->setFaceAngVelo(AXIS_Y, 5*1000);
//    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
}

void MagicPointItem001::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    if (_pProgress->get() == 0) {
//        if (getActivePartFrame() < 60 && getActivePartFrame() % 10 == 0) {
//            _pKuroko->orderTagettingMvAngSequence(P_MYSHIP,2000,2000,TURN_CLOSE_TO);
//        }
    }
    if (_pProgress->get() == 1) {
        if (_pProgress->isJustChanged()) {
            _pKuroko->setVxMvVelo(_pKuroko->_vX*_pKuroko->_veloMv);
            _pKuroko->setVyMvVelo(_pKuroko->_vY*_pKuroko->_veloMv);
            _pKuroko->setVzMvVelo(_pKuroko->_vZ*_pKuroko->_veloMv);
            _pKuroko->setMvVelo(0);
            _pKuroko->setMvAcce(0);
            _pKuroko->orderGravitationMvSequence(
                    pMyShip, 20000, 1000, 100000);
        }

        if (abs(_X - pMyShip->_X) < 2000 &&
            abs(_Y - pMyShip->_Y) < 2000 &&
            abs(_Z - pMyShip->_Z) < 2000 ) {
            _pProgress->change(2);
        }
    }

    if (_pProgress->get() == 2) {
        if (_pProgress->isJustChanged()) {
            _pKuroko->setVxMvVelo(0);
            _pKuroko->setVyMvVelo(0);
            _pKuroko->setVzMvVelo(0);
            _pKuroko->_gravitation_mv_seq_flg = false;
        }
        _X = pMyShip->_X;
        _Y = pMyShip->_Y;
        _Z = pMyShip->_Z;
        _SX -= 100;
        _SY -= 100;
        _SZ -= 100;
        if (_SX < 5) {
            sayonara();
        }
        P_MYSHIP_SCENE->_pEnagyBar->_enagy += 1;
    }
    _pKuroko->behave();
}

void MagicPointItem001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void MagicPointItem001::onInactive() {
}

void MagicPointItem001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト


    if (_pProgress->get() == 0 && pOther->getKind() & KIND_MY_BODY)  {
        setHitAble(false);
        _pProgress->change(1);
    }
//
//        P_MYSHIP_SCENE->_pEnagyBar->_enagy += 10;
//        _pSeTransmitter->playImmediately(0);
//        setHitAble(false);
//        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
//        if (pExplo001) {
//            pExplo001->locateWith(this);
//            pExplo001->activate();
//        }
//        sayonara();
//    }


}

MagicPointItem001::~MagicPointItem001() {
}
