#include "TamagoScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TamagoScene::TamagoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TamagoScene";

    //wishActor(100000001, HoshiBoshi001, "HoshiBoshi001");
//    wishActor(100000002, EnemyTamago01, "gyoku2");
//    wishActor(100000003, EnemyTamago01, "gyoku3");
//    wishActor(100000004, EnemyTamago01, "gyoku4");
//    wishActor(100000005, EnemyTamago01, "gyoku5");
//    wishActor(100000006, EnemyTamago01, "gyoku6");
//    wishActor(100000007, EnemyTamago01, "gyoku7");
//    wishActor(100000008, EnemyTamago01, "gyoku8");
//    wishActor(100000009, EnemyTamago01, "gyoku9");
//    wishActor(100000010, EnemyTamago01, "gyoku10");
//    wishActor(100000011, EnemyTamago01, "gyoku11");
//    wishActor(100000012, EnemyTamago01, "gyoku12");
//    wishActor(100000013, EnemyTamago01, "gyoku13");
//    wishActor(100000014, EnemyTamago01, "gyoku14");
//    wishActor(100000015, EnemyTamago01, "gyoku15");
//    wishActor(100000016, EnemyTamago01, "gyoku16");

//
//    wishActor(100000001, EnemyOmulus, "EnemyOmulus1");
//    wishActor(100000002, EnemyOmulus, "EnemyOmulus2");
//    wishActor(100000003, EnemyOmulus, "EnemyOmulus3");
//    wishActor(100000004, EnemyOmulus, "EnemyOmulus4");
//    wishActor(100000005, EnemyOmulus, "EnemyOmulus5");
//    wishActor(100000006, EnemyOmulus, "EnemyOmulus6");
//    wishActor(100000009, EnemyIrce, "EnemyIrce");

//    wishActor(100000001, FormationGeria001, "FormationGeria001");
//    wishActor(900000001, VarietyRatislavia001, "EnemyRatislavia001");
}

void TamagoScene::onReset() {
}
void TamagoScene::ready() {
}

void TamagoScene::initialize() {
}

void TamagoScene::processBehavior() {
//    if (getActiveFrame() == 60) {
//        VarietyRatislavia001* p = (VarietyRatislavia001*)receiveActor(900000001);
//        bringSceneMediator()->addSubGroup(p);
//    }

//    if (getActiveFrame() == 120) {
//        FormationGeria001* p = (FormationGeria001*)receiveActor(100000001);
//        bringSceneMediator()->addSubGroup(p);
//    }
//    if (getActiveFrame() == 120) {
//
//        EnemyOmulus* p1 = (EnemyOmulus*)receiveActor(100000001);
//        EnemyOmulus* p2 = (EnemyOmulus*)receiveActor(100000002);
//        EnemyOmulus* p3 = (EnemyOmulus*)receiveActor(100000003);
//        EnemyOmulus* p4 = (EnemyOmulus*)receiveActor(100000004);
//        EnemyOmulus* p5 = (EnemyOmulus*)receiveActor(100000005);
//        EnemyOmulus* p6 = (EnemyOmulus*)receiveActor(100000006);
//
//        EnemyIrce* p9 = (EnemyIrce*)receiveActor(100000009);
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
//            HoshiBoshi001* p = (HoshiBoshi001*)(receiveActor(100000000+i));
//            p->setPosition(0,0,0);
//            bringSceneMediator()->addSubGroup(p);
//        }
//    }



}

TamagoScene::~TamagoScene() {
}
