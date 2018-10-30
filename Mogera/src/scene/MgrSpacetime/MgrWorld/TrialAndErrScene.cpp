
#include "TrialAndErrScene.h"

#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "actor/PointSpriteTest.h"
#include "actor/BoardTest.h"
#include "actor/BoardTest2.h"
#include "actor/Zako.h"
#include "actor/SmpActor1.h"
#include "actor/SmpActor2.h"
#include "actor/SmpSprite.h"
#include "actor/SmpPieGraphSprite.h"
#include "actor/EffectExplosion004.h"
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


//    requestActor(1111, SmpActor1, "SmpActor1");
//    requestActor(2222, SmpActor2, "SmpActor2");
    requestActor(3333, SmpSprite);
      requestActor(6666, SmpPieGraphSprite);

//    for (int id = 0; id < 17; id++) {
//        requestActor(900+id, PointSpriteTest, "PointSpriteTest");
//    }
////    requestActor(990, PointSpriteTest, "PointSpriteTest1");
////    requestActor(991, PointSpriteTest, "PointSpriteTest2");
//    requestActor(10000, Zako, "Zako");
//    requestActor(993, PointSpriteTest, "PointSpriteTest4");
//    requestActor(994, PointSpriteTest, "PointSpriteTest5");
//    requestActor(995, PointSpriteTest, "PointSpriteTest6");
//    requestActor(996, PointSpriteTest, "PointSpriteTest7");
//    requestActor(20000, BoardTest, "BoardTest");
      requestActor(20000, BoardTest2, "BoardTest2");
}


void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {

//    if (GgafDxInput::isPressedKey(DIK_L)) {
//        EffectExplosion004* p = desireActor(EffectExplosion004);
//        bringSceneMediator()->appendGroupChild(MGR_TEKI, p);
//    }

    if (getActiveFrame() == 100) {
        SmpPieGraphSprite* pSmpPieGraphSprite = (SmpPieGraphSprite*)receiveActor(6666);
        pSmpPieGraphSprite->setPosition(0, 0, 0);
        bringSceneMediator()->appendGroupChild(MGR_TEKI, pSmpPieGraphSprite);

        BoardTest2* pBoardTest2 = (BoardTest2*)receiveActor(20000);
        pBoardTest2->setPosition(PX_C(50), PX_C(50), 0);
        bringSceneMediator()->appendGroupChild(MGR_TEKI, pBoardTest2);

//        SmpActor1* pSmpActor1 = (SmpActor1*)receiveActor(1111);
//        bringSceneMediator()->appendGroupChild(MGR_MIKATA, pSmpActor1);
//        pSmpActor1->setPosition(PX_C(50), PX_C(+200), PX_C(50));
//
//        SmpActor2* pSmpActor2 = (SmpActor2*)receiveActor(2222);
//        bringSceneMediator()->appendGroupChild(MGR_TEKI, pSmpActor2);
//        pSmpActor2->setPosition(PX_C(50), PX_C(50), PX_C(50));

//        BoardTest* pBoardTest = (BoardTest*)receiveActor(20000);
//        pBoardTest->setPosition(PX_C(100), PX_C(50));
//        bringSceneMediator()->appendGroupChild(pBoardTest);

        SmpSprite* pSmpSprite = (SmpSprite*)receiveActor(3333);
        bringSceneMediator()->appendGroupChild(MGR_TEKI, pSmpSprite);
        pSmpSprite->setPosition(PX_C(50), PX_C(-50), 0);

//        for (int id = 0; id < 17; id++) {
//            PointSpriteTest* pTest = (PointSpriteTest*)receiveActor(900+id);
//            pTest->setPosition(PX_C(100*id), PX_C(100*id), PX_C(100*id));
//            bringSceneMediator()->appendGroupChild(pTest);
//        }
    }
//    if (getActiveFrame() == 120) {
//        PointSpriteTest* pTest1 = (PointSpriteTest*)receiveActor(990);
//        bringSceneMediator()->appendGroupChild(pTest1);
//        pTest1->setPosition(0,0,0);
//    }
//    if (getActiveFrame() == 140) {
//        PointSpriteTest* pTest2 = (PointSpriteTest*)receiveActor(991);
//        bringSceneMediator()->appendGroupChild(pTest2);
//        pTest2->setPosition(PX_C(200), PX_C(200), PX_C(200));
//    }
//    if (getActiveFrame() == 160) {
//        Zako* pZako = (Zako*)receiveActor(10000);
//        bringSceneMediator()->appendGroupChild(pZako);
//        pZako->setPosition(PX_C(400), PX_C(400), PX_C(400));
//    }
//    if (getActiveFrame() == 180) {
//        PointSpriteTest* pTest4 = (PointSpriteTest*)receiveActor(993);
//        bringSceneMediator()->appendGroupChild(pTest4);
//        pTest4->setPosition(PX_C(600), PX_C(600), PX_C(600));
//    }
//    if (getActiveFrame() == 200) {
//        PointSpriteTest* pTest5 = (PointSpriteTest*)receiveActor(994);
//        bringSceneMediator()->appendGroupChild(pTest5);
//        pTest5->setPosition(PX_C(800), PX_C(800), PX_C(800));
//    }
//    if (getActiveFrame() == 220) {
//        PointSpriteTest* pTest6 = (PointSpriteTest*)receiveActor(995);
//        bringSceneMediator()->appendGroupChild(pTest6);
//        pTest6->setPosition(PX_C(1000), PX_C(1000), PX_C(1000));
//    }
//    if (getActiveFrame() == 240) {
//        PointSpriteTest* pTest7 = (PointSpriteTest*)receiveActor(996);
//        bringSceneMediator()->appendGroupChild(pTest7);
//        pTest7->setPosition(PX_C(1200), PX_C(1200), PX_C(1200));
//    }
}


TrialAndErrScene::~TrialAndErrScene() {
}
