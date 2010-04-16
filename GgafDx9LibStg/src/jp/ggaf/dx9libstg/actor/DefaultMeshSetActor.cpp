#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultMeshSetActor::DefaultMeshSetActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshSetActor(prm_name,
                        prm_model,
                        "DefaultMeshSetEffect",
                        "DefaultMeshSetTechnique",
                        NEW CollisionChecker(this) ) {

    _class_name = "DefaultMeshSetActor";
    _frame_offset = 0;
    _pCollisionChecker = (CollisionChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);
//    if (_pMeshSetModel->_paVtxBuffer_org[0].nx == 0 &&
//        _pMeshSetModel->_paVtxBuffer_org[0].ny == 0 &&
//        _pMeshSetModel->_paVtxBuffer_org[0].nz == 0)
//    {
//        strcpy(_technique, "DefaultMeshSetTechnique2");
//    }

}

void DefaultMeshSetActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}

DefaultMeshSetActor::~DefaultMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pCollisionChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
