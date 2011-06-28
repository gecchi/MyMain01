#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationEunomia002::FormationEunomia002(const char* prm_name) :
                                        FormationEunomia(prm_name,
                                                         4  + _RANK_*2,
                                                         15 + _RANK_*10,
                                                         2  +  (10 - (_RANK_>1.0?1.0:_RANK_)*5),
                                                         10000 + _RANK_*10000,
                                                         "FormationEunomia002") {
    _class_name = "FormationEunomia002";
}


void FormationEunomia002::wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    //•Ò‘àÁ–ÅŽž‚ÌŽÀŒ±
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pStore_EffectTurbo002->employForce();
    if (pTurbo002) {
        pTurbo002->locateAs(prm_pActorLast);
        pTurbo002->activate();
    }
}

void FormationEunomia002::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia002::~FormationEunomia002() {
}
