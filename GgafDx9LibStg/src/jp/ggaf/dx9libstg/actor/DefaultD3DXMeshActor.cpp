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
    _pMover = NEW GgafDx9GeometryMover(this);
    _pScaler = NEW GgafDx9GeometryScaler(this);

}

#ifdef OREDEBUG

void DefaultD3DXMeshActor::processAfterDraw() {
    //“–‚½‚è”»’è—Ìˆæ•\Ž¦
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pStgChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void DefaultD3DXMeshActor::processAfterDraw() {}

#endif

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pStgChecker);
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pScaler);
}
