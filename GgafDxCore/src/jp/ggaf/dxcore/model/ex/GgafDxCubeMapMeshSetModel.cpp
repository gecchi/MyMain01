#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshSetModel.h"

#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCubeMapMeshSetModel::GgafDxCubeMapMeshSetModel(const char* prm_model_name) : GgafDxMeshSetModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _obj_model |= Obj_GgafDxCubeMapMeshSetModel;
}

GgafDxCubeMapMeshSetModel::~GgafDxCubeMapMeshSetModel() {
}

