#include "jp/ggaf/dx/model/ex/CubeMapMeshModel.h"

#include "jp/ggaf/dx/manager/ModelManager.h"


using namespace GgafDx;


CubeMapMeshModel::CubeMapMeshModel(const char* prm_model_id) : MeshModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_model |= Obj_GgafDx_CubeMapMeshModel;
}

CubeMapMeshModel::~CubeMapMeshModel() {
}

