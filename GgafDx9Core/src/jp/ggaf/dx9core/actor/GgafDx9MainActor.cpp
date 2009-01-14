#include "stdafx.h"

GgafDx9MainActor::GgafDx9MainActor(int prm_type, string prm_name, string prm_model, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker)
: GgafDx9MeshActor(prm_type, prm_name, prm_model, prm_pGeoMover, prm_pGeoChecker),
  GgafDx9DynaMeshActor(prm_type, prm_name, prm_model, prm_pGeoMover, prm_pGeoChecker),
  GgafDx9SpriteActor(prm_type, prm_name, prm_model, prm_pGeoMover, prm_pGeoChecker),
  GgafDx9CubeActor(prm_type, prm_name, prm_pGeoMover, prm_pGeoChecker) ,
  GgafDx9SquareActor(prm_type, prm_name, prm_pGeoMover, prm_pGeoChecker)
{
	_class_name = "GgafDx9MainActor";
	_dwFrameOffset = 0;
//	_pChecker = (StgChecker*)_pGeoChecker;

}


GgafDx9MainActor::~GgafDx9MainActor() {
	TRACE("GgafDx9MainActor::~GgafDx9MainActor() "<<getName()<<" start--->");
	TRACE("GgafDx9MainActor::~GgafDx9MainActor() "<<getName()<<" <---end");
}
