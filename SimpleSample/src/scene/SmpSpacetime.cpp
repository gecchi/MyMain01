#include "SmpSpacetime.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "SmpSpacetime/SmpWorld.h"
#include "actor/SmpCamera.h"

using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //「この世」コンストラクタ内で、シーンの new は行わないで下さい。
}

void SmpSpacetime::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    SmpWorld* pWorld = createInFactory(SimpleSample::SmpWorld, "SIMPLE_WORLD");
    addSubLast(pWorld);
}

SmpSpacetime::~SmpSpacetime() {
}

