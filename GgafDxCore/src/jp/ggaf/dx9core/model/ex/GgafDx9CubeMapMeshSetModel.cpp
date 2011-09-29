#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9CubeMapMeshSetModel::GgafDx9CubeMapMeshSetModel(char* prm_model_name) : GgafDx9MeshSetModel(prm_model_name) {
    TRACE3("GgafDx9CubeMapMeshSetModel::GgafDx9CubeMapMeshSetModel(" << _model_name << ")");
}

GgafDx9CubeMapMeshSetModel::~GgafDx9CubeMapMeshSetModel() {
}

