#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

FormationEunomia002::FormationEunomia002(const char* prm_name) :
                                        FormationEunomia(prm_name,
                                                         "FormationEunomia002") {
    _class_name = "FormationEunomia002";
}


void FormationEunomia002::onDestroyedAll(GgafDxGeometricActor* prm_pActor_LastDestroyed) {
    //•Ò‘àÁ–ÅŽž‚ÌŽÀŒ±
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDepo_EffectTurbo002->dispatchForce();
    if (pTurbo002) {
        pTurbo002->locateAs(prm_pActor_LastDestroyed);
        pTurbo002->activate();
    }
}

void FormationEunomia002::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia002::~FormationEunomia002() {
}
