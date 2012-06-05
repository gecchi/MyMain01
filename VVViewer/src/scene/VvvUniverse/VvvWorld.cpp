#include "stdafx.h"
using namespace VVViewer;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    getDirector()->addSubGroup(NEW VvvCamWorker("VvvCamWorker"));

    pActor_ = new VvvActor("TEST");      //キャラ作成＆保持
    getDirector()->addSubGroup(pActor_); //キャラをシーン監督の配下に所属（表示される）

    vb_ = NEW GgafLib::VirtualButton();
    GgafLib::VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //ボタン１=スペースキー とする。

}
void VvvWorld::initialize() {
}

void VvvWorld::processBehavior() {
    vb_->update(); //入力状況更新
    if (VvvGod::is_wm_dropfiles_) {
        VvvGod::is_wm_dropfiles_ = false;
//        getDirector()->addSubGroup(createInFactory(GgafLib::DefaultMeshActor, VvvGod::is_wm_dropfiles_));
    }
}

VvvWorld::~VvvWorld() {
}
