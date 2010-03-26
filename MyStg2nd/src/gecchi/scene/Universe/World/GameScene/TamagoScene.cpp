#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoScene::TamagoScene(const char* prm_name) : DefaultScene(prm_name) {
    //orderActorToFactory(100000001, HoshiBoshi001, "HoshiBoshi001");
//    orderActorToFactory(100000002, EnemyTamago01, "gyoku2");
//    orderActorToFactory(100000003, EnemyTamago01, "gyoku3");
//    orderActorToFactory(100000004, EnemyTamago01, "gyoku4");
//    orderActorToFactory(100000005, EnemyTamago01, "gyoku5");
//    orderActorToFactory(100000006, EnemyTamago01, "gyoku6");
//    orderActorToFactory(100000007, EnemyTamago01, "gyoku7");
//    orderActorToFactory(100000008, EnemyTamago01, "gyoku8");
//    orderActorToFactory(100000009, EnemyTamago01, "gyoku9");
//    orderActorToFactory(100000010, EnemyTamago01, "gyoku10");
//    orderActorToFactory(100000011, EnemyTamago01, "gyoku11");
//    orderActorToFactory(100000012, EnemyTamago01, "gyoku12");
//    orderActorToFactory(100000013, EnemyTamago01, "gyoku13");
//    orderActorToFactory(100000014, EnemyTamago01, "gyoku14");
//    orderActorToFactory(100000015, EnemyTamago01, "gyoku15");
//    orderActorToFactory(100000016, EnemyTamago01, "gyoku16");

    _pTurboMeter001 = NEW TurboMeter("TurboMeter001");
    _pTurboMeter001->setGeometry(16 , GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 64);
    getLordActor()->addSubGroup(_pTurboMeter001);



    orderActorToFactory(100000001, EnemyVesta, "EnemyVesta1");
    orderActorToFactory(100000002, EnemyVesta, "EnemyVesta2");
    orderActorToFactory(100000003, EnemyVesta, "EnemyVesta3");
    orderActorToFactory(100000009, EnemyCirce, "EnemyCirce");
}

void TamagoScene::reset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
    if (getPartFrame() == 60) {

        EnemyVesta* p1 = (EnemyVesta*)obtainActorFromFactory(100000001);
        p1->chengeGeoLocal();
        p1->setGeometry(-100000,10000,-100000);
        p1->chengeGeoFinal();
        EnemyVesta* p2 = (EnemyVesta*)obtainActorFromFactory(100000002);
        p2->chengeGeoLocal();
        p2->setGeometry(-100000,10000,0);
        p2->chengeGeoFinal();
        EnemyVesta* p3 = (EnemyVesta*)obtainActorFromFactory(100000003);
        p3->chengeGeoLocal();
        p3->setGeometry(-100000,10000,+100000);
        p3->chengeGeoFinal();


        EnemyCirce* p9 = (EnemyCirce*)obtainActorFromFactory(100000009);
        p9->setGeometry(80000,50000,50000);
        p1->_pActor_Foundation = p9;
        p2->_pActor_Foundation = p9;
        p3->_pActor_Foundation = p9;
        p9->addSubGroup(p1);
        p9->addSubGroup(p2);
        p9->addSubGroup(p3);
        getLordActor()->addSubGroup(p9);

    }
//    for (int i = 1; i <= 1; i++) {
//        if (getBehaveingFrame() == (i*8)) {
//            HoshiBoshi001* p = (HoshiBoshi001*)(obtainActorFromFactory(100000000+i));
//            p->setGeometry(0,0,0);
//            getLordActor()->addSubGroup(p);
//        }
//    }



}

void TamagoScene::processFinal() {
}

TamagoScene::~TamagoScene() {
}
