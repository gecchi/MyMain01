#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;

DefaultMeshActor::DefaultMeshActor(string prm_name, string prm_model)
	: GgafDx9MeshActor(prm_name, prm_model, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))
{
	_class_name = "DefaultMeshActor";
	_dwFrameOffset = 0;
	_pChecker = (StgChecker*)_pGeoChecker;

}

#ifdef OREDEBUG

void DefaultMeshActor::processDrawTerminate() {
	//�����蔻��̈�\��
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	DelineateActor::get()-> drawHitarea(_pChecker);
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
}

#else

void DefaultMeshActor::processDrawTerminate() {}

#endif

DefaultMeshActor::~DefaultMeshActor() {
	TRACE("DefaultMeshActor::~DefaultMeshActor() "<<getName()<<" start--->");
	TRACE("DefaultMeshActor::~DefaultMeshActor() "<<getName()<<" <---end");
}
