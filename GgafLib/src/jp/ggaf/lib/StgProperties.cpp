#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

string StgProperties::DIR_SCENE_DATA = ".\\scene\\";
string StgProperties::DIR_SPLINE_DATA = ".\\model\\spline\\";


void StgProperties::load(string prm_ini_filename) {
    GgafDxProperties::load(prm_ini_filename);
    if (GgafProperties::isExistKey("DIR_SCENE_DATA")) {
        StgProperties::DIR_SCENE_DATA   = getStr("DIR_SCENE_DATA");
    }
    if (GgafProperties::isExistKey("DIR_SPLINE_DATA")) {
        StgProperties::DIR_SPLINE_DATA  = getStr("DIR_SPLINE_DATA");
    }

    _TRACE_("StgProperties::DIR_SCENE_DATA="<<StgProperties::DIR_SCENE_DATA);
    _TRACE_("StgProperties::DIR_SPLINE_DATA="<<StgProperties::DIR_SPLINE_DATA);
}

void StgProperties::clean() {
    GgafDxProperties::clean();
}
