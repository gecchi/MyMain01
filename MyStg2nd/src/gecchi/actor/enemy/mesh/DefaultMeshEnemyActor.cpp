#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultMeshEnemyActor::DefaultMeshEnemyActor(const char* prm_name, const char* prm_model) : DefaultD3DXMeshActor(prm_name, prm_model, "DefaultMeshTechnique") {
    _class_name = "DefaultMeshEnemyActor";
}

DefaultMeshEnemyActor::~DefaultMeshEnemyActor() {
}
