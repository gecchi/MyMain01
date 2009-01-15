#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;

DefaultDynaMeshActor::DefaultDynaMeshActor(string prm_name, string prm_model)
	: GgafDx9DynaMeshActor(prm_name, prm_model, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))
{
	_class_name = "DefaultDynaMeshActor";
	_dwFrameOffset = 0;
	_pChecker = (StgChecker*)_pGeoChecker;

}

#ifdef OREDEBUG

void DefaultDynaMeshActor::processDrawTerminate() {
	//“–‚½‚è”»’è—Ìˆæ•\Ž¦
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	DelineateActor::get()-> drawHitarea(_pChecker);
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

#else

void DefaultDynaMeshActor::processDrawTerminate() {}

#endif


bool DefaultDynaMeshActor::isOffScreen() {
	if (_X < _X_OffScreenLeft) {
		return true;
	} else {
		if (_X > _X_OffScreenRight) {
			return true;
		} else {
			if (_Y > _Y_OffScreenTop) {
				return true;
			} else {
				if (_Y < _Y_OffScreenBottom) {
					return true;
				} else {
					if (_Z < GgafDx9God::_dCamZ*LEN_UNIT*10) {
						return true;
					} else {
						if (_Z > -1* GgafDx9God::_dCamZ*LEN_UNIT*10) {
							return true;
						} else {
							return false;
						}
					}
				}
			}
		}
	}
}
DefaultDynaMeshActor::~DefaultDynaMeshActor() {
	TRACE("DefaultDynaMeshActor::~DefaultDynaMeshActor() "<<getName()<<" start--->");
	TRACE("DefaultDynaMeshActor::~DefaultDynaMeshActor() "<<getName()<<" <---end");
}
