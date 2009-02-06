#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultSquareActor::DefaultSquareActor(const char* prm_name, const char* prm_model) :
    GgafDx9SquareActor(prm_name, prm_model, NEW GgafDx9GeometryMover(this), NEW StgChecker(this))
{
    _class_name = "DefaultSquareActor";
    _pChecker = (StgChecker*)_pGeoChecker;
}

DefaultSquareActor::~DefaultSquareActor() {
    TRACE("DefaultSquareActor::~DefaultSquareActor() "<<getName()<<" start--->");TRACE("DefaultSquareActor::~DefaultSquareActor() "<<getName()<<" <---end");
}
