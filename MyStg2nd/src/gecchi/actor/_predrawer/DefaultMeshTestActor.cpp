#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


DefaultMeshTestActor::DefaultMeshTestActor(const char* prm_name) :
        DefaultMeshActor(prm_name, "_chk_DefaultMeshTestModel", NULL) {
    _class_name = "DefaultMeshTestActor";
    setHitAble(false);
}

DefaultMeshTestActor::~DefaultMeshTestActor() {
}

