#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultD3DXMeshActor::DefaultD3DXMeshActor(const char* prm_name, const char* prm_model) :
    GgafDx9D3DXMeshActor(prm_name, prm_model, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))
{
    _class_name = "DefaultD3DXMeshActor";
    _dwFrameOffset = 0;
    _pChecker = (StgChecker*)_pGeoChecker;

}

#ifdef OREDEBUG

void DefaultD3DXMeshActor::processDrawTerminate() {
    //“–‚½‚è”»’è—Ìˆæ•\Ž¦
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    DelineateActor::get()->drawHitarea(_pChecker);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

#else

void DefaultD3DXMeshActor::processDrawTerminate() {}

#endif

DefaultD3DXMeshActor::~DefaultD3DXMeshActor() {
    TRACE("DefaultD3DXMeshActor::~DefaultD3DXMeshActor() "<<getName()<<" start--->");TRACE("DefaultD3DXMeshActor::~DefaultD3DXMeshActor() "<<getName()<<" <---end");
}
