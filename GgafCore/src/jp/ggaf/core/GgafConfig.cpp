#include "jp/ggaf/core/GgafConfig.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "Shlwapi.h"


using namespace GgafCore;

GgafProperties GgafConfig::_properties;

uint32_t GgafConfig::MAX_SKIP_FRAME = 20;
uint32_t GgafConfig::OBJNUM_TO_SLOWDOWN1 = 1000;
uint32_t GgafConfig::OBJNUM_TO_SLOWDOWN2 = 1500;
float GgafConfig::FPS_TO_CLEAN_GARBAGE_BOX = 30.0f;
std::string GgafConfig::DIR_RESOURCE = "./";
std::string GgafConfig::DIRNAME_RESOURCE_SKIN = ".";
std::string GgafConfig::DIRNAME_RESOURCE_SKIN_DEFAULT = ".";
std::string GgafConfig::DIRNAME_RESOURCE_SKIN_USER = "";
std::string GgafConfig::DIR_SKIN = GgafConfig::DIR_RESOURCE + "/" + GgafConfig::DIRNAME_RESOURCE_SKIN + "/";
std::string GgafConfig::DIR_SKIN_KIND[] = {
                GgafConfig::DIR_SKIN + "/" + GgafConfig::DIRNAME_RESOURCE_SKIN_DEFAULT + "/",
                "",
                "./"
            };

#ifdef _MSC_VER
volatile bool GgafConfig::_is_lock = false;
#else
volatile std::atomic<bool> GgafConfig::_is_lock(false);
#endif

#define WAIT_LOCK do { \
wait: \
if (GgafConfig::_is_lock) { Sleep(1); goto wait; } \
} while(0)

void GgafConfig::loadProperties(std::string prm_properties_filename) {
    WAIT_LOCK;
    GgafConfig::_is_lock = true;

    _properties.read(prm_properties_filename);

    if (_properties.isExistKey("MAX_SKIP_FRAME")) {
        GgafConfig::MAX_SKIP_FRAME = _properties.getUInt("MAX_SKIP_FRAME");
    }
    if (_properties.isExistKey("OBJNUM_TO_SLOWDOWN1")) {
        GgafConfig::OBJNUM_TO_SLOWDOWN1 = _properties.getUInt("OBJNUM_TO_SLOWDOWN1");
    }
    if (_properties.isExistKey("OBJNUM_TO_SLOWDOWN2")) {
        GgafConfig::OBJNUM_TO_SLOWDOWN2 = _properties.getUInt("OBJNUM_TO_SLOWDOWN2");
    }
    if (_properties.isExistKey("FPS_TO_CLEAN_GARBAGE_BOX")) {
        GgafConfig::FPS_TO_CLEAN_GARBAGE_BOX = _properties.getFloat("FPS_TO_CLEAN_GARBAGE_BOX");
    }
    if (_properties.isExistKey("DIR_RESOURCE")) {
        GgafConfig::DIR_RESOURCE = _properties.getStr("DIR_RESOURCE");
    }
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN")) {
        GgafConfig::DIRNAME_RESOURCE_SKIN = _properties.getStr("DIRNAME_RESOURCE_SKIN");
    }
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN_DEFAULT")) {
        GgafConfig::DIRNAME_RESOURCE_SKIN_DEFAULT = _properties.getStr("DIRNAME_RESOURCE_SKIN_DEFAULT");
    }
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN_USER")) {
        GgafConfig::DIRNAME_RESOURCE_SKIN_USER = _properties.getStr("DIRNAME_RESOURCE_SKIN_USER");
    }

    GgafConfig::DIR_SKIN = GgafConfig::DIR_RESOURCE + "/" + GgafConfig::DIRNAME_RESOURCE_SKIN  + "/";
    UTIL::strReplace(GgafConfig::DIR_SKIN, "//", "/");

    GgafConfig::DIR_SKIN_KIND[0] = GgafConfig::DIR_SKIN + "/" + GgafConfig::DIRNAME_RESOURCE_SKIN_DEFAULT + "/";
    UTIL::strReplace(GgafConfig::DIR_SKIN_KIND[0], "//", "/");

    if (GgafConfig::DIRNAME_RESOURCE_SKIN_USER == "") {
        //ユーザースキンディレクトリー名指定無しの場合
        GgafConfig::DIR_SKIN_KIND[1] = GgafConfig::DIR_SKIN_KIND[0];
    } else {
        //ユーザースキンディレクトリー名指定有りの場合
        GgafConfig::DIR_SKIN_KIND[1] = GgafConfig::DIR_SKIN + "/" + GgafConfig::DIRNAME_RESOURCE_SKIN_USER + "/";
    }
    UTIL::strReplace(GgafConfig::DIR_SKIN_KIND[1], "//", "/");

    GgafConfig::DIR_SKIN_KIND[2] = "./";
    UTIL::strReplace(GgafConfig::DIR_SKIN_KIND[2], "//", "/");

    //DIR存在チェック
    if (!PathFileExists(GgafConfig::DIR_SKIN.c_str()) ) {
        throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_SKIN("<<GgafConfig::DIR_SKIN<<") のディレクトリが見つかりません。");
    }

    if (GgafConfig::DIRNAME_RESOURCE_SKIN_USER == "") {

    } else {
        //ユーザースキンディレクトリー名指定有りの場合、デフォルトスキンの存在チェック
        if (!PathFileExists(GgafConfig::DIR_SKIN_KIND[0].c_str()) ) {
            throwGgafCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIRNAME_RESOURCE_SKIN_USERを指定しましたが、\n("<<GgafConfig::DIR_SKIN_KIND[1]<<") のディレクトリが見つかりません。");
        }
    }
    GgafConfig::_is_lock = false;
    _TRACE_("GgafConfig::MAX_SKIP_FRAME="<<GgafConfig::MAX_SKIP_FRAME);
    _TRACE_("GgafConfig::OBJNUM_TO_SLOWDOWN1="<<GgafConfig::OBJNUM_TO_SLOWDOWN1);
    _TRACE_("GgafConfig::OBJNUM_TO_SLOWDOWN2="<<GgafConfig::OBJNUM_TO_SLOWDOWN2);
    _TRACE_("GgafConfig::FPS_TO_CLEAN_GARBAGE_BOX="<<GgafConfig::FPS_TO_CLEAN_GARBAGE_BOX);
    _TRACE_("GgafConfig::DIR_RESOURCE="<<GgafConfig::DIR_RESOURCE);
    _TRACE_("GgafConfig::DIRNAME_RESOURCE_SKIN="<<GgafConfig::DIRNAME_RESOURCE_SKIN);
    _TRACE_("GgafConfig::DIR_SKIN="<<GgafConfig::DIR_SKIN);
    _TRACE_("GgafConfig::DIR_SKIN_KIND[0]="<<GgafConfig::DIR_SKIN_KIND[0]);
    _TRACE_("GgafConfig::DIR_SKIN_KIND[1]="<<GgafConfig::DIR_SKIN_KIND[1]);
}

