#include "TrialAndErrScene.h"

#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/gecchi/VioletVrain/scene/VvSpacetime/World.h"
#include "jp/gecchi/VioletVrain/actor/Test01.h"
#include "jp/gecchi/VioletVrain/actor/Jiki.h"
#include "jp/gecchi/VioletVrain/VvGod.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVrain;

enum {
    PROG_INIT ,
    PROG_CALM ,
    PROG_WAIT ,
    PROG_BANPEI,
};

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    requestActor(10000, Test01);
    requestActor(10001, Jiki);
}

void TrialAndErrScene::initialize() {
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {
    if (getActiveFrame() == 100) {

//        ColliAABoxActor* XXX = NEW ColliAABoxActor("HOGEHOGE");
//        XXX->setScaleR(100);
//        bringSceneMediator()->appendGroupChild(XXX);
//        XXX->sayonara(2);


        Test01* pTest = (Test01*)receiveActor(10000);
        pTest->setPosition(0,0,0);
        bringSceneMediator()->appendGroupChild(VV_MIKATA, pTest);

        Jiki* pJiki = (Jiki*)receiveActor(10001);
        pJiki->setPosition(PX_C(200), PX_C(200),0);
        bringSceneMediator()->appendGroupChild(VV_TEKI, pJiki);


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
