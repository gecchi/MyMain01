#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9CubeMapMorphMeshModel::GgafDx9CubeMapMorphMeshModel(char* prm_model_name) : GgafDx9MorphMeshModel(prm_model_name) {
    TRACE3("GgafDx9CubeMapMorphMeshModel::GgafDx9CubeMapMorphMeshModel(" << _model_name << ")");
}

GgafDx9CubeMapMorphMeshModel::~GgafDx9CubeMapMorphMeshModel() {
}

