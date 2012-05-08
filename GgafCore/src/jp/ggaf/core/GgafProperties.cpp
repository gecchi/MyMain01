#include "stdafx.h"

using namespace GgafCore;

GgafStrMap* GgafProperties::_pMapProperties = NULL;

UINT32 GgafProperties::MAX_SKIP_FRAME = 12;
int GgafProperties::DRAWNUM_TO_SLOWDOWN1 = 350;
int GgafProperties::DRAWNUM_TO_SLOWDOWN2 = 500;
float GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = 50.0f;

void GgafProperties::load(std::string prm_properties_filename) {
    if (_pMapProperties == NULL) {
        _pMapProperties = NEW GgafStrMap();
        GgafUtil::readProperties(prm_properties_filename, _pMapProperties);
//        if (ret != 0) {
//            throwGgafCriticalException("GgafProperties::load() Error! "<<prm_properties_filename<<"��read()�Ɏ��s�B�X�e�[�g��"<<ret);
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

std::string GgafProperties::getStr(std::string prm_key) {
    if (isExistKey(prm_key)) {
        std::string* r = NEW std::string((*_pMapProperties)[prm_key].c_str());
        std::string val = *r;
        DELETE_IMPOSSIBLE_NULL(r);
        return val;
    } else {
        throwGgafCriticalException("GgafProperties::getStr() Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}
float GgafProperties::getFloat(std::string prm_key) {
    if (isExistKey(prm_key)) {
        float ret = (float)atof((*_pMapProperties)[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }

}
int GgafProperties::getInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        int ret = (int)(atoi((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

UINT32 GgafProperties::getUInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        UINT32 ret = (UINT32)(_atoi64((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getUInt() Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

bool GgafProperties::getBool(std::string prm_key) {
    if (isExistKey(prm_key)) {
        return GgafUtil::cnvBool((*_pMapProperties)[prm_key]);
    } else {
        throwGgafCriticalException("GgafProperties::getBool() Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

double GgafProperties::getDouble(std::string prm_key) {
    if (isExistKey(prm_key)) {
        double ret = atof((*_pMapProperties)[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getDouble() Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

GgafRgb GgafProperties::getRGB(std::string prm_key) {
    if (isExistKey(prm_key)) {
        GgafRgb rgb = GgafRgb(prm_key);
        return rgb; //2��R�s�[�����d���Ȃ��B
    } else {
        throwGgafCriticalException("GgafProperties::getRGB() Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}


bool GgafProperties::isExistKey(std::string prm_key) {
    //__map__<std::string, std::string>::iterator
    GgafStrMap::iterator itr;
    itr = _pMapProperties->find(prm_key);
    if (itr != _pMapProperties->end()) {
        return true;
    } else {
        return false;
    }
}
