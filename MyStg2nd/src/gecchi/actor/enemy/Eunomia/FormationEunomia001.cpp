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


void FormationEunomia001::wasDestroyedFormation(GgafDxGeometricActor* prm_pActorLast) {
    //�ґ����Ŏ��̎���
    EffectTurbo002* pTurbo002 = (EffectTurbo002*)P_COMMON_SCENE->_pDepo_EffectTurbo002->dispatchForce();
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
