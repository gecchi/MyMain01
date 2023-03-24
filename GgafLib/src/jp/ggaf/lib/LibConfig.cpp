#include "jp/ggaf/lib/LibConfig.h"

#include <Shlwapi.h>

using namespace GgafLib;

std::string LibConfig::DIRNAME_RESOURCE_WALL = "wall";
std::string LibConfig::DIR_WALL  = GgafCore::Config::DIR_RESOURCE + "/" + LibConfig::DIRNAME_RESOURCE_WALL + "/" ;

void LibConfig::loadProperties(std::string prm_properties_filename) {
    GgafDx::Config::loadProperties(prm_properties_filename);
    if (LibConfig::_properties.isExistKey("DIRNAME_RESOURCE_WALL")) {
        LibConfig::DIRNAME_RESOURCE_WALL   = LibConfig::_properties.getStr("DIRNAME_RESOURCE_WALL");
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
}

