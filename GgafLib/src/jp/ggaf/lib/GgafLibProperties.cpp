#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

std::string GgafLibProperties::DIR_SCENE_DATA = ".\\scene\\";
std::string GgafLibProperties::DIR_SPLINE_DATA = ".\\spline\\";
int GgafLibProperties::OCTREE_LEVEL = 1;

void GgafLibProperties::load(std::string prm_ini_filename) {
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
