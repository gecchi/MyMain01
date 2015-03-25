#include "SmpSpacetime.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "SmpSpacetime/SmpWorld.h"
#include "actor/SmpCamera.h"

using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //SmpWorldシーンの作成を注文する
    orderSceneToFactory(0, SimpleSample::SmpWorld, "SIMPLE_WORLD");
    //この世(Spacetime)コンストラクタ内で、
    //他のシーンの所属( addSubLast(GgafScene*) )は実行しないでください。
}

void SmpSpacetime::initialize() {
    //世界シーン(SmpWorld)を配下に所属させる
    addSubLast(obtainSceneFromFactory(0));
}

SmpSpacetime::~SmpSpacetime() {
}

