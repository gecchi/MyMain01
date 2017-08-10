#include "jp/ggaf/lib/GgafLibProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

std::string GgafLibProperties::DIRNAME_RESOURCE_WALL = "wall";
std::string GgafLibProperties::DIRNAME_RESOURCE_SPLINE = "spline";
std::string GgafLibProperties::DIR_WALL  = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_WALL + "/" ;
std::string GgafLibProperties::DIR_SPLINE = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_SPLINE + "/" ;

int GgafLibProperties::OCTREE_LEVEL = 1;
int GgafLibProperties::QUADTREE_LEVEL = 1;

bool GgafLibProperties::IS_HIT_CHECK_3D = true;
bool GgafLibProperties::IS_HIT_CHECK_2D = false;

void GgafLibProperties::load(std::string prm_properties_filename) {
    GgafDxProperties::load(prm_properties_filename);
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_WALL")) {
        GgafLibProperties::DIRNAME_RESOURCE_WALL   = getStr("DIRNAME_RESOURCE_WALL");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SPLINE")) {
        GgafLibProperties::DIRNAME_RESOURCE_SPLINE  = getStr("DIRNAME_RESOURCE_SPLINE");
    }

    if (GgafProperties::isExistKey("IS_HIT_CHECK_3D") && GgafProperties::isExistKey("IS_HIT_CHECK_2D")) {
        GgafLibProperties::IS_HIT_CHECK_3D = getBool("IS_HIT_CHECK_3D");
        GgafLibProperties::IS_HIT_CHECK_2D = getBool("IS_HIT_CHECK_2D");
        if (GgafLibProperties::IS_HIT_CHECK_3D == GgafLibProperties::IS_HIT_CHECK_2D) {
            throwGgafCriticalException("IS_HIT_CHECK_3D と IS_HIT_CHECK_2D は、必ずどちらか一方のみを true に設定してください。");
        }
    } else {
        if (GgafProperties::isExistKey("IS_HIT_CHECK_3D")) {
            GgafLibProperties::IS_HIT_CHECK_3D = getBool("IS_HIT_CHECK_3D");
            GgafLibProperties::IS_HIT_CHECK_2D = ! GgafLibProperties::IS_HIT_CHECK_3D;
        }
        if (GgafProperties::isExistKey("IS_HIT_CHECK_2D")) {
            GgafLibProperties::IS_HIT_CHECK_2D = getBool("IS_HIT_CHECK_2D");
            GgafLibProperties::IS_HIT_CHECK_3D = ! GgafLibProperties::IS_HIT_CHECK_2D;
        }
    }

    if (GgafProperties::isExistKey("OCTREE_LEVEL")) {
        GgafLibProperties::OCTREE_LEVEL  = getInt("OCTREE_LEVEL");
    }

    if (GgafProperties::isExistKey("QUADTREE_LEVEL")) {
        GgafLibProperties::QUADTREE_LEVEL  = getInt("QUADTREE_LEVEL");
    }

    GgafLibProperties::DIR_WALL   = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_WALL   + "/";
    GgafLibProperties::DIR_SPLINE = GgafProperties::DIR_RESOURCE + "/" + GgafLibProperties::DIRNAME_RESOURCE_SPLINE + "/";

    UTIL::strReplace(GgafLibProperties::DIR_WALL, "//", "/");
    UTIL::strReplace(GgafLibProperties::DIR_SPLINE , "//", "/");

    //指定があるのならば、ディレクトリ存在チェック
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_WALL")) {
        if (!PathFileExists(GgafLibProperties::DIR_WALL.c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_WALL("<<GgafLibProperties::DIR_WALL<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SPLINE")) {
        if (!PathFileExists(GgafLibProperties::DIR_SPLINE.c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_WALL("<<GgafLibProperties::DIR_SPLINE<<") のディレクトリが見つかりません。");
        }
    }

    _TRACE_("GgafLibProperties::DIRNAME_RESOURCE_WALL=" << GgafLibProperties::DIRNAME_RESOURCE_WALL);
    _TRACE_("GgafLibProperties::DIRNAME_RESOURCE_SPLINE=" << GgafLibProperties::DIRNAME_RESOURCE_SPLINE);
    _TRACE_("GgafLibProperties::DIR_WALL=" << GgafLibProperties::DIR_WALL);
    _TRACE_("GgafLibProperties::DIR_SPLINE=" << GgafLibProperties::DIR_SPLINE);
    _TRACE_("GgafLibProperties::IS_HIT_CHECK_3D=" << GgafLibProperties::IS_HIT_CHECK_3D);
    _TRACE_("GgafLibProperties::IS_HIT_CHECK_2D=" << GgafLibProperties::IS_HIT_CHECK_2D);
    _TRACE_("GgafLibProperties::OCTREE_LEVEL=" << GgafLibProperties::OCTREE_LEVEL);
    _TRACE_("GgafLibProperties::QUADTREE_LEVEL=" << GgafLibProperties::QUADTREE_LEVEL);

}

