#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

string GgafLibProperties::DIR_SCENE_DATA = ".\\scene\\";
string GgafLibProperties::DIR_SPLINE_DATA = ".\\model\\spline\\";
int GgafLibProperties::OCTREE_LEVEL = 5;

void GgafLibProperties::load(string prm_ini_filename) {
    GgafDxProperties::load(prm_ini_filename);
    if (GgafProperties::isExistKey("DIR_SCENE_DATA")) {
        GgafLibProperties::DIR_SCENE_DATA   = getStr("DIR_SCENE_DATA");
    }
    if (GgafProperties::isExistKey("DIR_SPLINE_DATA")) {
        GgafLibProperties::DIR_SPLINE_DATA  = getStr("DIR_SPLINE_DATA");
    }

    if (GgafProperties::isExistKey("OCTREE_LEVEL")) {
        GgafLibProperties::OCTREE_LEVEL  = getInt("OCTREE_LEVEL");
    }

    _TRACE_("GgafLibProperties::DIR_SCENE_DATA="<<GgafLibProperties::DIR_SCENE_DATA);
    _TRACE_("GgafLibProperties::DIR_SPLINE_DATA="<<GgafLibProperties::DIR_SPLINE_DATA);
    _TRACE_("GgafLibProperties::OCTREE_LEVEL="<<GgafLibProperties::OCTREE_LEVEL);
}

void GgafLibProperties::clean() {
    GgafDxProperties::clean();
}
