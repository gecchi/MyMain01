#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationEunomia001::FormationEunomia001(const char* prm_name) :
                                        FormationEunomia(prm_name,
                                                         "FormationEunomia001") {
    _class_name = "FormationEunomia001";
}


void FormationEunomia001::onDestroyedAll(GgafDxGeometricActor* prm_pActor_LastDestroyed) {
    //•Ò‘àÁ–ÅŽž‚ÌŽÀŒ±
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDepo_EffectTurbo002->dispatchForce();
    if (pTurbo002) {
        pTurbo002->locateAs(prm_pActor_LastDestroyed);
        pTurbo002->activate();
    }
}

void FormationEunomia001::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia001::~FormationEunomia001() {
}
