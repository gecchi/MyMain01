#include "jp/ggaf/dx/model/ex/CubeMapMeshModel.h"

#include "jp/ggaf/dx/manager/ModelManager.h"


using namespace GgafDx;


CubeMapMeshModel::CubeMapMeshModel(const char* prm_model_name) : MeshModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _obj_model |= Obj_GgafDx_CubeMapMeshModel;
}

CubeMapMeshModel::~CubeMapMeshModel() {
}

