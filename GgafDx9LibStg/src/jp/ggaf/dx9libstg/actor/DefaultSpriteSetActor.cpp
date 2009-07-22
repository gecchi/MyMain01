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
    _pMover = NEW GgafDx9GeometryMover(this);
    _pScaler = NEW GgafDx9GeometryScaler(this);
}

#ifdef OREDEBUG

void DefaultSpriteSetActor::processDrawTerminate() {
    //“–‚½‚è”»’è—Ìˆæ•\Ž¦
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pStgChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void DefaultSpriteSetActor::processDrawTerminate() {}

#endif

DefaultSpriteSetActor::~DefaultSpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
