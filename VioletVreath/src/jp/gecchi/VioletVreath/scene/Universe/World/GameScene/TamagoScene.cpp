#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TamagoScene::TamagoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TamagoScene";

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

//    _pTurboMeter001 = NEW TurboMeter("TurboMeter001");
//    _pTurboMeter001->locate(16 , CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 64);
//    getDirector()->addSubGroup(_pTurboMeter001);
//
//    orderActorToFactory(100000001, EnemyVesta, "EnemyVesta1");
//    orderActorToFactory(100000002, EnemyVesta, "EnemyVesta2");
//    orderActorToFactory(100000003, EnemyVesta, "EnemyVesta3");
//    orderActorToFactory(100000004, EnemyVesta, "EnemyVesta4");
//    orderActorToFactory(100000005, EnemyVesta, "EnemyVesta5");
//    orderActorToFactory(100000006, EnemyVesta, "EnemyVesta6");
//    orderActorToFactory(100000009, EnemyCirce, "EnemyCirce");

//    orderActorToFactory(100000001, FormationJuno001, "FormationJuno001");
//    orderActorToFactory(900000001, VarietyTorus001, "Torus001");
}

void TamagoScene::onReset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
//    if (getActivePartFrame() == 60) {
//        VarietyTorus001* p = (VarietyTorus001*)obtainActorFromFactory(900000001);
//        getDirector()->addSubGroup(p);
//    }

//    if (getActivePartFrame() == 120) {
//        FormationJuno001* p = (FormationJuno001*)obtainActorFromFactory(100000001);
//        getDirector()->addSubGroup(p);
//    }
//    if (getActivePartFrame() == 120) {
//
//        EnemyVesta* p1 = (EnemyVesta*)obtainActorFromFactory(100000001);
//        EnemyVesta* p2 = (EnemyVesta*)obtainActorFromFactory(100000002);
//        EnemyVesta* p3 = (EnemyVesta*)obtainActorFromFactory(100000003);
//        EnemyVesta* p4 = (EnemyVesta*)obtainActorFromFactory(100000004);
//        EnemyVesta* p5 = (EnemyVesta*)obtainActorFromFactory(100000005);
//        EnemyVesta* p6 = (EnemyVesta*)obtainActorFromFactory(100000006);
//
//        EnemyCirce* p9 = (EnemyCirce*)obtainActorFromFactory(100000009);
//        p9->locate(80000,50000,50000);
//        p9->addSubBone(p1,       0,       0,  300000, D0ANG,   D0ANG, D270ANG);
//        p9->addSubBone(p2,  300000,       0,       0, D0ANG,   D0ANG, D0ANG);
//        p9->addSubBone(p3,       0,       0, -300000, D0ANG,   D0ANG, D90ANG);
//        p9->addSubBone(p4, -300000,       0,       0, D0ANG,   D0ANG, D180ANG);
//        p9->addSubBone(p5,       0,  300000,       0, D0ANG,  D90ANG, D0ANG);
//        p9->addSubBone(p6,       0, -300000,       0, D0ANG, D270ANG, D0ANG);
//
//        getDirector()->addSubGroup(p9);
//
//    }
//    for (int i = 1; i <= 1; i++) {
//        if (getBehaveingFrame() == (i*8)) {
//            HoshiBoshi001* p = (HoshiBoshi001*)(obtainActorFromFactory(100000000+i));
//            p->locate(0,0,0);
//            getDirector()->addSubGroup(p);
//        }
//    }



}

TamagoScene::~TamagoScene() {
}
