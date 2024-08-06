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
    VirtualButton* pVb = &(pCARETAKER->getSpacetime()->getWorld()->vb_);
    //ワイヤフレーム表示切替
#ifdef MY_DEBUG
    if (pVb->isPushedDown(0, VB_UI_DEBUG)) {
       if (pCARETAKER->_draw_hit_area_kind == 0) {
           pCARETAKER->_d3dfillmode = D3DFILL_WIREFRAME;
           pCARETAKER->_draw_hit_area_kind = 1;
       } else {
           pCARETAKER->_d3dfillmode = D3DFILL_SOLID;
           pCARETAKER->_draw_hit_area_kind = 0;
       }
   }
#endif
}

TrialAndErrScene::~TrialAndErrScene() {
}
