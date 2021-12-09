
#include "TrialAndErrScene.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "actor/PointSpriteTest.h"
#include "actor/BoardTest.h"
#include "actor/BoardTest2.h"
#include "actor/Zako.h"
#include "actor/SmpActor1.h"
#include "actor/SmpActor2.h"
#include "actor/SmpSprite.h"
#include "actor/SeActor3.h"
#include "actor/SmpPieGraphSprite.h"
#include "actor/EffectExplosion004.h"
#include "actor/AniTest.h"
#include "actor/AniTest2.h"
#include "actor/AniTest3.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"

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
    requestActor(1234, AniTest3, "AniTest1-1");
    requestActor(1235, AniTest3, "AniTest1-2");
//    requestActor(1236, AniTest3, "AniTest1-3");
//    requestActor(1237, AniTest2, "AniTest2-1");
//    requestActor(1238, AniTest2, "AniTest2-2");
//    requestActor(1239, AniTest2, "AniTest2-3");
}


void TrialAndErrScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {
    static AniTest3* p1 = nullptr;
    static AniTest3* p2 = nullptr;
//    static AniTest3* p3 = nullptr;
//    static AniTest2* p4 = nullptr;
//    static AniTest2* p5 = nullptr;
//    static AniTest2* p6 = nullptr;
    if (getActiveFrame() == 200) {
        p1 = (AniTest3*)receiveActor(1234);
        bringSceneMediator()->appendGroupChild(p1);
        p1->setPosition(PX_C(-200), PX_C(0), 0);
        p1->_pPuppeteer->stop();
//        p1->setRxFaceAng(D_ANG(-90));
//        p1->getVecDriver()->setRyFaceAngVelo(D_ANG(0.5));

        p2 = (AniTest3*)receiveActor(1235);
        bringSceneMediator()->appendGroupChild(p2);
        p2->setPosition(PX_C(0), PX_C(0), 0);
        p2->_pPuppeteer->stop();
//        p2->setRxFaceAng(D_ANG(-90));
//        p2->getVecDriver()->setRyFaceAngVelo(D_ANG(-1));
//
//        p3 = (AniTest3*)receiveActor(1236);
//        bringSceneMediator()->appendGroupChild(p3);
//        p3->setPosition(PX_C(200), PX_C(-250), 0);
//        p3->_pPuppeteer->stop();
//        p3->setRxFaceAng(D_ANG(-90));
//        p3->getVecDriver()->setRyFaceAngVelo(D_ANG(0.5));

//        p4 = (AniTest2*)receiveActor(1237);
//        bringSceneMediator()->appendGroupChild(p4);
//        p4->setPosition(PX_C(-200), PX_C(-50), 0);
//        p4->_pPuppeteer->stop();
//
//        p5 = (AniTest2*)receiveActor(1238);
//        bringSceneMediator()->appendGroupChild(p5);
//        p5->setPosition(0, PX_C(-50), 0);
//        p5->_pPuppeteer->stop();
//
//        p6 = (AniTest2*)receiveActor(1239);
//        bringSceneMediator()->appendGroupChild(p6);
//        p6->setPosition(PX_C(200), PX_C(-50), 0);
//        p6->_pPuppeteer->stop();
    }


    if (GgafDx::Input::isPushedDownKey(DIK_2)) {
        p1->_pPuppeteer->play(0);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_3)) {
        p1->_pPuppeteer->play(1);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_4)) {
        p1->_pPuppeteer->play(2);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_5)) {
        p1->_pPuppeteer->play(3);
    }
//    if (GgafDx::Input::isPushedDownKey(DIK_6)) {
//        p1->_pPuppeteer->play(4);
//    }

    if (GgafDx::Input::isPushedDownKey(DIK_W)) {
        p1->_pPuppeteer->playPartly(0);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_E)) {
        p1->_pPuppeteer->shiftTo(1);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_R)) {
        p1->_pPuppeteer->shiftTo(2);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_T)) {
        p1->_pPuppeteer->shiftTo(3);
    }
//    if (GgafDx::Input::isPushedDownKey(DIK_Y)) {
//        p1->_pPuppeteer->shiftTo(4);
//    }


////////////////////////


    if (GgafDx::Input::isPushedDownKey(DIK_A)) {
        p2->_pPuppeteer->play(0);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_S)) {
        p2->_pPuppeteer->play(1);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_D)) {
        p2->_pPuppeteer->play(2);
    }
    if (GgafDx::Input::isPushedDownKey(DIK_F)) {
        p2->_pPuppeteer->play(3);
    }
//    if (GgafDx::Input::isPushedDownKey(DIK_G)) {
//        p2->_pPuppeteer->play(4);
//    }

    if (GgafDx::Input::isPushedDownKey(DIK_Z)) {
         p2->_pPuppeteer->playPartly(0);
     }
     if (GgafDx::Input::isPushedDownKey(DIK_X)) {
         p2->_pPuppeteer->shiftTo(1);
     }
     if (GgafDx::Input::isPushedDownKey(DIK_C)) {
         p2->_pPuppeteer->shiftTo(2);
     }
     if (GgafDx::Input::isPushedDownKey(DIK_V)) {
         p2->_pPuppeteer->shiftTo(3);
     }
//     if (GgafDx::Input::isPushedDownKey(DIK_B)) {
//         p2->_pPuppeteer->shiftTo(4);
//     }

}

TrialAndErrScene::~TrialAndErrScene() {
}

