#include "jp/ggaf/lib/GgafLibConfig.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

std::string GgafLibConfig::DIRNAME_RESOURCE_WALL = "wall";
std::string GgafLibConfig::DIRNAME_RESOURCE_SPLINE = "spline";
std::string GgafLibConfig::DIR_WALL  = GgafConfig::DIR_RESOURCE + "/" + GgafLibConfig::DIRNAME_RESOURCE_WALL + "/" ;
std::string GgafLibConfig::DIR_SPLINE = GgafConfig::DIR_RESOURCE + "/" + GgafLibConfig::DIRNAME_RESOURCE_SPLINE + "/" ;

int GgafLibConfig::OCTREE_LEVEL = 1;
int GgafLibConfig::QUADTREE_LEVEL = 1;

bool GgafLibConfig::IS_HIT_CHECK_3D = true;
bool GgafLibConfig::IS_HIT_CHECK_2D = false;

void GgafLibConfig::loadProperties(std::string prm_properties_filename) {
    GgafDxConfig::loadProperties(prm_properties_filename);
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_WALL")) {
        GgafLibConfig::DIRNAME_RESOURCE_WALL   = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_WALL");
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SPLINE")) {
        GgafLibConfig::DIRNAME_RESOURCE_SPLINE  = GgafConfig::_properties.getStr("DIRNAME_RESOURCE_SPLINE");
    }

    if (GgafConfig::_properties.isExistKey("IS_HIT_CHECK_3D") && GgafConfig::_properties.isExistKey("IS_HIT_CHECK_2D")) {
        GgafLibConfig::IS_HIT_CHECK_3D = GgafConfig::_properties.getBool("IS_HIT_CHECK_3D");
        GgafLibConfig::IS_HIT_CHECK_2D = GgafConfig::_properties.getBool("IS_HIT_CHECK_2D");
        if (GgafLibConfig::IS_HIT_CHECK_3D == GgafLibConfig::IS_HIT_CHECK_2D) {
            throwGgafCriticalException("IS_HIT_CHECK_3D と IS_HIT_CHECK_2D は、必ずどちらか一方のみを true に設定してください。");
        }
    } else {
        if (GgafConfig::_properties.isExistKey("IS_HIT_CHECK_3D")) {
            GgafLibConfig::IS_HIT_CHECK_3D = GgafConfig::_properties.getBool("IS_HIT_CHECK_3D");
            GgafLibConfig::IS_HIT_CHECK_2D = ! GgafLibConfig::IS_HIT_CHECK_3D;
        }
        if (GgafConfig::_properties.isExistKey("IS_HIT_CHECK_2D")) {
            GgafLibConfig::IS_HIT_CHECK_2D = GgafConfig::_properties.getBool("IS_HIT_CHECK_2D");
            GgafLibConfig::IS_HIT_CHECK_3D = ! GgafLibConfig::IS_HIT_CHECK_2D;
        }
    }

    if (GgafConfig::_properties.isExistKey("OCTREE_LEVEL")) {
        GgafLibConfig::OCTREE_LEVEL  = GgafConfig::_properties.getInt("OCTREE_LEVEL");
    }

    if (GgafConfig::_properties.isExistKey("QUADTREE_LEVEL")) {
        GgafLibConfig::QUADTREE_LEVEL  = GgafConfig::_properties.getInt("QUADTREE_LEVEL");
    }

    GgafLibConfig::DIR_WALL   = GgafConfig::DIR_RESOURCE + "/" + GgafLibConfig::DIRNAME_RESOURCE_WALL   + "/";
    GgafLibConfig::DIR_SPLINE = GgafConfig::DIR_RESOURCE + "/" + GgafLibConfig::DIRNAME_RESOURCE_SPLINE + "/";

    UTIL::strReplace(GgafLibConfig::DIR_WALL, "//", "/");
    UTIL::strReplace(GgafLibConfig::DIR_SPLINE , "//", "/");

    //指定があるのならば、ディレクトリ存在チェック
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_WALL")) {
        if (!PathFileExists(GgafLibConfig::DIR_WALL.c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_WALL("<<GgafLibConfig::DIR_WALL<<") のディレクトリが見つかりません。");
        }
    }
    if (GgafConfig::_properties.isExistKey("DIRNAME_RESOURCE_SPLINE")) {
        if (!PathFileExists(GgafLibConfig::DIR_SPLINE.c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_WALL("<<GgafLibConfig::DIR_SPLINE<<") のディレクトリが見つかりません。");
        }
    }

    _TRACE_("GgafLibConfig::DIRNAME_RESOURCE_WALL=" << GgafLibConfig::DIRNAME_RESOURCE_WALL);
    _TRACE_("GgafLibConfig::DIRNAME_RESOURCE_SPLINE=" << GgafLibConfig::DIRNAME_RESOURCE_SPLINE);
    _TRACE_("GgafLibConfig::DIR_WALL=" << GgafLibConfig::DIR_WALL);
    _TRACE_("GgafLibConfig::DIR_SPLINE=" << GgafLibConfig::DIR_SPLINE);
    _TRACE_("GgafLibConfig::IS_HIT_CHECK_3D=" << GgafLibConfig::IS_HIT_CHECK_3D);
    _TRACE_("GgafLibConfig::IS_HIT_CHECK_2D=" << GgafLibConfig::IS_HIT_CHECK_2D);
    _TRACE_("GgafLibConfig::OCTREE_LEVEL=" << GgafLibConfig::OCTREE_LEVEL);
    _TRACE_("GgafLibConfig::QUADTREE_LEVEL=" << GgafLibConfig::QUADTREE_LEVEL);

}

