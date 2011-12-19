#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafStrMap* GgafProperties::_pMapProperties = NULL;

UINT32 GgafProperties::MAX_SKIP_FRAME = 0;
int GgafProperties::DRAWNUM_TO_SLOWDOWN1 = 0;
int GgafProperties::DRAWNUM_TO_SLOWDOWN2 = 0;
float GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = 55.0f;
void GgafProperties::load(string prm_properties_filename) {
    if (_pMapProperties == NULL) {
        _pMapProperties = NEW GgafStrMap();
        GgafUtil::readProperties(prm_properties_filename, _pMapProperties);
//        if (ret != 0) {
//            throwGgafCriticalException("GgafProperties::load() Error! "<<prm_properties_filename<<"のread()に失敗。ステート→"<<ret);
//        }
    }

    GgafProperties::MAX_SKIP_FRAME = getUInt("MAX_SKIP_FRAME");
    GgafProperties::DRAWNUM_TO_SLOWDOWN1 = getInt("DRAWNUM_TO_SLOWDOWN1");
    GgafProperties::DRAWNUM_TO_SLOWDOWN2 = getInt("DRAWNUM_TO_SLOWDOWN2");
    GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = getFloat("FPS_TO_CLEAN_GARBAGE_BOX");
    _TRACE_("GgafProperties::MAX_SKIP_FRAME="<<GgafProperties::MAX_SKIP_FRAME);
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN1="<<GgafProperties::DRAWNUM_TO_SLOWDOWN1);
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN2="<<GgafProperties::DRAWNUM_TO_SLOWDOWN2);
    _TRACE_("GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX="<<GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX);
    GgafUtil::writeProperties("back.properties", _pMapProperties);
}

void GgafProperties::clean() {
    _TRACE_("Properties::clean()");
    DELETE_IMPOSSIBLE_NULL(_pMapProperties);
}

string GgafProperties::getStr(string prm_key) {
    if (isExistKey(prm_key)) {
        string* r = NEW string((*_pMapProperties)[prm_key].c_str());
        string val = *r;
        DELETE_IMPOSSIBLE_NULL(r);
        return val;
    } else {
        throwGgafCriticalException("GgafProperties::getStr() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}
float GgafProperties::getFloat(string prm_key) {
    if (isExistKey(prm_key)) {
        float ret = (float)atof((*_pMapProperties)[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }

}
int GgafProperties::getInt(string prm_key) {
    if (isExistKey(prm_key)) {
        int ret = (int)(atoi((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

UINT32 GgafProperties::getUInt(string prm_key) {
    if (isExistKey(prm_key)) {
        UINT32 ret = (UINT32)(atoi((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getUInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool GgafProperties::getBool(string prm_key) {
    if (isExistKey(prm_key)) {
        return GgafUtil::cnvBool((*_pMapProperties)[prm_key]);
    } else {
        throwGgafCriticalException("GgafProperties::getBool() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

double GgafProperties::getDouble(string prm_key) {
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


bool GgafProperties::isExistKey(string prm_key) {
    //__map__<string, string>::iterator
    GgafStrMap::iterator itr;
    itr = _pMapProperties->find(prm_key);
    if (itr != _pMapProperties->end()) {
        return true;
    } else {
        return false;
    }
}
