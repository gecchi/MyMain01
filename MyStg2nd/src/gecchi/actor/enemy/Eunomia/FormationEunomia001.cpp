#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia001::FormationEunomia001(const char* prm_name) :
                                        FormationEunomia(prm_name,
                                                         5  + _RANK_*2,
                                                         20 + _RANK_*10,
                                                         10 - _RANK_*5,
                                                         10000 + _RANK_*10000,
                                                         "FormationEunomia001") {
    _class_name = "FormationEunomia001";
}


void FormationEunomia001::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //•Ò‘àÁ–ÅŽž‚ÌŽÀŒ±
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDispatcher_EffectTurbo002->employForce();
    if (pTurbo002) {
        pTurbo002->setCoordinateBy(prm_pActorLast);
        pTurbo002->activate();
    }
}

void FormationEunomia001::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia001::~FormationEunomia001() {
}
