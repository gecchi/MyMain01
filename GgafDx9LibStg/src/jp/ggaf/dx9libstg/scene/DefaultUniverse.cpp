#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DefaultUniverse::DefaultUniverse(const char* prm_name) : GgafDx9Universe(prm_name) {
    _class_name = "DefaultUniverse";
    _pLinearOctree = NEW GgafLinearOctree<StgChecker>
    (
        5,
        -8000000 ,-8000000 ,-8000000 ,8000000 ,8000000 ,8000000
    );


//
//
//    GgafLinearOctree<GgafDx9GeometricActor>* pLinearOctree =
//            NEW GgafLinearOctree<GgafDx9GeometricActor>
//                (
//                    5,
//                    -8000000 ,-8000000 ,-8000000 ,8000000 ,8000000 ,8000000
//                );
//    GgafLinearOctree<GgafDx9GeometricActor>::Elem* pElem = NEW GgafLinearOctree<GgafDx9GeometricActor>::Elem(this);
//    pLinearOctree->registElem(pElem, 1000,1000,1000,1500,1500,1500);
//
//    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")
//    pLinearOctree->putTree();
}

void DefaultUniverse::nextFrame() {
    GgafDx9Core::GgafDx9Universe::nextFrame();
}

DefaultUniverse::~DefaultUniverse() {
    _pLinearOctree->putTree();
    DELETE_IMPOSSIBLE_NULL(_pLinearOctree);

}
