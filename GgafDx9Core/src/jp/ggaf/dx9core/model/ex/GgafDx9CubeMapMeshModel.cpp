#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9CubeMapMeshModel::GgafDx9CubeMapMeshModel(char* prm_model_name) : GgafDx9MeshModel(prm_model_name) {
    TRACE3("GgafDx9CubeMapMeshModel::GgafDx9CubeMapMeshModel(" << _model_name << ")");
}

GgafDx9CubeMapMeshModel::~GgafDx9CubeMapMeshModel() {
}

