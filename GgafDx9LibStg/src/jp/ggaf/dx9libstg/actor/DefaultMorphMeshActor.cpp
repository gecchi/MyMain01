#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultMorphMeshActor::DefaultMorphMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9MorphMeshActor(prm_name,
                     prm_model,
                     "M/DefaultMorphMeshEffect",
                     "DefaultMorphMeshTechnique",
                     NEW GgafDx9GeometryMover(this),
                     NEW StgChecker(this) ) {

    _class_name = "DefaultMorphMeshActor";
    _frame_offset = 0;
    _pChecker = (StgChecker*)_pGeoChecker;

}

#ifdef OREDEBUG

void DefaultMorphMeshActor::processDrawTerminate() {
    //“–‚½‚è”»’è—Ìˆæ•\Ž¦
    if (GgafDx9God::_d3dfillmode == D3DFILL_WIREFRAME) {
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        DelineateActor::get()->drawHitarea(_pChecker);
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
    }
}

#else

void DefaultMorphMeshActor::processDrawTerminate() {}

#endif

DefaultMorphMeshActor::~DefaultMorphMeshActor() {
}
