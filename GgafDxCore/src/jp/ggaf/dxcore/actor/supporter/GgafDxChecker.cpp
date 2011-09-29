#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxChecker::GgafDxChecker(GgafDxGeometricActor* prm_pActor) :
    GgafObject() {
    _pCollisionArea = NULL;
    _pActor = prm_pActor;
    _blown_sgn_vX = 0;
    _blown_sgn_vY = 0;
    _blown_sgn_vZ = 0;
//    _is_blown = false;
}


GgafDxChecker::~GgafDxChecker() {
}
