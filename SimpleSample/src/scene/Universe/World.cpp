#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    pActor_ = new TestActor("TEST");     //キャラ作成＆保持
    getDirector()->addSubGroup(pActor_); //キャラをシーン監督の配下に所属（表示される）
    VirtualButton::_tagKeymap.BUTTON1 = DIK_SPACE; //ボタン１=スペースキー とする。
}

void World::processBehavior() {
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
            pActor_->_Y += PX2CO(2); //上（Y軸は上が正）
        }
        if (vb_.isBeingPressed(VB_DOWN)) {
            pActor_->_Y -= PX2CO(2); //下
        }
    }
}

World::~World() {
}
