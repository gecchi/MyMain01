#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultMeshSetActor::DefaultMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                        prm_model,
                        "DefaultMashSetEffect",
                        "DefaultMeshSetTechnique",
                        NEW StgChecker(this) ) {

    _class_name = "DefaultMeshSetActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);

}

void DefaultMeshSetActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}

DefaultMeshSetActor::~DefaultMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
