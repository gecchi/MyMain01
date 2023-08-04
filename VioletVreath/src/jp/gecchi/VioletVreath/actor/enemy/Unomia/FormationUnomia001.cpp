#include "FormationUnomia001.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationUnomia001::FormationUnomia001(const char* prm_name) :
                                        FormationUnomia(prm_name, "FormationUnomia001", StatusReset(FormationUnomia001)) {
    _class_name = "FormationUnomia001";
}

void FormationUnomia001::processBehavior() {
    FormationUnomia::processBehavior();
}

FormationUnomia001::~FormationUnomia001() {
}
