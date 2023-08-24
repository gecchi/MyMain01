#include "jp/ggaf/core/Config.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"
#include <Shlwapi.h>


using namespace GgafCore;

std::string Config::_load_properties_filename = "";
Properties Config::_properties;
frame Config::FPS = 60;
double Config::FRAME_SEC = 1.0 / Config::FPS;
frame Config::END_DELAY_FRAME = 5400;
frame Config::MAX_SKIP_FRAME = 20;
uint32_t Config::OBJNUM_TO_SLOWDOWN1 = 99999;
uint32_t Config::OBJNUM_TO_SLOWDOWN2 = 99999;
double Config::RATE_OF_SLOWDOWN1 = 1.0;
double Config::RATE_OF_SLOWDOWN2 = 1.0;
float Config::FPS_TO_CLEAN_GARBAGE_BOX = 41.0f;
std::string Config::DIR_RESOURCE = "./";
std::string Config::DIRNAME_RESOURCE_SKIN = ".";
std::string Config::DIRNAME_RESOURCE_SKIN_SYSTEM = ".";
std::string Config::DIRNAME_RESOURCE_SKIN_USER = "";
std::string Config::DIR_SKIN = Config::DIR_RESOURCE + "/" + Config::DIRNAME_RESOURCE_SKIN + "/";
std::string Config::DIR_SKIN_KIND[] = {
                Config::DIR_SKIN + "/" + Config::DIRNAME_RESOURCE_SKIN_SYSTEM + "/",
                Config::DIR_SKIN + "/" + Config::DIRNAME_RESOURCE_SKIN_USER + "/",
                Config::DIR_SKIN + "/"
            };

#ifdef _MSC_VER
volatile bool Config::_is_lock = false;
#else
volatile std::atomic<bool> Config::_is_lock(false);
#endif

#define WAIT_LOCK do { \
wait: \
if (GgafCore::Config::_is_lock) { Sleep(1); goto wait; } \
} while(0)

