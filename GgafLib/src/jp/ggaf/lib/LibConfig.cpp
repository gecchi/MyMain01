#include "jp/ggaf/lib/LibConfig.h"

#include <Shlwapi.h>



using namespace GgafLib;

std::string LibConfig::DIRNAME_RESOURCE_WALL = "wall";
std::string LibConfig::DIR_WALL  = GgafCore::Config::DIR_RESOURCE + "/" + LibConfig::DIRNAME_RESOURCE_WALL + "/" ;

int LibConfig::OCTREE_LEVEL = 1;
int LibConfig::QUADTREE_LEVEL = 1;

bool LibConfig::IS_HIT_CHECK_3D = true;
bool LibConfig::IS_HIT_CHECK_2D = false;

void LibConfig::loadProperties(std::string prm_properties_filename) {
    GgafDx::Config::loadProperties(prm_properties_filename);
    if (LibConfig::_properties.isExistKey("DIRNAME_RESOURCE_WALL")) {
        LibConfig::DIRNAME_RESOURCE_WALL   = LibConfig::_properties.getStr("DIRNAME_RESOURCE_WALL");
    }

    if (LibConfig::_properties.isExistKey("IS_HIT_CHECK_3D") && LibConfig::_properties.isExistKey("IS_HIT_CHECK_2D")) {
        LibConfig::IS_HIT_CHECK_3D = LibConfig::_properties.getBool("IS_HIT_CHECK_3D");
        LibConfig::IS_HIT_CHECK_2D = LibConfig::_properties.getBool("IS_HIT_CHECK_2D");
        if (LibConfig::IS_HIT_CHECK_3D == LibConfig::IS_HIT_CHECK_2D) {
            throwCriticalException("IS_HIT_CHECK_3D と IS_HIT_CHECK_2D は、必ずどちらか一方のみを true に設定してください。");
        }
    } else {
        if (LibConfig::_properties.isExistKey("IS_HIT_CHECK_3D")) {
            LibConfig::IS_HIT_CHECK_3D = LibConfig::_properties.getBool("IS_HIT_CHECK_3D");
            LibConfig::IS_HIT_CHECK_2D = ! LibConfig::IS_HIT_CHECK_3D;
        }
        if (LibConfig::_properties.isExistKey("IS_HIT_CHECK_2D")) {
            LibConfig::IS_HIT_CHECK_2D = LibConfig::_properties.getBool("IS_HIT_CHECK_2D");
            LibConfig::IS_HIT_CHECK_3D = ! LibConfig::IS_HIT_CHECK_2D;
        }
    }

    if (LibConfig::_properties.isExistKey("OCTREE_LEVEL")) {
        LibConfig::OCTREE_LEVEL  = LibConfig::_properties.getInt("OCTREE_LEVEL");
    }

    if (LibConfig::_properties.isExistKey("QUADTREE_LEVEL")) {
        LibConfig::QUADTREE_LEVEL  = LibConfig::_properties.getInt("QUADTREE_LEVEL");
    }

    LibConfig::DIR_WALL   = GgafCore::Config::DIR_RESOURCE + "/" + LibConfig::DIRNAME_RESOURCE_WALL   + "/";

    UTIL::strReplace(LibConfig::DIR_WALL, "//", "/");

    //指定があるのならば、ディレクトリ存在チェック
    if (LibConfig::_properties.isExistKey("DIRNAME_RESOURCE_WALL")) {
        if (!PathFileExists(LibConfig::DIR_WALL.c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_WALL("<<LibConfig::DIR_WALL<<") のディレクトリが見つかりません。");
        }
    }

    _TRACE_("LibConfig::DIRNAME_RESOURCE_WALL=" << LibConfig::DIRNAME_RESOURCE_WALL);
    _TRACE_("LibConfig::DIR_WALL=" << LibConfig::DIR_WALL);
    _TRACE_("LibConfig::IS_HIT_CHECK_3D=" << LibConfig::IS_HIT_CHECK_3D);
    _TRACE_("LibConfig::IS_HIT_CHECK_2D=" << LibConfig::IS_HIT_CHECK_2D);
    _TRACE_("LibConfig::OCTREE_LEVEL=" << LibConfig::OCTREE_LEVEL);
    _TRACE_("LibConfig::QUADTREE_LEVEL=" << LibConfig::QUADTREE_LEVEL);

}

