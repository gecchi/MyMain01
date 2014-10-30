#include "jp/ggaf/lib/GgafLibProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

std::string GgafLibProperties::DIRNAME_RESOURCE_WALL = "wall";
std::string GgafLibProperties::DIRNAME_RESOURCE_SPLINE = "spline";
std::string GgafLibProperties::DIR_WALL  = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_WALL + "/" ;
std::string GgafLibProperties::DIR_SPLINE = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_SPLINE + "/" ;

int GgafLibProperties::OCTREE_LEVEL = 1;

void GgafLibProperties::load(std::string prm_properties_filename) {
    GgafDxProperties::load(prm_properties_filename);
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_WALL")) {
        GgafLibProperties::DIRNAME_RESOURCE_WALL   = getStr("DIRNAME_RESOURCE_WALL");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SPLINE")) {
        GgafLibProperties::DIRNAME_RESOURCE_SPLINE  = getStr("DIRNAME_RESOURCE_SPLINE");
    }

    if (GgafProperties::isExistKey("OCTREE_LEVEL")) {
        GgafLibProperties::OCTREE_LEVEL  = getInt("OCTREE_LEVEL");
    }

    GgafLibProperties::DIR_WALL   = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_WALL   + "/";
    GgafLibProperties::DIR_SPLINE = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_SPLINE + "/";

    UTIL::strReplace(GgafLibProperties::DIR_WALL, "//", "/");
    UTIL::strReplace(GgafLibProperties::DIR_SPLINE , "//", "/");

    //指定があるのならば、ディレクトリ存在チェック
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_WALL")) {
        if (!PathFileExists(GgafLibProperties::DIR_WALL.c_str()) ) {
            throwGgafCriticalException("GgafLibProperties::load("<<prm_properties_filename<<") DIR_WALL("<<GgafLibProperties::DIR_WALL<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SPLINE")) {
        if (!PathFileExists(GgafLibProperties::DIR_SPLINE.c_str()) ) {
            throwGgafCriticalException("GgafLibProperties::load("<<prm_properties_filename<<") DIR_WALL("<<GgafLibProperties::DIR_SPLINE<<") のディレクトリが見つかりません。");
        }
    }

    _DTRACE_("GgafLibProperties::DIRNAME_RESOURCE_WALL=" << GgafLibProperties::DIRNAME_RESOURCE_WALL);
    _DTRACE_("GgafLibProperties::DIRNAME_RESOURCE_SPLINE=" << GgafLibProperties::DIRNAME_RESOURCE_SPLINE);
    _DTRACE_("GgafLibProperties::DIR_WALL=" << GgafLibProperties::DIR_WALL);
    _DTRACE_("GgafLibProperties::DIR_SPLINE=" << GgafLibProperties::DIR_SPLINE);
    _DTRACE_("GgafLibProperties::OCTREE_LEVEL=" << GgafLibProperties::OCTREE_LEVEL);
}

void GgafLibProperties::clean() {
    GgafDxProperties::clean();
}
