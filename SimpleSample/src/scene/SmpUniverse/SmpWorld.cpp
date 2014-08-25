#include "SmpWorld.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");  //キャラ作成＆保持
    getSceneDirector()->addSubGroup(pActor_);  //キャラをシーン監督の配下に所属（表示される）
    GgafLib::VirtualButton::_keyboardmap.BUTTON1 = DIK_SPACE;  //ボタン１=スペースキー とする。
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
    //キャラをボタン入力で移動
    vb_.update(); //入力状況更新
    if (vb_.isBeingPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_z += PX_C(2); //奥
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb_.isBeingPressed(VB_RIGHT)) {
            pActor_->_x += PX_C(2); //右
        }
        if (vb_.isBeingPressed(VB_LEFT)) {
            pActor_->_x -= PX_C(2); //左
        }
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_y += PX_C(2); //上
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_y -= PX_C(2); //下
        }
    }
}

SmpWorld::~SmpWorld() {
}
