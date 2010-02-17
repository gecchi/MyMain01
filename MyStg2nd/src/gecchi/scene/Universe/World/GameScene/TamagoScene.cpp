#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoScene::TamagoScene(const char* prm_name) : DefaultScene(prm_name) {
    orderActorToFactory(100000001, EnemyTamago01, "gyoku1");
    orderActorToFactory(100000002, EnemyTamago01, "gyoku2");
    orderActorToFactory(100000003, EnemyTamago01, "gyoku3");
    orderActorToFactory(100000004, EnemyTamago01, "gyoku4");
    orderActorToFactory(100000005, EnemyTamago01, "gyoku5");
    orderActorToFactory(100000006, EnemyTamago01, "gyoku6");
    orderActorToFactory(100000007, EnemyTamago01, "gyoku7");
    orderActorToFactory(100000008, EnemyTamago01, "gyoku8");
    orderActorToFactory(100000009, EnemyTamago01, "gyoku9");
    orderActorToFactory(100000010, EnemyTamago01, "gyoku10");
    orderActorToFactory(100000011, EnemyTamago01, "gyoku11");
    orderActorToFactory(100000012, EnemyTamago01, "gyoku12");
    orderActorToFactory(100000013, EnemyTamago01, "gyoku13");
    orderActorToFactory(100000014, EnemyTamago01, "gyoku14");
    orderActorToFactory(100000015, EnemyTamago01, "gyoku15");
    orderActorToFactory(100000016, EnemyTamago01, "gyoku16");

    _pTurboMeter001 = NEW TurboMeter("TurboMeter001");
    _pTurboMeter001->setGeometry(50, 50);
    getLordActor()->addSubGroup(_pTurboMeter001);
    _pTurboMeter002 = NEW TurboMeter("TurboMeter002");
    _pTurboMeter002->setGeometry(200, 200);
    _pTurboMeter002->_pUvFlipper->setPtnNo(15);
    getLordActor()->addSubGroup(_pTurboMeter002);
}

void TamagoScene::reset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
//    if (getBehaveingFrame() == 1) {
//        orderActorToFactory(100000001, EnemyTamago01, "gyoku");
//    }
    for (int i = 1; i <= 16; i++) {
        if (getBehaveingFrame() == (i*8)) {
            EnemyTamago01* p = (EnemyTamago01*)(obtainActorFromFactory(100000000+i));
            p->setGeometry(i*100000,0,0);
            getLordActor()->addSubGroup(p);
        }
    }
}

void TamagoScene::processFinal() {
}

TamagoScene::~TamagoScene() {
}
