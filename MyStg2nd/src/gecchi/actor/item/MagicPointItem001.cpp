#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MagicPointItem001::MagicPointItem001(const char* prm_name)
               : Item(prm_name, "vic2") {
    _class_name = "MagicPointItem001";
    MyStgUtil::resetMagicPointItem001Status(_pStatus);
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り

    _SX = _SY = _SZ = 100;
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

    _pKuroko->setMvAng(P_MYSHIP);
    _pKuroko->setFaceAngVelo(AXIS_X, 1000);
    _pKuroko->setMvVelo(2000);
    _pKuroko->setMvAcce(10);
    _pKuroko->forceMvVeloRange(0, 5000);
    _pKuroko->forceVxMvVeloRange(-20000, 20000);
    _pKuroko->forceVyMvVeloRange(-20000, 20000);
    _pKuroko->forceVzMvVeloRange(-20000, 20000);

    _pKuroko->setVxMvVelo(0);
    _pKuroko->setVyMvVelo(0);
    _pKuroko->setVzMvVelo(0);
    _pKuroko->setVxMvAcce(0);
    _pKuroko->setVyMvAcce(0);
    _pKuroko->setVzMvAcce(0);
    _pProgress->change(0);
}
void MagicPointItem001::onActive() {
//    _pKuroko->setFaceAngVelo(AXIS_Y, 5*1000);
//    _pKuroko->setFaceAngVelo(AXIS_Z, 7*1000);
}

void MagicPointItem001::processBehavior() {
    if (_pProgress->get() == 0) {
        if (getActivePartFrame() < 60 && getActivePartFrame() % 10 == 0) {
            _pKuroko->orderTagettingMvAngSequence(P_MYSHIP,2000,2000,TURN_CLOSE_TO);
        }
        _pKuroko->behave();
    }
    if (_pProgress->get() == 1) {
        if (_pProgress->isJustChanged()) {
            _pKuroko->setMvVelo(0);
            _pKuroko->setMvAcce(0);
        }
        float rate = 8.0 - 0.06*_pProgress->getChangedFrom(); //0.06 * 120 = 8.0
        rate = rate > 0 ? rate : 0;
        int fdx = P_MYSHIP->_X - (_X + _pKuroko->_veloVxMv*rate);
        int fdy = P_MYSHIP->_Y - (_Y + _pKuroko->_veloVyMv*rate);
        int fdz = P_MYSHIP->_Z - (_Z + _pKuroko->_veloVzMv*rate);
        _pKuroko->setVxMvAcce(fdx);
        _pKuroko->setVyMvAcce(fdy);
        _pKuroko->setVzMvAcce(fdz);

        _SX -= 1;
        _SY -= 1;
        _SZ -= 1;
        if (_SX < 10) {
            sayonara();
        }
        P_MYSHIP_SCENE->_pEnagyBar->_enagy += 1;
        _pKuroko->behave();
    }
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


    if (pOther->getKind() & KIND_MY_BODY)  {
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
