#include "jp/ggaf/lib/LibConfig.h"

#include <Shlwapi.h>

using namespace GgafLib;

std::string LibConfig::DIRNAME_RESOURCE_WALL = "wall";
std::string LibConfig::DIR_WALL  = GgafCore::Config::DIR_RESOURCE + "/" + LibConfig::DIRNAME_RESOURCE_WALL + "/" ;

int LibConfig::WORLD_HIT_CHECK_OCTREE_LEVEL = 2;
int LibConfig::WORLD_HIT_CHECK_QUADTREE_LEVEL = 2;
int LibConfig::VIEW_HIT_CHECK_QUADTREE_LEVEL = 2;
bool LibConfig::ENABLE_WORLD_HIT_CHECK_2D = false;

void LibConfig::loadProperties(std::string prm_properties_filename) {
    GgafDx::Config::loadProperties(prm_properties_filename);
    if (LibConfig::_properties.isExistKey("DIRNAME_RESOURCE_WALL")) {
        LibConfig::DIRNAME_RESOURCE_WALL   = LibConfig::_properties.getStr("DIRNAME_RESOURCE_WALL");
    }

    if (LibConfig::_properties.isExistKey("ENABLE_WORLD_HIT_CHECK_2D")) {
        LibConfig::ENABLE_WORLD_HIT_CHECK_2D = LibConfig::_properties.getBool("ENABLE_WORLD_HIT_CHECK_2D");
    }

    if (LibConfig::ENABLE_WORLD_HIT_CHECK_2D) {
        if (LibConfig::_properties.isExistKey("WORLD_HIT_CHECK_QUADTREE_LEVEL")) {
            LibConfig::WORLD_HIT_CHECK_QUADTREE_LEVEL  = LibConfig::_properties.getInt("WORLD_HIT_CHECK_QUADTREE_LEVEL");
        }
        if (LibConfig::_properties.isExistKey("WORLD_HIT_CHECK_OCTREE_LEVEL")) {
            throwCriticalException("ENABLE_WORLD_HIT_CHECK_2D が ture の場合、WORLD_HIT_CHECK_OCTREE_LEVEL は設定できません。(WORLD_HIT_CHECK_QUADTREE_LEVEL を設定してください。)");
        }
    } else {
        if (LibConfig::_properties.isExistKey("WORLD_HIT_CHECK_QUADTREE_LEVEL")) {
            throwCriticalException("ENABLE_WORLD_HIT_CHECK_2D が false の場合、WORLD_HIT_CHECK_QUADTREE_LEVEL は設定できません。(WORLD_HIT_CHECK_OCTREE_LEVEL を設定してください。)");
        }
        if (LibConfig::_properties.isExistKey("WORLD_HIT_CHECK_OCTREE_LEVEL")) {
            LibConfig::WORLD_HIT_CHECK_OCTREE_LEVEL  = LibConfig::_properties.getInt("WORLD_HIT_CHECK_OCTREE_LEVEL");
        }
    }
    if (LibConfig::_properties.isExistKey("VIEW_HIT_CHECK_QUADTREE_LEVEL")) {
        LibConfig::VIEW_HIT_CHECK_QUADTREE_LEVEL  = LibConfig::_properties.getInt("VIEW_HIT_CHECK_QUADTREE_LEVEL");
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
    _TRACE_("LibConfig::ENABLE_WORLD_HIT_CHECK_2D=" << LibConfig::ENABLE_WORLD_HIT_CHECK_2D);
    _TRACE_("LibConfig::WORLD_HIT_CHECK_OCTREE_LEVEL=" << LibConfig::WORLD_HIT_CHECK_OCTREE_LEVEL);
    _TRACE_("LibConfig::WORLD_HIT_CHECK_QUADTREE_LEVEL=" << LibConfig::WORLD_HIT_CHECK_QUADTREE_LEVEL);
}

