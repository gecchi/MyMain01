#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultDynaD3DXMeshActor::DefaultDynaD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9DynaD3DXMeshActor(prm_name,
                             prm_model,
                             "DefaultMeshEffect",
                             "DefaultMeshTechnique",
                             NEW StgChecker(this) ) {
    _class_name = "DefaultDynaD3DXMeshActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);


}

void DefaultDynaD3DXMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}


DefaultDynaD3DXMeshActor::~DefaultDynaD3DXMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
