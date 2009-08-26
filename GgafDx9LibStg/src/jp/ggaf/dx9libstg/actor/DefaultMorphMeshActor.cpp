#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9MorphMeshActor(prm_name,
                     prm_model_id,
                     "DefaultMorphMeshEffect",
                     "DefaultMorphMeshTechnique",
                     NEW StgChecker(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;

    _pScaler = NEW GgafDx9GeometryScaler(this);
    _pMorpher = NEW GgafDx9GeometryMorpher(this);

}

void DefaultMorphMeshActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}


DefaultMorphMeshActor::~DefaultMorphMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
    DELETE_IMPOSSIBLE_NULL(_pMorpher);
}
