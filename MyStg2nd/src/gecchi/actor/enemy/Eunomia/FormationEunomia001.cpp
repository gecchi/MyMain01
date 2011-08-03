#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia001::FormationEunomia001(const char* prm_name) :
                                        FormationEunomia(prm_name,
                                                         R_FormationEunomia001_Col,
                                                         R_FormationEunomia001_Num,
                                                         R_FormationEunomia001_LaunchInterval,
                                                         R_FormationEunomia001_MvVelo,
                                                         "FormationEunomia001") {
    _class_name = "FormationEunomia001";
}


void FormationEunomia001::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //•Ò‘àÁ–ÅŽž‚ÌŽÀŒ±
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pStore_EffectTurbo002->dispatchForce();
    if (pTurbo002) {
        pTurbo002->locateAs(prm_pActorLast);
        pTurbo002->activate();
    }
}

void FormationEunomia001::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia001::~FormationEunomia001() {
}
