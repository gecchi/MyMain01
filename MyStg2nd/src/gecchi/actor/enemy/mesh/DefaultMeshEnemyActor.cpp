#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultMeshEnemyActor::DefaultMeshEnemyActor(char* prm_name, char* prm_model) : DefaultMeshActor(prm_name, prm_model) {
	_class_name = "DefaultMeshEnemyActor";
}

DefaultMeshEnemyActor::~DefaultMeshEnemyActor() {
}
