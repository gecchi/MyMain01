#include "SmpWorld.h"

#include "actor/SmpActor.h"

using namespace SimpleSample;

SmpWorld::Mediator::Mediator(SmpWorld* prm_pSmpWorld) :
        GgafLib::DefaultSceneMediator(prm_pSmpWorld) {
    vb_.remap(VB_UP     , VBK_UP   , VBJ_Y_POS_MINUS);  //VB_UP      = キーボード↑ または、Y軸－ とする。
    vb_.remap(VB_DOWN   , VBK_DOWN , VBJ_Y_POS_PLUS );  //VB_DOWN    = キーボード↓ または、Y軸＋ とする。
    vb_.remap(VB_LEFT   , VBK_LEFT , VBJ_X_POS_MINUS);  //VB_LEFT    = キーボード← または、X軸－ とする。
    vb_.remap(VB_RIGHT  , VBK_RIGHT, VBJ_X_POS_PLUS );  //VB_RIGHT   = キーボード→ または、X軸＋ とする。
    vb_.remap(VB_BUTTON1, VBK_SPACE, VBJ_BUTTON_01  );  //VB_BUTTON1 = スペースキー または ジョイスティックボタン１ とする。
}


SmpWorld::SmpWorld(const char* prm_name) :
        GgafLib::DefaultScene(prm_name, NEW SmpWorld::Mediator(this)) {
    SmpActor* pActor = new SmpActor("TEST");  //キャラクター作成
    bringSceneMediator()->addSubGroup(pActor);  //キャラクターをシーン監督の配下に所属（表示される）
}

void SmpWorld::initialize() {
}

void SmpWorld::processBehavior() {
}

SmpWorld::~SmpWorld() {
}
