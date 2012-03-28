#include "stdafx.h"
using namespace SimpleSample;

SmpUniverse::SmpUniverse(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    //「この世」コンストラクタ内で、シーンの new は行わないで下さい。
}

void SmpUniverse::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    SmpWorld* pWorld = createInFactory(SmpWorld, "SIMPLE_WORLD");
    addSubLast(pWorld);
}

SmpUniverse::~SmpUniverse() {
}

