#include "TrialAndErrScene.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "actor/Zako.h"
#include "actor/FormationZako001.h"
#include "scene/MgrSpacetime/MgrWorld.h"

#include "actor/BoardTest.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    orderActorToFactory(999, FormationZako001, "FormationZako001");
}

void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {
    if (getActiveFrame() == 10) {
        BoardTest* p1 = createInFactory(BoardTest, "BoardTest1");
        bringDirector()->addSubGroup(p1);
        p1->position( PX_C(10), PX_C(30));
        p1->setMaterialColor(0.2,1.0,1.2);
        BoardTest* p2 = createInFactory(BoardTest, "BoardTest1");
        bringDirector()->addSubGroup(p2);
        p2->position(PX_C(100), PX_C(100));
        p2->setScaleR(2.0);
        p2->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
        p2->pAFader_->beat(300, 100,20,100,-1);
        p2->setAlpha(0.5);
        BoardTest* p3 = createInFactory(BoardTest, "BoardTest1");
        bringDirector()->addSubGroup(p3);
        p3->position(PX_C(200), PX_C(200));
        p3->setAlign(ALIGN_RIGHT, VALIGN_BOTTOM);
        p3->setMaterialColor(1.0,0.5,0.2);
    }

    if (getActiveFrame() == 120) {
        FormationZako001* p = (FormationZako001*)obtainActorFromFactory(999);
        bringDirector()->addSubGroup(p);
        p->position(0,0,0);
    }

    if (GgafDxInput::isPushedDownKey(DIK_O) ) {
        fadeinSceneTree(200);
    }
    if (GgafDxInput::isPushedDownKey(DIK_P) ) {
        fadeoutScene(200);
    }

}

TrialAndErrScene::~TrialAndErrScene() {
}
