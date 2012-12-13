#include "stdafx.h"
using namespace Mogera;

MgrUniverse::MgrUniverse(const char* prm_name, MgrCamera* prm_pCam) :
        GgafLib::DefaultUniverse(prm_name, prm_pCam) {
    //「この世」コンストラクタ内で、シーンの new は行わないで下さい。
}

void MgrUniverse::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    MgrWorld* pWorld = createInFactory(MgrWorld, "SIMPLE_WORLD");
    addSubLast(pWorld);
}

MgrUniverse::~MgrUniverse() {
}

