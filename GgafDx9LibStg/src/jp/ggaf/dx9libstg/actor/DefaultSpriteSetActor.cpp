#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultSpriteSetActor::DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9SpriteSetActor(prm_name,
                          prm_model_id,
                          "DefaultSpriteSetEffect",
                          "DefaultSpriteSetTechnique",
                          NEW StgChecker(this) ) {
    _class_name = "DefaultSpriteSetActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pScaler = NEW GgafDx9GeometryScaler(this);
}



void DefaultSpriteSetActor::drawHitArea() {
    CubeEx::get()->drawHitarea(_pStgChecker);
}


DefaultSpriteSetActor::~DefaultSpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
