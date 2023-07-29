#include "TrialAndErrScene.h"

#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/core/actor/SceneChief.h"
#include "scene/HgrSpacetime/HgrWorld.h"
#include "actor/Test01.h"
#include "actor/Jiki.h"
#include "HgrCaretaker.h"



using namespace GgafLib;
using namespace Hogera;

enum {
    PHASE_INIT ,
    PHASE_CALM ,
    PHASE_WAIT ,
    PHASE_BANPEI,
};

TrialAndErrScene::TrialAndErrScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "TrialAndErrScene";
    requestActor(10000, Test01);
    requestActor(10001, Jiki);
}

void TrialAndErrScene::initialize() {
    GgafDx::Input::updateMouseState();
    GgafDx::Input::updateMouseState(); //マウス座標の相対座標を0にするため２回呼び出す
}

void TrialAndErrScene::processBehavior() {
    if (getActiveFrame() == 100) {

//        ColliAABoxActor* XXX = NEW ColliAABoxActor("HOGEHOGE");
//        XXX->setScaleR(100);
//        getSceneChief()->appendGroupChild(XXX);
//        XXX->sayonara(2);


        Test01* pTest = (Test01*)receiveActor(10000);
        pTest->setPosition(0,0,0);
        getSceneChief()->appendGroupChild(HGR_MIKATA, pTest);

        Jiki* pJiki = (Jiki*)receiveActor(10001);
        pJiki->setPosition(PX_C(200), PX_C(200),0);
        getSceneChief()->appendGroupChild(HGR_TEKI, pJiki);


    }


#ifdef MY_DEBUG
    //ワイヤフレーム表示切替
    if (GgafDx::Input::isPushedDownKey(DIK_Q)) {
        if (pCARETAKER->_d3dfillmode == D3DFILL_WIREFRAME) {
            pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
        } else {
            pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
#endif
}

TrialAndErrScene::~TrialAndErrScene() {
}
