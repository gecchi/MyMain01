#include "TrialAndErrScene.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "actor/PointSpriteTest.h"
#include "actor/BoardTest.h"
#include "actor/Zako.h"
#include "actor/SmpActor.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

enum {
    PROG_INIT ,
    PROG_CALM ,
    PROG_WAIT ,
    PROG_BANPEI,
};

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    pTest_ = nullptr;

    orderActorToFactory(1234, SmpActor, "SmpActor");

//    for (int id = 0; id < 17; id++) {
//        orderActorToFactory(900+id, PointSpriteTest, "PointSpriteTest");
//    }
////    orderActorToFactory(990, PointSpriteTest, "PointSpriteTest1");
////    orderActorToFactory(991, PointSpriteTest, "PointSpriteTest2");
//    orderActorToFactory(10000, Zako, "Zako");
//    orderActorToFactory(993, PointSpriteTest, "PointSpriteTest4");
//    orderActorToFactory(994, PointSpriteTest, "PointSpriteTest5");
//    orderActorToFactory(995, PointSpriteTest, "PointSpriteTest6");
//    orderActorToFactory(996, PointSpriteTest, "PointSpriteTest7");
//    orderActorToFactory(20000, BoardTest, "BoardTest");
}

void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {

    if (getActiveFrame() == 100) {
        SmpActor* pSmpActor = (SmpActor*)obtainActorFromFactory(1234);
        bringSceneMediator()->addSubGroup(pSmpActor);

//        BoardTest* pBoardTest = (BoardTest*)obtainActorFromFactory(20000);
//        pBoardTest->setPosition(PX_C(100), PX_C(50));
//        bringSceneMediator()->addSubGroup(pBoardTest);


//        for (int id = 0; id < 17; id++) {
//            PointSpriteTest* pTest = (PointSpriteTest*)obtainActorFromFactory(900+id);
//            pTest->setPosition(PX_C(100*id), PX_C(100*id), PX_C(100*id));
//            bringSceneMediator()->addSubGroup(pTest);
//        }
    }
//    if (getActiveFrame() == 120) {
//        PointSpriteTest* pTest1 = (PointSpriteTest*)obtainActorFromFactory(990);
//        bringSceneMediator()->addSubGroup(pTest1);
//        pTest1->setPosition(0,0,0);
//    }
//    if (getActiveFrame() == 140) {
//        PointSpriteTest* pTest2 = (PointSpriteTest*)obtainActorFromFactory(991);
//        bringSceneMediator()->addSubGroup(pTest2);
//        pTest2->setPosition(PX_C(200), PX_C(200), PX_C(200));
//    }
//    if (getActiveFrame() == 160) {
//        Zako* pZako = (Zako*)obtainActorFromFactory(10000);
//        bringSceneMediator()->addSubGroup(pZako);
//        pZako->setPosition(PX_C(400), PX_C(400), PX_C(400));
//    }
//    if (getActiveFrame() == 180) {
//        PointSpriteTest* pTest4 = (PointSpriteTest*)obtainActorFromFactory(993);
//        bringSceneMediator()->addSubGroup(pTest4);
//        pTest4->setPosition(PX_C(600), PX_C(600), PX_C(600));
//    }
//    if (getActiveFrame() == 200) {
//        PointSpriteTest* pTest5 = (PointSpriteTest*)obtainActorFromFactory(994);
//        bringSceneMediator()->addSubGroup(pTest5);
//        pTest5->setPosition(PX_C(800), PX_C(800), PX_C(800));
//    }
//    if (getActiveFrame() == 220) {
//        PointSpriteTest* pTest6 = (PointSpriteTest*)obtainActorFromFactory(995);
//        bringSceneMediator()->addSubGroup(pTest6);
//        pTest6->setPosition(PX_C(1000), PX_C(1000), PX_C(1000));
//    }
//    if (getActiveFrame() == 240) {
//        PointSpriteTest* pTest7 = (PointSpriteTest*)obtainActorFromFactory(996);
//        bringSceneMediator()->addSubGroup(pTest7);
//        pTest7->setPosition(PX_C(1200), PX_C(1200), PX_C(1200));
//    }
}

TrialAndErrScene::~TrialAndErrScene() {
}
