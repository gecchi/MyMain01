
#include "TrialAndErrScene.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/lib/util/ViewCollisionChecker.h"
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
#include "actor/ItemBoardTest.h"
#include "actor/LabelMenuItemFont01.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"


using namespace GgafLib;
using namespace Mogera;

enum {
    PHASE_INIT ,
    PHASE_CALM ,
    PHASE_WAIT ,
    PHASE_BANPEI,
};
#define NN 1

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";

    for (int i = 0; i < NN; i++) {
        requestActor(1000+i, EffectExplosion004, "EffectExplosion004");
    }
//    requestActor(3000, ItemBoardTest, "ItemBoardTest");
//    requestActor(4000, LabelMenuItemFont01, "LabelMenuItemFont01");
//    requestActor(5000, AniTest, "AniTest1-1");
}


void TrialAndErrScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {
//    static ItemBoardTest* pItemBoardTest = nullptr;
//    static LabelMenuItemFont01* pLabelMenuItemFont01 = nullptr;

//    static AniTest* p1 = nullptr;

    static EffectExplosion004* aA[NN];

    if (hasJustChangedToActive()) {
//        p1 = (AniTest*)receiveActor(5000);
//        getSceneChief()->appendChild(p1);

        for (int i = 0; i < NN; i++) {
            aA[i] = (EffectExplosion004*)receiveActor(1000+i);
            aA[i]->setDefaultKind(MGR_MIKATA);
            getSceneChief()->appendChild(aA[i]);
            aA[i]->setPosition(PX_C(-200) + PX_C(i)*20, 0, 0);
        }


//        pItemBoardTest = (ItemBoardTest*)receiveActor(3000);
//        getSceneChief()->appendChild(MGR_MIKATA, pItemBoardTest);
//        pItemBoardTest->setPosition(PX_C(100), PX_C(200));
//
//        pLabelMenuItemFont01 = (LabelMenuItemFont01*)receiveActor(4000);
//        pLabelMenuItemFont01->update("AAAAAA\r\nBBBBBBB");
//        pLabelMenuItemFont01->getViewCollisionChecker()->addCollisionArea(1);
//        pLabelMenuItemFont01->getViewCollisionChecker()->setColliAABox(0, 0.8);
//        pLabelMenuItemFont01->setHitAble(true);
//        getSceneChief()->appendChild(MGR_MIKATA, pLabelMenuItemFont01);
//        pLabelMenuItemFont01->setPosition(PX_C(300), PX_C(250));
    }
    if (GgafDx::Input::isPressedKey(DIK_C)) {
         aA[0]->changeModel("EffectExplosion001");
    }
    if (GgafDx::Input::isPressedKey(DIK_B)) {
         aA[0]->changeDefaultModel();
    }

}

TrialAndErrScene::~TrialAndErrScene() {
}

