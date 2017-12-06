#include "TamagoScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"

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

//
//    orderActorToFactory(100000001, EnemyOmulus, "EnemyOmulus1");
//    orderActorToFactory(100000002, EnemyOmulus, "EnemyOmulus2");
//    orderActorToFactory(100000003, EnemyOmulus, "EnemyOmulus3");
//    orderActorToFactory(100000004, EnemyOmulus, "EnemyOmulus4");
//    orderActorToFactory(100000005, EnemyOmulus, "EnemyOmulus5");
//    orderActorToFactory(100000006, EnemyOmulus, "EnemyOmulus6");
//    orderActorToFactory(100000009, EnemyIrce, "EnemyIrce");

//    orderActorToFactory(100000001, FormationGeria001, "FormationGeria001");
//    orderActorToFactory(900000001, VarietyRatislavia001, "EnemyRatislavia001");
}

void TamagoScene::onReset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
//    if (getActiveFrame() == 60) {
//        VarietyRatislavia001* p = (VarietyRatislavia001*)obtainActorFromFactory(900000001);
//        bringSceneMediator()->addSubGroup(p);
//    }

//    if (getActiveFrame() == 120) {
//        FormationGeria001* p = (FormationGeria001*)obtainActorFromFactory(100000001);
//        bringSceneMediator()->addSubGroup(p);
//    }
//    if (getActiveFrame() == 120) {
//
//        EnemyOmulus* p1 = (EnemyOmulus*)obtainActorFromFactory(100000001);
//        EnemyOmulus* p2 = (EnemyOmulus*)obtainActorFromFactory(100000002);
//        EnemyOmulus* p3 = (EnemyOmulus*)obtainActorFromFactory(100000003);
//        EnemyOmulus* p4 = (EnemyOmulus*)obtainActorFromFactory(100000004);
//        EnemyOmulus* p5 = (EnemyOmulus*)obtainActorFromFactory(100000005);
//        EnemyOmulus* p6 = (EnemyOmulus*)obtainActorFromFactory(100000006);
//
//        EnemyIrce* p9 = (EnemyIrce*)obtainActorFromFactory(100000009);
//        p9->setPosition(80000,50000,50000);
//        p9->addSubGroupAsFk(p1,       0,       0,  300000, D0ANG, D270ANG,  D0ANG);
//        p9->addSubGroupAsFk(p2,  300000,       0,       0, D0ANG, D0ANG,  D0ANG);
//        p9->addSubGroupAsFk(p3,       0,       0, -300000, D0ANG, D90ANG,  D0ANG);
//        p9->addSubGroupAsFk(p4, -300000,       0,       0, D0ANG, D180ANG,    D0ANG);
//        p9->addSubGroupAsFk(p5,       0,  300000,       0, D0ANG, D0ANG,     D90ANG);
//        p9->addSubGroupAsFk(p6,       0, -300000,       0, D0ANG, D0ANG,    D270ANG);
//
//        bringSceneMediator()->addSubGroup(p9);
//
//    }
//    for (int i = 1; i <= 1; i++) {
//        if (getBehaveingFrame() == (i*8)) {
//            HoshiBoshi001* p = (HoshiBoshi001*)(obtainActorFromFactory(100000000+i));
//            p->setPosition(0,0,0);
//            bringSceneMediator()->addSubGroup(p);
//        }
//    }



}

TamagoScene::~TamagoScene() {
}
