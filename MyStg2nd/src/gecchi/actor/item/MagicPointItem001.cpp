#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MagicPointItem001::MagicPointItem001(const char* prm_name)
               : Item(prm_name, "vic2") {
    _class_name = "MagicPointItem001";
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り

    _SX = _SY = _SZ = 100;
    _pMover->relateRzRyFaceAngToMvAng(true);
}

void MagicPointItem001::initialize() {


}

void MagicPointItem001::onReset() {
    setHitAble(true);
    _pMover->setMvAng(P_MYSHIP);
    _pMover->setFaceAngVelo(AXIS_X, 1000);
    _pMover->setMvVelo(2000);
    _pMover->setMvAcce(10);
    _pMover->forceMvVeloRange(0, 5000);
}
void MagicPointItem001::onActive() {
//    _pMover->setFaceAngVelo(AXIS_Y, 5*1000);
//    _pMover->setFaceAngVelo(AXIS_Z, 7*1000);
}

void MagicPointItem001::processBehavior() {
    if (getActivePartFrame() < 60 && getActivePartFrame() % 10 == 0) {
        _pMover->execTagettingMvAngSequence(P_MYSHIP,2000,2000,TURN_CLOSE_TO);
    }
    _pMover->behave();
}

void MagicPointItem001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void MagicPointItem001::onInactive() {
}

MagicPointItem001::~MagicPointItem001() {
}
