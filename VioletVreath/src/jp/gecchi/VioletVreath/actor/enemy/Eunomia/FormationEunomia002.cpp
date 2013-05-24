#include "stdafx.h"
#include "FormationEunomia002.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationEunomia002::FormationEunomia002(const char* prm_name) :
                                        FormationEunomia(prm_name,
                                                         "FormationEunomia002") {
    _class_name = "FormationEunomia002";
}

void FormationEunomia002::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia002::~FormationEunomia002() {
}
