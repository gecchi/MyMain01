#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultMeshActor::DefaultMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshActor(prm_name,
                     prm_model,
                     "DefaultMeshEffect",
                     "DefaultMeshTechnique",
                     NEW StgChecker(this) ) {

    _class_name = "DefaultMeshActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);

    if (_pMeshModel->_paVtxBuffer_org[0].nx == 0 &&
        _pMeshModel->_paVtxBuffer_org[0].ny == 0 &&
        _pMeshModel->_paVtxBuffer_org[0].nz == 0)
    {
        strcpy(_technique, "DefaultMeshTechnique2");
    }
}

void DefaultMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}

DefaultMeshActor::~DefaultMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
