#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


SpriteMeshSetTestActor::SpriteMeshSetTestActor(const char* prm_name) :
        SpriteMeshSetActor(prm_name, "_chk_DefaultMeshSetTestModel", NULL) {
    _class_name = "DefaultMeshSetTestActor";
    setHitAble(false);
}

SpriteMeshSetTestActor::~SpriteMeshSetTestActor() {
}

