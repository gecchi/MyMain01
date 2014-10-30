#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshModel.h"

#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"

using namespace GgafCore;
using namespace GgafDxCore;


GgafDxCubeMapMeshModel::GgafDxCubeMapMeshModel(char* prm_model_name) : GgafDxMeshModel(prm_model_name) {
    _DTRACE3_("GgafDxCubeMapMeshModel::GgafDxCubeMapMeshModel(" << _model_name << ")");
    _obj_model |= Obj_GgafDxCubeMapMeshModel;
}

GgafDxCubeMapMeshModel::~GgafDxCubeMapMeshModel() {
}

