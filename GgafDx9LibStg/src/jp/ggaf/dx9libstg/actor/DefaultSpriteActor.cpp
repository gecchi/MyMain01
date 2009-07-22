#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultSpriteActor::DefaultSpriteActor(const char* prm_name, const char* prm_model_id) :
    GgafDx9SpriteActor(prm_name,
                       prm_model_id,
                       "DefaultSpriteEffect",
                       "DefaultSpriteTechnique",
                       NEW StgChecker(this) ) {
    _class_name = "DefaultSpriteActor";
    _frame_offset = 0;
    _pStgChecker = (StgChecker*)_pChecker;
    _pMover = NEW GgafDx9GeometryMover(this);
    _pScaler = NEW GgafDx9GeometryScaler(this);
}

#ifdef OREDEBUG

void DefaultSpriteActor::processDrawTerminate() {
    //“–‚½‚è”»’è—Ìˆæ•\Ž¦
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pStgChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void DefaultSpriteActor::processDrawTerminate() {}

#endif

DefaultSpriteActor::~DefaultSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
