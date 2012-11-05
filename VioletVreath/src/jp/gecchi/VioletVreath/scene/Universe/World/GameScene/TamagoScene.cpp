#include "stdafx.h"
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

//    pTurboMeter001_ = NEW TurboMeter("TurboMeter001");
//    pTurboMeter001_->locate(16 , GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 64);
//    getDirector()->addSubGroup(pTurboMeter001_);
//
//    orderActorToFactory(100000001, EnemyRomulus, "EnemyRomulus1");
//    orderActorToFactory(100000002, EnemyRomulus, "EnemyRomulus2");
//    orderActorToFactory(100000003, EnemyRomulus, "EnemyRomulus3");
//    orderActorToFactory(100000004, EnemyRomulus, "EnemyRomulus4");
//    orderActorToFactory(100000005, EnemyRomulus, "EnemyRomulus5");
//    orderActorToFactory(100000006, EnemyRomulus, "EnemyRomulus6");
//    orderActorToFactory(100000009, EnemyCirce, "EnemyCirce");

//    orderActorToFactory(100000001, FormationJuno001, "FormationJuno001");
//    orderActorToFactory(900000001, VarietySylvia001, "EnemySylvia001");
}

void TamagoScene::onReset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
//    if (getActivePartFrame() == 60) {
//        VarietySylvia001* p = (VarietySylvia001*)obtainActorFromFactory(900000001);
//        getDirector()->addSubGroup(p);
//    }

//    if (getActivePartFrame() == 120) {
//        FormationJuno001* p = (FormationJuno001*)obtainActorFromFactory(100000001);
//        getDirector()->addSubGroup(p);
//    }
//    if (getActivePartFrame() == 120) {
//
//        EnemyRomulus* p1 = (EnemyRomulus*)obtainActorFromFactory(100000001);
//        EnemyRomulus* p2 = (EnemyRomulus*)obtainActorFromFactory(100000002);
//        EnemyRomulus* p3 = (EnemyRomulus*)obtainActorFromFactory(100000003);
//        EnemyRomulus* p4 = (EnemyRomulus*)obtainActorFromFactory(100000004);
//        EnemyRomulus* p5 = (EnemyRomulus*)obtainActorFromFactory(100000005);
//        EnemyRomulus* p6 = (EnemyRomulus*)obtainActorFromFactory(100000006);
//
//        EnemyCirce* p9 = (EnemyCirce*)obtainActorFromFactory(100000009);
//        p9->locate(80000,50000,50000);
//        p9->addSubGroupAsFk(p1,       0,       0,  300000, D0ANG, D270ANG,  D0ANG);
//        p9->addSubGroupAsFk(p2,  300000,       0,       0, D0ANG, D0ANG,  D0ANG);
//        p9->addSubGroupAsFk(p3,       0,       0, -300000, D0ANG, D90ANG,  D0ANG);
//        p9->addSubGroupAsFk(p4, -300000,       0,       0, D0ANG, D180ANG,    D0ANG);
//        p9->addSubGroupAsFk(p5,       0,  300000,       0, D0ANG, D0ANG,     D90ANG);
//        p9->addSubGroupAsFk(p6,       0, -300000,       0, D0ANG, D0ANG,    D270ANG);
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
