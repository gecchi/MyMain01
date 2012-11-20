#include "stdafx.h"

using namespace GgafCore;

GgafStrMap* GgafProperties::_pMapProperties = nullptr;

UINT32 GgafProperties::MAX_SKIP_FRAME = 12;
int GgafProperties::DRAWNUM_TO_SLOWDOWN1 = 350;
int GgafProperties::DRAWNUM_TO_SLOWDOWN2 = 500;
float GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = 50.0f;
std::string GgafProperties::DIR_RESOURCE = "./";
std::string GgafProperties::DIRNAME_RESOURCE_SKIN = ".";
std::string GgafProperties::DIRNAME_RESOURCE_SKIN_DEFAULT = ".";
std::string GgafProperties::DIRNAME_RESOURCE_SKIN_USER = "";
std::string GgafProperties::DIR_SKIN = GgafProperties::DIR_RESOURCE + "/" + GgafProperties::DIRNAME_RESOURCE_SKIN + "/";
std::string GgafProperties::DIR_SKIN_KIND[] = {
                GgafProperties::DIR_SKIN + "/" + GgafProperties::DIRNAME_RESOURCE_SKIN_DEFAULT + "/",
                "",
                "./"
            };



void GgafProperties::load(std::string prm_properties_filename) {
    if (_pMapProperties == nullptr) {
        _pMapProperties = NEW GgafStrMap();
        UTIL::readProperties(prm_properties_filename, _pMapProperties);
//        if (ret != 0) {
//            throwGgafCriticalException("GgafProperties::load() Error! "<<prm_properties_filename<<"のread()に失敗。ステート→"<<ret);
//        }
    }

    if (GgafProperties::isExistKey("MAX_SKIP_FRAME")) {
        GgafProperties::MAX_SKIP_FRAME = getUInt("MAX_SKIP_FRAME");
    }
    if (GgafProperties::isExistKey("DRAWNUM_TO_SLOWDOWN1")) {
        GgafProperties::DRAWNUM_TO_SLOWDOWN1 = getInt("DRAWNUM_TO_SLOWDOWN1");
    }
    if (GgafProperties::isExistKey("DRAWNUM_TO_SLOWDOWN2")) {
        GgafProperties::DRAWNUM_TO_SLOWDOWN2 = getInt("DRAWNUM_TO_SLOWDOWN2");
    }
    if (GgafProperties::isExistKey("FPS_TO_CLEAN_GARBAGE_BOX")) {
        GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = getFloat("FPS_TO_CLEAN_GARBAGE_BOX");
    }
    if (GgafProperties::isExistKey("DIR_RESOURCE")) {
        GgafProperties::DIR_RESOURCE = getStr("DIR_RESOURCE");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN")) {
        GgafProperties::DIRNAME_RESOURCE_SKIN = getStr("DIRNAME_RESOURCE_SKIN");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_DEFAULT")) {
        GgafProperties::DIRNAME_RESOURCE_SKIN_DEFAULT = getStr("DIRNAME_RESOURCE_SKIN_DEFAULT");
    }
    if (GgafProperties::isExistKey("DIRNAME_RESOURCE_SKIN_USER")) {
        GgafProperties::DIRNAME_RESOURCE_SKIN_USER = getStr("DIRNAME_RESOURCE_SKIN_USER");
    }

    GgafProperties::DIR_SKIN = GgafProperties::DIR_RESOURCE + "/" + GgafProperties::DIRNAME_RESOURCE_SKIN  + "/";
    UTIL::strReplace(GgafProperties::DIR_SKIN, "//", "/");

    GgafProperties::DIR_SKIN_KIND[0] = GgafProperties::DIR_SKIN + "/" + GgafProperties::DIRNAME_RESOURCE_SKIN_DEFAULT + "/";
    UTIL::strReplace(GgafProperties::DIR_SKIN_KIND[0], "//", "/");

    if (GgafProperties::DIRNAME_RESOURCE_SKIN_USER == "") {
        //ユーザースキンディレクトリー名指定無しの場合
        GgafProperties::DIR_SKIN_KIND[1] = GgafProperties::DIR_SKIN_KIND[0];
    } else {
        //ユーザースキンディレクトリー名指定有りの場合
        GgafProperties::DIR_SKIN_KIND[1] = GgafProperties::DIR_SKIN + "/" + GgafProperties::DIRNAME_RESOURCE_SKIN_USER + "/";
    }
    UTIL::strReplace(GgafProperties::DIR_SKIN_KIND[1], "//", "/");

    GgafProperties::DIR_SKIN_KIND[2] = "./";
    UTIL::strReplace(GgafProperties::DIR_SKIN_KIND[2], "//", "/");

    //DIR存在チェック
    if (!PathFileExists(GgafProperties::DIR_SKIN.c_str()) ) {
        throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIR_SKIN("<<GgafProperties::DIR_SKIN<<") のディレクトリが見つかりません。");
    }

    if (GgafProperties::DIRNAME_RESOURCE_SKIN_USER == "") {

    } else {
        //ユーザースキンディレクトリー名指定有りの場合、デフォルトスキンの存在チェック
        if (!PathFileExists(GgafProperties::DIR_SKIN_KIND[0].c_str()) ) {
            throwGgafCriticalException("GgafProperties::load("<<prm_properties_filename<<") DIRNAME_RESOURCE_SKIN_USERを指定しましたが、\n("<<GgafProperties::DIR_SKIN_KIND[1]<<") のディレクトリが見つかりません。");
        }
    }

    _TRACE_("GgafProperties::MAX_SKIP_FRAME="<<GgafProperties::MAX_SKIP_FRAME);
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN1="<<GgafProperties::DRAWNUM_TO_SLOWDOWN1);
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN2="<<GgafProperties::DRAWNUM_TO_SLOWDOWN2);
    _TRACE_("GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX="<<GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX);
    _TRACE_("GgafProperties::DIR_RESOURCE="<<GgafProperties::DIR_RESOURCE);
    _TRACE_("GgafProperties::DIRNAME_RESOURCE_SKIN="<<GgafProperties::DIRNAME_RESOURCE_SKIN);
    _TRACE_("GgafProperties::DIR_SKIN="<<GgafProperties::DIR_SKIN);
    _TRACE_("GgafProperties::DIR_SKIN_KIND[0]="<<GgafProperties::DIR_SKIN_KIND[0]);
    _TRACE_("GgafProperties::DIR_SKIN_KIND[1]="<<GgafProperties::DIR_SKIN_KIND[1]);

    UTIL::writeProperties("back.properties", _pMapProperties);
}

