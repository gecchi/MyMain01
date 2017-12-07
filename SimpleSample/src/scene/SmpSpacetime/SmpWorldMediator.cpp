#include "SmpWorldMediator.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "actor/SmpActor.h"
#include "SmpWorld.h"

using namespace SimpleSample;

SmpWorldMediator::SmpWorldMediator(GgafLib::DefaultScene* prm_pScene) :
        DefaultSceneMediator(prm_pScene) {
    pActor_ = new SmpActor("TEST");  //キャラクター作成＆保持
    addSubGroup(pActor_);  //キャラクターをシーン仲介者の配下に所属（表示される）
}
void SmpWorldMediator::initialize() {
}

void SmpWorldMediator::processBehavior() {
    //キャラをボタン入力で移動
    GgafLib::VirtualButton* vb = ((SmpWorld*)getPlatformScene())->getVB();
    if (vb->isPressed(VB_BUTTON1)) {
        //ボタン１（スペースキー）を押しながらの場合
        if (vb->isPressed(VB_UP)) {
            pActor_->_z += PX_C(2); //奥
        }
        if (vb->isPressed(VB_DOWN)) {
            pActor_->_z -= PX_C(2); //手前
        }
    } else {
        //ボタン１（スペースキー）を離している場合
        if (vb->isPressed(VB_RIGHT)) {
            pActor_->_x += PX_C(2); //右
        }
        if (vb->isPressed(VB_LEFT)) {
            pActor_->_x -= PX_C(2); //左
        }
        if (vb->isPressed(VB_UP)) {
            pActor_->_y += PX_C(2); //上
        }
        if (vb->isPressed(VB_DOWN)) {
            pActor_->_y -= PX_C(2); //下
        }
    }
}

SmpWorldMediator::~SmpWorldMediator() {
}
