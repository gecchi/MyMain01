#include "TrialAndErrScene.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "scene/HgrSpacetime/HgrWorld.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "actor/Test01.h"
#include "actor/Jiki.h"
#include "HgrGod.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Hogera;

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    orderActorToFactory(10000, Test01, "Test01");
    orderActorToFactory(10001, Jiki, "Jiki");
}

void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {
    if (getActiveFrame() == 100) {
        Test01* pTest = (Test01*)obtainActorFromFactory(10000);
        pTest->setPosition(0,0,0);
        bringDirector()->addSubGroup(HGR_MIKATA, pTest);

        Jiki* pJiki = (Jiki*)obtainActorFromFactory(10001);
        pJiki->setPosition(PX_C(200), PX_C(200),0);
        bringDirector()->addSubGroup(HGR_TEKI, pJiki);

    }


#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
    if (GgafDxInput::isPushedDownKey(DIK_Q)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif
}

TrialAndErrScene::~TrialAndErrScene() {
}
