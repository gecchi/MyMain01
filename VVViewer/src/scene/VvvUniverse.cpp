#include "stdafx.h"
#include "VvvUniverse.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "scene/VvvUniverse/VvvWorld.h"

using namespace VVViewer;

VvvUniverse::VvvUniverse(const char* prm_name, VvvCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    pWorld_ = nullptr;

    //「この世」コンストラクタ内で、シーンの new は行わないで下さい。
}

void VvvUniverse::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    pWorld_ = createInFactory(VVViewer::VvvWorld, "SIMPLE_WORLD");
    addSubLast(pWorld_);
}

VvvUniverse::~VvvUniverse() {
}

