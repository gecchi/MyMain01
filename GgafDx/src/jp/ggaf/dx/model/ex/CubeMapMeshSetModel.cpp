#include "jp/ggaf/dx/model/ex/CubeMapMeshSetModel.h"

#include "jp/ggaf/dx/manager/ModelManager.h"


using namespace GgafDx;

CubeMapMeshSetModel::CubeMapMeshSetModel(const char* prm_model_name) : MeshSetModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _obj_model |= Obj_GgafDx_CubeMapMeshSetModel;
}

CubeMapMeshSetModel::~CubeMapMeshSetModel() {
}

