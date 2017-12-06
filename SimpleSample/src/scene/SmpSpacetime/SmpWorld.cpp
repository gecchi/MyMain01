#include "SmpWorld.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");  //キャラクター作成＆保持
    bringSceneMediator()->addSubGroup(pActor_);  //キャラクターをシーン仲介者の配下に所属（表示される）
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = キーボード↑ または、Y軸－ とする。
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = キーボード↓ または、Y軸＋ とする。
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = キーボード← または、X軸－ とする。
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = キーボード→ または、X軸＋ とする。
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = スペースキー または ジョイスティックボタン１ とする。
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
    //キャラをボタン入力で移動
    vb_.update(); //入力状況更新
    if (vb_.isPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb_.isPressed(VB_UP)) {
            pActor_->_z += PX_C(2); //奥
        }
        if (vb_.isPressed(VB_DOWN)) {
            pActor_->_z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb_.isPressed(VB_RIGHT)) {
            pActor_->_x += PX_C(2); //右
        }
        if (vb_.isPressed(VB_LEFT)) {
            pActor_->_x -= PX_C(2); //左
        }
        if (vb_.isPressed(VB_UP)) {
            pActor_->_y += PX_C(2); //上
        }
        if (vb_.isPressed(VB_DOWN)) {
            pActor_->_y -= PX_C(2); //下
        }
    }
}

SmpWorld::~SmpWorld() {
}
