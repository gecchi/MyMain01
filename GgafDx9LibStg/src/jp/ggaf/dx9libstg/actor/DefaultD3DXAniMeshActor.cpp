#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultD3DXAniMeshActor::DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9D3DXAniMeshActor(prm_name,
                         prm_model,
                         "DefaultAniMeshEffect",
                         "DefaultAniMeshTechnique",
                         NEW StgChecker(this) ) {
    _class_name = "DefaultD3DXAniMeshActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);

}

void DefaultD3DXAniMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}

DefaultD3DXAniMeshActor::~DefaultD3DXAniMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
