#include "SmpSpacetime.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpCaretaker.h"
#include "actor/SmpCamera.h"
#include "SmpSpacetime/SmpWorld.h"

using namespace SimpleSample;

#define ID_SMPWORLD 123
#define P1 0

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //SmpWorldシーンの作成要求
    requestScene(ID_SMPWORLD, SmpWorld);
    //この世(Spacetime)コンストラクタ内で、
    //他のシーンの所属( appendChild(GgafCore::Scene*) )は実行しないでください。
    pVb_ = new GgafLib::VirtualButton(); //仮想ボタンの生成
    pVb_->remap(P1, VB_UP     , VBK_UP   , VBJ_P1_POV_UP   );    //VB_UP      => キーボード↑ または、ハットスイッチ上 とする。
    pVb_->remap(P1, VB_DOWN   , VBK_DOWN , VBJ_P1_POV_DOWN );    //VB_DOWN    => キーボード↓ または、ハットスイッチ下 とする。
    pVb_->remap(P1, VB_LEFT   , VBK_LEFT , VBJ_P1_POV_LEFT );    //VB_LEFT    => キーボード← または、ハットスイッチ左 とする。
    pVb_->remap(P1, VB_RIGHT  , VBK_RIGHT, VBJ_P1_POV_RIGHT);    //VB_RIGHT   => キーボード→ または、ハットスイッチ右 とする。
    pVb_->remap(P1, VB_BUTTON1, VBK_SPACE, VBJ_P1_BUTTON_01);    //VB_BUTTON1 => スペースキー または ジョイスティックボタン１ とする。
}

void SmpSpacetime::initialize() {
    //世界シーン(SmpWorld)を配下に所属させる
    appendChild(receiveScene(ID_SMPWORLD));
}

void SmpSpacetime::processBehavior() {
    //仮想ボタンの状態を更新
    pVb_->update();
}

SmpSpacetime::~SmpSpacetime() {
    delete pVb_;
}

