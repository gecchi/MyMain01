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
            throwCriticalException("ENABLE_WORLD_HIT_CHECK_2D �� ture �̏ꍇ�AWORLD_HIT_CHECK_OCTREE_LEVEL �͐ݒ�ł��܂���B(WORLD_HIT_CHECK_QUADTREE_LEVEL ��ݒ肵�Ă��������B)");
        }
    } else {
        if (LibConfig::_properties.isExistKey("WORLD_HIT_CHECK_QUADTREE_LEVEL")) {
            throwCriticalException("ENABLE_WORLD_HIT_CHECK_2D �� false �̏ꍇ�AWORLD_HIT_CHECK_QUADTREE_LEVEL �͐ݒ�ł��܂���B(WORLD_HIT_CHECK_OCTREE_LEVEL ��ݒ肵�Ă��������B)");
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

    //�w�肪����̂Ȃ�΁A�f�B���N�g�����݃`�F�b�N
    if (LibConfig::_properties.isExistKey("DIRNAME_RESOURCE_WALL")) {
        if (!PathFileExists(LibConfig::DIR_WALL.c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_WALL("<<LibConfig::DIR_WALL<<") �̃f�B���N�g����������܂���B");
        }
    }
    _TRACE_("LibConfig::DIRNAME_RESOURCE_WALL=" << LibConfig::DIRNAME_RESOURCE_WALL);
    _TRACE_("LibConfig::DIR_WALL=" << LibConfig::DIR_WALL);
    _TRACE_("LibConfig::ENABLE_WORLD_HIT_CHECK_2D=" << LibConfig::ENABLE_WORLD_HIT_CHECK_2D);
    _TRACE_("LibConfig::WORLD_HIT_CHECK_OCTREE_LEVEL=" << LibConfig::WORLD_HIT_CHECK_OCTREE_LEVEL);
    _TRACE_("LibConfig::WORLD_HIT_CHECK_QUADTREE_LEVEL=" << LibConfig::WORLD_HIT_CHECK_QUADTREE_LEVEL);
}

