#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultMeshEnemyActor::DefaultMeshEnemyActor(const char* prm_name, const char* prm_model, const char* prm_technique) : DefaultMeshActor(prm_name, prm_model, prm_technique) {
    _class_name = "DefaultMeshEnemyActor";
}

DefaultMeshEnemyActor::~DefaultMeshEnemyActor() {
}
