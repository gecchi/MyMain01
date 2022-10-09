#include "jp/ggaf/dx/model/ex/CubeMapMeshSetModel.h"

#include "jp/ggaf/dx/manager/ModelManager.h"


using namespace GgafDx;

CubeMapMeshSetModel::CubeMapMeshSetModel(const char* prm_model_id) : MeshSetModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_CubeMapMeshSetModel;
}

CubeMapMeshSetModel::~CubeMapMeshSetModel() {
}

