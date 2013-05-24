#include "stdafx.h"
#include "FormationEunomia001.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia001::FormationEunomia001(const char* prm_name) :
                                        FormationEunomia(prm_name,
                                                         "FormationEunomia001") {
    _class_name = "FormationEunomia001";
}

void FormationEunomia001::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia001::~FormationEunomia001() {
}
