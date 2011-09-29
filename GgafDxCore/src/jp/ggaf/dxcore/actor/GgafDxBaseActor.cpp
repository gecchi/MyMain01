#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBaseActor::GgafDxBaseActor(const char* prm_name, GgafStatus* prm_pStat) : GgafMainActor(prm_name, prm_pStat) {
    _obj_class |= Obj_GgafDxBaseActor;
    _class_name = "GgafDxBaseActor";
}

GgafDxBaseActor::~GgafDxBaseActor() {
}
