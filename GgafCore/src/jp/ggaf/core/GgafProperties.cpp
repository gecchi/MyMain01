#include "jp/ggaf/core/GgafProperties.h"

#include <fstream>
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "Shlwapi.h"


using namespace GgafCore;

GgafProperties::GgafProperties() : GgafObject() {

}
GgafProperties::GgafProperties(std::string prm_properties_filename)  : GgafObject() {
    GgafProperties::read(prm_properties_filename);
}

//void GgafProperties::read(std::string prm_properties_filename) {
//    UTIL::readProperties(prm_properties_filename, _mapProperties);
//
//}
void GgafProperties::read(std::string filename) {
    std::ifstream file(filename.c_str());
    if (!file) {
        throwGgafCriticalException("ファイルが見つかりません。 filename="<<filename);
    }
    _TRACE_(FUNC_NAME<<" filename="<<filename);
    read(file);
    file.close();
}

void GgafProperties::read(std::istream& is) {
    if (!is)
        throwGgafCriticalException("unable to read from stream");

    int ch = 0;

    ch = is.get();

    while (!is.eof()) {
        switch (ch) {
            case '#':
            case '!':
                do {
                    ch = is.get();
                } while (!is.eof() && ch >= 0 && ch != '\n' && ch != '\r');
                continue;
            case '\n':
            case '\r':
            case ' ':
            case '\t':
                ch = is.get();
                continue;
        }

        std::ostringstream key, val;

        while (!is.eof() && ch >= 0 && ch != '=' && ch != ':' && ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {
            key << char(ch);
            ch = is.get();
        }

        while (!is.eof() && (ch == ' ' || ch == '\t'))
            ch = is.get();

        if (!is.eof() && (ch == '=' || ch == ':'))
            ch = is.get();

        while (!is.eof() && (ch == ' ' || ch == '\t'))
            ch = is.get();

        while (!is.eof() && ch >= 0 && ch != '\n' && ch != '\r') {
            int next = 0;
            next = is.get();
            val << char(ch);
            ch = next;
        }
        _TRACE_("\"" << key.str() << "\" => \"" << val.str() <<"\"");
        _mapProperties[key.str()] = val.str();
    }
}

void GgafProperties::write(std::string filename, const char *header) {
    std::ofstream file(filename.c_str());
    write(file, header);
    file.close();
}

void GgafProperties::write(std::ostream &os, const char *header) {
    if (header != nullptr) {
        os << '#' << header << std::endl;
    }
    os << '#' << "update " << GgafUtil::getSystemDateTimeStr() << std::endl;

    for (GgafStrMap::iterator it = _mapProperties.begin(), end = _mapProperties.end(); it != end; ++it) {
        const std::string &key = (*it).first, &val = (*it).second;
        os << key << '=' << val << std::endl;
    }
}

void GgafProperties::print(std::ostream &os) {
    GgafStrMap::iterator it = _mapProperties.begin(), end = _mapProperties.end();
    for (; it != end; ++it)
        os << (*it).first << "=" << (*it).second << std::endl;
}

//void GgafProperties::write(std::string prm_properties_filename) {
//    UTIL::writeProperties(prm_properties_filename.c_str(), _mapProperties);
//}

std::string GgafProperties::getStr(std::string prm_key) {
    if (isExistKey(prm_key)) {
        std::string* r = NEW std::string(_mapProperties[prm_key].c_str());
        std::string val = *r; //コピー
        GGAF_DELETE(r);
        return val;
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

float GgafProperties::getFloat(std::string prm_key) {
    if (isExistKey(prm_key)) {
        float ret = (float)atof(_mapProperties[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }

}
int GgafProperties::getInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        int ret = (int)(atoi(_mapProperties[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

uint32_t GgafProperties::getUInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        uint32_t ret = (uint32_t)(atof(_mapProperties[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool GgafProperties::getBool(std::string prm_key) {
    if (isExistKey(prm_key)) {
        return UTIL::cnvBool(_mapProperties[prm_key]);
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

double GgafProperties::getDouble(std::string prm_key) {
    if (isExistKey(prm_key)) {
        double ret = atof(_mapProperties[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

GgafRgb GgafProperties::getRGB(std::string prm_key) {
    if (isExistKey(prm_key)) {
        GgafRgb rgb = GgafRgb(prm_key);
        return rgb; //2回コピーだが仕方ない。
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void GgafProperties::setValue(std::string prm_key, int prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void GgafProperties::setValue(std::string prm_key, uint32_t prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void GgafProperties::setValue(std::string prm_key, std::string prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = prm_value;
    } else {
        throwGgafCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void GgafProperties::setValue(std::string prm_key, float prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void GgafProperties::setValue(std::string prm_key, double prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwGgafCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
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
        throwGgafCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void GgafProperties::setValue(std::string prm_key, GgafRgb prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = prm_value.toStr();
    } else {
        throwGgafCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool GgafProperties::isExistKey(std::string prm_key) {
    return _mapProperties.find(prm_key) != _mapProperties.end() ? true :false;
}

