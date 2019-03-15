#include "jp/ggaf/core/Config.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"
#include "Shlwapi.h"


using namespace GgafCore;

Properties Config::_properties;

uint32_t Config::MAX_SKIP_FRAME = 20;
uint32_t Config::OBJNUM_TO_SLOWDOWN1 = 1000;
uint32_t Config::OBJNUM_TO_SLOWDOWN2 = 1500;
float Config::FPS_TO_CLEAN_GARBAGE_BOX = 30.0f;
std::string Config::DIR_RESOURCE = "./";
std::string Config::DIRNAME_RESOURCE_SKIN = ".";
std::string Config::DIRNAME_RESOURCE_SKIN_DEFAULT = ".";
std::string Config::DIRNAME_RESOURCE_SKIN_USER = "";
std::string Config::DIR_SKIN = Config::DIR_RESOURCE + "/" + Config::DIRNAME_RESOURCE_SKIN + "/";
std::string Config::DIR_SKIN_KIND[] = {
                Config::DIR_SKIN + "/" + Config::DIRNAME_RESOURCE_SKIN_DEFAULT + "/",
                "",
                "./"
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

    if (_properties.isExistKey("MAX_SKIP_FRAME")) {
        Config::MAX_SKIP_FRAME = _properties.getUInt("MAX_SKIP_FRAME");
    }
    if (_properties.isExistKey("OBJNUM_TO_SLOWDOWN1")) {
        Config::OBJNUM_TO_SLOWDOWN1 = _properties.getUInt("OBJNUM_TO_SLOWDOWN1");
    }
    if (_properties.isExistKey("OBJNUM_TO_SLOWDOWN2")) {
        Config::OBJNUM_TO_SLOWDOWN2 = _properties.getUInt("OBJNUM_TO_SLOWDOWN2");
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
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN_DEFAULT")) {
        Config::DIRNAME_RESOURCE_SKIN_DEFAULT = _properties.getStr("DIRNAME_RESOURCE_SKIN_DEFAULT");
    }
    if (_properties.isExistKey("DIRNAME_RESOURCE_SKIN_USER")) {
        Config::DIRNAME_RESOURCE_SKIN_USER = _properties.getStr("DIRNAME_RESOURCE_SKIN_USER");
    }

    Config::DIR_SKIN = Config::DIR_RESOURCE + "/" + Config::DIRNAME_RESOURCE_SKIN  + "/";
    UTIL::strReplace(Config::DIR_SKIN, "//", "/");

    Config::DIR_SKIN_KIND[0] = Config::DIR_SKIN + "/" + Config::DIRNAME_RESOURCE_SKIN_DEFAULT + "/";
    UTIL::strReplace(Config::DIR_SKIN_KIND[0], "//", "/");

    if (Config::DIRNAME_RESOURCE_SKIN_USER == "") {
        //���[�U�[�X�L���f�B���N�g���[���w�薳���̏ꍇ
        Config::DIR_SKIN_KIND[1] = Config::DIR_SKIN_KIND[0];
    } else {
        //���[�U�[�X�L���f�B���N�g���[���w��L��̏ꍇ
        Config::DIR_SKIN_KIND[1] = Config::DIR_SKIN + "/" + Config::DIRNAME_RESOURCE_SKIN_USER + "/";
    }
    UTIL::strReplace(Config::DIR_SKIN_KIND[1], "//", "/");

    Config::DIR_SKIN_KIND[2] = "./";
    UTIL::strReplace(Config::DIR_SKIN_KIND[2], "//", "/");

    //DIR���݃`�F�b�N
    if (!PathFileExists(Config::DIR_SKIN.c_str()) ) {
        throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIR_SKIN("<<Config::DIR_SKIN<<") �̃f�B���N�g����������܂���B");
    }

    if (Config::DIRNAME_RESOURCE_SKIN_USER == "") {

    } else {
        //���[�U�[�X�L���f�B���N�g���[���w��L��̏ꍇ�A�f�t�H���g�X�L���̑��݃`�F�b�N
        if (!PathFileExists(Config::DIR_SKIN_KIND[0].c_str()) ) {
            throwCriticalException("prm_properties_filename="<<prm_properties_filename<<" DIRNAME_RESOURCE_SKIN_USER���w�肵�܂������A\n("<<Config::DIR_SKIN_KIND[1]<<") �̃f�B���N�g����������܂���B");
        }
    }
    Config::_is_lock = false;
    _TRACE_("Config::MAX_SKIP_FRAME="<<Config::MAX_SKIP_FRAME);
    _TRACE_("Config::OBJNUM_TO_SLOWDOWN1="<<Config::OBJNUM_TO_SLOWDOWN1);
    _TRACE_("Config::OBJNUM_TO_SLOWDOWN2="<<Config::OBJNUM_TO_SLOWDOWN2);
    _TRACE_("Config::FPS_TO_CLEAN_GARBAGE_BOX="<<Config::FPS_TO_CLEAN_GARBAGE_BOX);
    _TRACE_("Config::DIR_RESOURCE="<<Config::DIR_RESOURCE);
    _TRACE_("Config::DIRNAME_RESOURCE_SKIN="<<Config::DIRNAME_RESOURCE_SKIN);
    _TRACE_("Config::DIR_SKIN="<<Config::DIR_SKIN);
    _TRACE_("Config::DIR_SKIN_KIND[0]="<<Config::DIR_SKIN_KIND[0]);
    _TRACE_("Config::DIR_SKIN_KIND[1]="<<Config::DIR_SKIN_KIND[1]);
}
