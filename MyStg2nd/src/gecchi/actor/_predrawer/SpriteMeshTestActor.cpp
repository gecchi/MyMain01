#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


SpriteMeshTestActor::SpriteMeshTestActor(const char* prm_name) :
        SpriteMeshActor(prm_name, "_chk_SpriteMeshTestModel", NULL) {
    _class_name = "SpriteMeshTestActor";
    setHitAble(false);
}

SpriteMeshTestActor::~SpriteMeshTestActor() {
}

