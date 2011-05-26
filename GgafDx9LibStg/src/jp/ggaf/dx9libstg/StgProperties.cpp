#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

string StgProperties::DIR_SCENE_DATA = "";
string StgProperties::DIR_SPLINE_DATA = "";


void StgProperties::load(string prm_ini_filename) {
    GgafDx9Properties::load(prm_ini_filename);
    StgProperties::DIR_SCENE_DATA   = getStr("DIR_SCENE_DATA");
    StgProperties::DIR_SPLINE_DATA  = getStr("DIR_SPLINE_DATA");

    _TRACE_("StgProperties::DIR_SCENE_DATA="<<StgProperties::DIR_SCENE_DATA);
    _TRACE_("StgProperties::DIR_SPLINE_DATA="<<StgProperties::DIR_SPLINE_DATA);
}

void StgProperties::clean() {
    GgafDx9Properties::clean();
}