void GgafProperties::clean() {
    _TRACE_("Properties::clean()");
    DELETE_IMPOSSIBLE_NULL(_pMapProperties);
}

std::string GgafProperties::getStr(std::string prm_key) {
    if (isExistKey(prm_key)) {
        std::string* r = NEW std::string((*_pMapProperties)[prm_key].c_str());
        std::string val = *r;
        DELETE_IMPOSSIBLE_NULL(r);
        return val;
    } else {
        throwGgafCriticalException("GgafProperties::getStr() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

float GgafProperties::getFloat(std::string prm_key) {
    if (isExistKey(prm_key)) {
        float ret = (float)atof((*_pMapProperties)[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }

}
int GgafProperties::getInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        int ret = (int)(atoi((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

UINT32 GgafProperties::getUInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        UINT32 ret = (UINT32)(atof((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getUInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool GgafProperties::getBool(std::string prm_key) {
    if (isExistKey(prm_key)) {
        return UTIL::cnvBool((*_pMapProperties)[prm_key]);
    } else {
        throwGgafCriticalException("GgafProperties::getBool() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

double GgafProperties::getDouble(std::string prm_key) {
    if (isExistKey(prm_key)) {
        double ret = atof((*_pMapProperties)[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getDouble() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

GgafRgb GgafProperties::getRGB(std::string prm_key) {
    if (isExistKey(prm_key)) {
        GgafRgb rgb = GgafRgb(prm_key);
        return rgb; //2回コピーだが仕方ない。
    } else {
        throwGgafCriticalException("GgafProperties::getRGB() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}


bool GgafProperties::isExistKey(std::string prm_key) {
    //std::map<std::string, std::string>::iterator
    GgafStrMap::iterator itr;
    itr = _pMapProperties->find(prm_key);
    if (itr != _pMapProperties->end()) {
        return true;
    } else {
        return false;
    }
}
