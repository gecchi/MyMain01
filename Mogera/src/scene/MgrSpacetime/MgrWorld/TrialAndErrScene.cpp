
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
#include "actor/ItemBoardTest.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"


using namespace GgafLib;
using namespace Mogera;

enum {
    PHASE_INIT ,
    PHASE_CALM ,
    PHASE_WAIT ,
    PHASE_BANPEI,
};


TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    requestActor(2000, SmpActor2, "SmpActor2");
    requestActor(3000, ItemBoardTest, "ItemBoardTest");
}


void TrialAndErrScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {
    static SmpActor2* pSmpActor2 = nullptr;
    static ItemBoardTest* pItemBoardTest = nullptr;

    if (hasJustChangedToActive()) {

        pSmpActor2 = (SmpActor2*)receiveActor(2000);
        bringSceneMediator()->appendGroupChild(MGR_MIKATA, pSmpActor2);
        pSmpActor2->setPosition(0, 0, 0);


        pItemBoardTest = (ItemBoardTest*)receiveActor(3000);
        bringSceneMediator()->appendGroupChild(MGR_MIKATA, pItemBoardTest);
        pItemBoardTest->setPosition(PX_C(100), PX_C(200));


    }
}

TrialAndErrScene::~TrialAndErrScene() {
}

