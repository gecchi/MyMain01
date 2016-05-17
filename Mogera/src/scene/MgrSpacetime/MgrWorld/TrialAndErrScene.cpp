#include "TrialAndErrScene.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "actor/PointSpriteTest.h"
#include "scene/MgrSpacetime/MgrWorld.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    pTest_ = nullptr;
    orderActorToFactory(990, PointSpriteTest, "PointSpriteTest1");
    orderActorToFactory(991, PointSpriteTest, "PointSpriteTest2");
    orderActorToFactory(992, PointSpriteTest, "PointSpriteTest3");
    orderActorToFactory(993, PointSpriteTest, "PointSpriteTest4");
}

void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {

    if (getActiveFrame() == 120) {
        PointSpriteTest* pTest1 = (PointSpriteTest*)obtainActorFromFactory(990);
        bringDirector()->addSubGroup(pTest1);
        pTest1->position(0,0,0);
    }
    if (getActiveFrame() == 140) {
        PointSpriteTest* pTest2 = (PointSpriteTest*)obtainActorFromFactory(991);
        bringDirector()->addSubGroup(pTest2);
        pTest2->position(PX_C(200), PX_C(200), PX_C(200));
    }
    if (getActiveFrame() == 160) {
        PointSpriteTest* pTest3 = (PointSpriteTest*)obtainActorFromFactory(992);
        bringDirector()->addSubGroup(pTest3);
        pTest3->position(PX_C(400), PX_C(400), PX_C(400));
    }
    if (getActiveFrame() == 180) {
        PointSpriteTest* pTest4 = (PointSpriteTest*)obtainActorFromFactory(993);
        bringDirector()->addSubGroup(pTest4);
        pTest4->position(PX_C(600), PX_C(600), PX_C(600));
    }

}

TrialAndErrScene::~TrialAndErrScene() {
}