void Config::loadProperties(std::string prm_properties_filename) {
    WAIT_LOCK;
    Config::_is_lock = true;
    _properties.read(prm_properties_filename);

    Config::_load_properties_filename = prm_properties_filename;
    if (_properties.isExistKey("FPS")) {
        Config::FPS = _properties.getUInt("FPS");
    }
    Config::FRAME_SEC = 1.0 / CONFIG::FPS;
    if (_properties.isExistKey("END_DELAY_FRAME")) {
        Config::END_DELAY_FRAME = _properties.getUInt("END_DELAY_FRAME");
    }
    if (_properties.isExistKey("MAX_SKIP_FRAME")) {
        Config::MAX_SKIP_FRAME = _properties.getUInt("MAX_SKIP_FRAME");
    }
    if (_properties.isExistKey("OBJNUM_TO_SLOWDOWN1")) {
        Config::OBJNUM_TO_SLOWDOWN1 = _properties.getUInt("OBJNUM_TO_SLOWDOWN1");
    }
    if (_properties.isExistKey("OBJNUM_TO_SLOWDOWN2")) {
        Config::OBJNUM_TO_SLOWDOWN2 = _properties.getUInt("OBJNUM_TO_SLOWDOWN2");
    }
    if (_properties.isExistKey("RATE_OF_SLOWDOWN1")) {
        Config::RATE_OF_SLOWDOWN1 = _properties.getDouble("RATE_OF_SLOWDOWN1");
    }
    if (_properties.isExistKey("RATE_OF_SLOWDOWN2")) {
        Config::RATE_OF_SLOWDOWN2 = _properties.getDouble("RATE_OF_SLOWDOWN2");
    }

    if (_properties.isExistKey("FPS_TO_CLEAN_GARBAGE_BOX")) {
        Config::FPS_TO_CLEAN_GARBAGE_BOX = _properties.getFloat("FPS_TO_CLEAN_GARBAGE_BOX");
    }
    if (_properties.isExistKey("DIR_RESOURCE")) {
        Config::DIR_RESOURCE = _properties.getStr("DIR_RESOURCE");
    }
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN")) {
        Config::DIRNAME_RESOURCE_SKIN = _properties.getStr("DIRNAME_RESOURCE_SKIN");
    }
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN_SYSTEM")) {
        Config::DIRNAME_RESOURCE_SKIN_SYSTEM = _properties.getStr("DIRNAME_RESOURCE_SKIN_SYSTEM");
    }
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN_USER")) {
        Config::DIRNAME_RESOURCE_SKIN_USER = _properties.getStr("DIRNAME_RESOURCE_SKIN_USER");
    }

    Config::DIR_SKIN = Config::DIR_RESOURCE + "/" + Config::DIRNAME_RESOURCE_SKIN  + "/";
    UTIL::strReplace(Config::DIR_SKIN, "//", "/");

    Config::DIR_SKIN_KIND[0] = Config::DIR_SKIN + "/" + Config::DIRNAME_RESOURCE_SKIN_SYSTEM + "/";
    UTIL::strReplace(Config::DIR_SKIN_KIND[0], "//", "/");

    if (Config::DIRNAME_RESOURCE_SKIN_USER == "") {
        //ユーザースキンディレクトリー名指定無しの場合、DIR_SKIN_KIND[0] と同じにする。
        Config::DIR_SKIN_KIND[1] = Config::DIR_SKIN_KIND[0];
    } else {
        //ユーザースキンディレクトリー名指定有りの場合
        Config::DIR_SKIN_KIND[1] = Config::DIR_SKIN + "/" + Config::DIRNAME_RESOURCE_SKIN_USER + "/";
    }
    UTIL::strReplace(Config::DIR_SKIN_KIND[1], "//", "/");

    //スキンディレクトリー直下
    Config::DIR_SKIN_KIND[2] = Config::DIR_SKIN + "/";
    UTIL::strReplace(Config::DIR_SKIN_KIND[2], "//", "/");

    //DIR存在チェック
    if (!PathFileExists(Config::DIR_SKIN.c_str()) ) {
        throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_SKIN("<<Config::DIR_SKIN<<") のディレクトリが見つかりません。");
    }

    if (Config::DIRNAME_RESOURCE_SKIN_USER == "") {

    } else {
        //ユーザースキンディレクトリー名指定有りの場合、システムスキンの存在チェック
        if (!PathFileExists(Config::DIR_SKIN_KIND[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIRNAME_RESOURCE_SKIN_USERを指定しましたが、\n("<<Config::DIR_SKIN_KIND[1]<<") のディレクトリが見つかりません。");
        }
    }
    Config::_is_lock = false;
    _TRACE_("Config::FPS="<<Config::FPS);
    _TRACE_("Config::END_DELAY_FRAME="<<Config::END_DELAY_FRAME);
    _TRACE_("Config::MAX_SKIP_FRAME="<<Config::MAX_SKIP_FRAME);
    _TRACE_("Config::OBJNUM_TO_SLOWDOWN1="<<Config::OBJNUM_TO_SLOWDOWN1);
    _TRACE_("Config::OBJNUM_TO_SLOWDOWN2="<<Config::OBJNUM_TO_SLOWDOWN2);
    _TRACE_("Config::RATE_OF_SLOWDOWN1="<<Config::RATE_OF_SLOWDOWN1);
    _TRACE_("Config::RATE_OF_SLOWDOWN2="<<Config::RATE_OF_SLOWDOWN2);
    _TRACE_("Config::FPS_TO_CLEAN_GARBAGE_BOX="<<Config::FPS_TO_CLEAN_GARBAGE_BOX);
    _TRACE_("Config::DIR_RESOURCE="<<Config::DIR_RESOURCE);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN="<<Config::DIRNAME_RESOURCE_SKIN);
    _TRACE_("Config::DIR_SKIN="<<Config::DIR_SKIN);
    _TRACE_("Config::DIR_SKIN_KIND[0]="<<Config::DIR_SKIN_KIND[0]);
    _TRACE_("Config::DIR_SKIN_KIND[1]="<<Config::DIR_SKIN_KIND[1]);
}

