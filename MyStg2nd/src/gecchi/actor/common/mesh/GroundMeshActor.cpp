#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundMeshActor::GroundMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9MeshActor(prm_name,
                     prm_model,
                     "GroundMeshEffect",
                     "GroundMeshTechnique",
                     NEW StgChecker(this) ) {

    _class_name = "GroundMeshActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);

    if (_pMeshModel->_paVtxBuffer_org[0].nx == 0 &&
        _pMeshModel->_paVtxBuffer_org[0].ny == 0 &&
        _pMeshModel->_paVtxBuffer_org[0].nz == 0)
    {
        strcpy(_technique, "GroundMeshTechnique2");
    }
}

//void GroundMeshActor::processPreDraw() {
//    _pNext_TheSameDrawDepthLevel = NULL;
//    if (_is_active_flg && _can_live_flg) {
//        //”wŒi‚È‚Ì‚Å”w–Ê‚Å•`‰æ
//        GgafDx9Universe::setDrawDepthMaxLevel(this);
//    }
//}


void GroundMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}

GroundMeshActor::~GroundMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
