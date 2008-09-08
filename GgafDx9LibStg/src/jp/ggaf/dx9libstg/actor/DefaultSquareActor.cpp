#include "stdafx.h"

DefaultSquareActor::DefaultSquareActor(string prm_name, string prm_xname)
	: GgafDx9SquareActor(prm_name, prm_xname, NEW StgMover(this), NEW StgChecker(this)) {
	_class_name = "DefaultSquareActor";
	_pMover = (StgMover*)_pGeoMover;
	_pChecker = (StgChecker*)_pGeoChecker;
}

DefaultSquareActor::~DefaultSquareActor() {
	TRACE("DefaultSquareActor::~DefaultSquareActor() "<<getName()<<" start--->");
	TRACE("DefaultSquareActor::~DefaultSquareActor() "<<getName()<<" <---end");
}
