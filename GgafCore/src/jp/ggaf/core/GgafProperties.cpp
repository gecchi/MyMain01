#include "jp/ggaf/core/GgafProperties.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "Shlwapi.h"


using namespace GgafCore;

GgafProperties::GgafProperties() : GgafObject() {

}

void GgafProperties::read(std::string prm_properties_filename) {
    UTIL::readProperties(prm_properties_filename, _mapProperties);
}

void GgafProperties::write(std::string prm_properties_filename) {
    UTIL::writeProperties(prm_properties_filename.c_str(), _mapProperties);
}

std::string GgafProperties::getStr(std::string prm_key) {
    if (isExistKey(prm_key)) {
        std::string* r = NEW std::string(_mapProperties[prm_key].c_str());
        std::string val = *r; //�R�s�[
        GGAF_DELETE(r);
        return val;
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

float GgafProperties::getFloat(std::string prm_key) {
    if (isExistKey(prm_key)) {
        float ret = (float)atof(_mapProperties[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }

}
int GgafProperties::getInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        int ret = (int)(atoi(_mapProperties[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

uint32_t GgafProperties::getUInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        uint32_t ret = (uint32_t)(atof(_mapProperties[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

bool GgafProperties::getBool(std::string prm_key) {
    if (isExistKey(prm_key)) {
        return UTIL::cnvBool(_mapProperties[prm_key]);
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

double GgafProperties::getDouble(std::string prm_key) {
    if (isExistKey(prm_key)) {
        double ret = atof(_mapProperties[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

GgafRgb GgafProperties::getRGB(std::string prm_key) {
    if (isExistKey(prm_key)) {
        GgafRgb rgb = GgafRgb(prm_key);
        return rgb; //2��R�s�[�����d���Ȃ��B
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

void GgafProperties::setValue(std::string prm_key, int prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("Error! �v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

void GgafProperties::setValue(std::string prm_key, uint32_t prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("�v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

void GgafProperties::setValue(std::string prm_key, std::string prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = prm_value;
    } else {
        throwGgafCriticalException("�v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

void GgafProperties::setValue(std::string prm_key, float prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("�v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

void GgafProperties::setValue(std::string prm_key, double prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("�v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

void GgafProperties::setValue(std::string prm_key, bool prm_value) {
    if (isExistKey(prm_key)) {
        if (prm_value) {
            _mapProperties[prm_key] = "true";
        } else {
            _mapProperties[prm_key] = "false";
        }
    } else {
        throwGgafCriticalException("�v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

void GgafProperties::setValue(std::string prm_key, GgafRgb prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = prm_value.toStr();
    } else {
        throwGgafCriticalException("�v���p�e�B�ɁA�L�[("<<prm_key<<")�����݂��܂���B");
    }
}

bool GgafProperties::isExistKey(std::string prm_key) {
    return _mapProperties.find(prm_key) != _mapProperties.end() ? true :false;
}

