#include "SmpSpacetime.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpGod.h"
#include "actor/SmpCamera.h"
#include "SmpSpacetime/SmpWorld.h"

using GgafLib::VirtualButton;
using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //SmpWorldシーンの作成
    requestScene(0, SmpWorld);
    //この世(Spacetime)コンストラクタ内で、
    //他のシーンの所属( appendChild(GgafScene*) )は実行しないでください。
}

void SmpSpacetime::initialize() {
    //世界シーン(SmpWorld)を配下に所属させる
    appendChild(receiveScene(0));
}

void SmpSpacetime::processBehavior() {
    //仮想ボタンの状態を更新
    VirtualButton* vb = pGOD->getVB();
    vb->update();
}

SmpSpacetime::~SmpSpacetime() {
}

