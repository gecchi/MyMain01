#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxCubeMapMeshSetModel::GgafDxCubeMapMeshSetModel(char* prm_model_name) : GgafDxMeshSetModel(prm_model_name) {
    TRACE3("GgafDxCubeMapMeshSetModel::GgafDxCubeMapMeshSetModel(" << _model_name << ")");
    _obj_model |= Obj_GgafDxCubeMapMeshSetModel;
}

GgafDxCubeMapMeshSetModel::~GgafDxCubeMapMeshSetModel() {
}

