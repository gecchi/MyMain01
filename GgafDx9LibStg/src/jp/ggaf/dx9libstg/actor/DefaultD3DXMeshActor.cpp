#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9D3DXMeshActor(prm_name,
                         prm_model,
                         "DefaultMashEffect",
                         "DefaultMeshTechnique",
                         NEW StgChecker(this) ) {
    _class_name = "DefaultD3DXMeshActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);

}

void DefaultD3DXMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
