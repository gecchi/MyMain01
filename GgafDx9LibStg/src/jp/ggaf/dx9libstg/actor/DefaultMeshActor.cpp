#include "stdafx.h"

DefaultMeshActor::DefaultMeshActor(string prm_name, string prm_model)
	: GgafDx9MeshActor(prm_name, prm_model, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))
{
	_class_name = "DefaultMeshActor";
	_dwFrameOffset = 0;
	_pChecker = (StgChecker*)_pGeoChecker;

}

#ifdef OREDEBUG

void DefaultMeshActor::processDrawTerminate() {
	//“–‚½‚è”»’è—Ìˆæ•\Ž¦
	DelineateActor::get()-> drawHitarea(_pChecker);
}

#else

void DefaultMeshActor::processDrawTerminate() {}

#endif

DefaultMeshActor::~DefaultMeshActor() {
	TRACE("DefaultMeshActor::~DefaultMeshActor() "<<getName()<<" start--->");
	TRACE("DefaultMeshActor::~DefaultMeshActor() "<<getName()<<" <---end");
}
