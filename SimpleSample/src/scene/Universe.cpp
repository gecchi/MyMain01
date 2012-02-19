#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace SimpleSample;

Universe::Universe(const char* prm_name, Camera* prm_pCamera) : DefaultUniverse(prm_name, prm_pCamera) {
}

void Universe::initialize() {
    //世界シーン生成し、自シーンの配下に所属させる
    addSubLast(new World("SIMPLE_WORLD"));
}

Universe::~Universe() {
}
