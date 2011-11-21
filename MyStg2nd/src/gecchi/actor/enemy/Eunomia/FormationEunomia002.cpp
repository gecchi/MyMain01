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


void FormationEunomia002::processBehavior() {
    FormationEunomia::processBehavior();
}

FormationEunomia002::~FormationEunomia002() {
}
