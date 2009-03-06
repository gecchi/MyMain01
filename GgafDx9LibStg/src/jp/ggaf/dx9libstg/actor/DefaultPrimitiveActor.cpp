#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultPrimitiveActor::DefaultPrimitiveActor(const char* prm_name, const char* prm_model, const char* prm_technique) :
    GgafDx9PrimitiveActor(prm_name, prm_model, prm_technique, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))
{
    _class_name = "DefaultPrimitiveActor";
    _dwFrameOffset = 0;
    _pChecker = (StgChecker*)_pGeoChecker;

}

#ifdef OREDEBUG

void DefaultPrimitiveActor::processDrawTerminate() {
    //“–‚½‚è”»’è—Ìˆæ•\Ž¦
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    DelineateActor::get()->drawHitarea(_pChecker);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

#else

void DefaultPrimitiveActor::processDrawTerminate() {}

#endif

DefaultPrimitiveActor::~DefaultPrimitiveActor() {
    TRACE("DefaultPrimitiveActor::~DefaultPrimitiveActor() "<<getName()<<" start--->");TRACE("DefaultPrimitiveActor::~DefaultPrimitiveActor() "<<getName()<<" <---end");
}
