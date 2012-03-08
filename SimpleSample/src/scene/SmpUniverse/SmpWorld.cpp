#include "stdafx.h"
using namespace SimpleSample;

SmpWorld::SmpWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pActor_ = new SmpActor("TEST");     //キャラ作成＆保持
    getDirector()->addSubGroup(pActor_); //キャラをシーン監督の配下に所属（表示される）
    GgafLib::VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //ボタン１=スペースキー とする。
}

void SmpWorld::processBehavior() {
    //キャラをボタン入力で移動
    vb_.update(); //入力状況更新
    if (vb_.isBeingPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Z += PX2CO(2); //奥
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Z -= PX2CO(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb_.isBeingPressed(VB_RIGHT)) {
            pActor_->_X += PX2CO(2); //右
        }
        if (vb_.isBeingPressed(VB_LEFT)) {
            pActor_->_X -= PX2CO(2); //左
        }
        if (vb_.isBeingPressed(VB_UP)) {
            pActor_->_Y += PX2CO(2); //上
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Y -= PX2CO(2); //下
        }
    }
}

SmpWorld::~SmpWorld() {
}
