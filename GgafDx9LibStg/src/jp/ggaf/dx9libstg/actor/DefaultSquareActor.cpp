#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;

DefaultSquareActor::DefaultSquareActor(string prm_name, string prm_model)
	: GgafDx9SquareActor(prm_name, prm_model, NEW GgafDx9GeometryMover(this), NEW StgChecker(this)) {
	_class_name = "DefaultSquareActor";
	_pChecker = (StgChecker*)_pGeoChecker;
}

DefaultSquareActor::~DefaultSquareActor() {
	TRACE("DefaultSquareActor::~DefaultSquareActor() "<<getName()<<" start--->");
	TRACE("DefaultSquareActor::~DefaultSquareActor() "<<getName()<<" <---end");
}
