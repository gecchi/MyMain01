#include "jp/ggaf/core/Properties.h"

#include <fstream>
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"
#include "Shlwapi.h"


using namespace GgafCore;

Properties::Properties() : Object() {

}
Properties::Properties(std::string prm_properties_filename)  : Object() {
    Properties::read(prm_properties_filename);
}

void Properties::read(std::string prm_properties_filename) {
    std::ifstream file(prm_properties_filename.c_str());
    if (!file) {
        throwCriticalException("ファイルが見つかりません。 prm_properties_filename="<<prm_properties_filename);
    }
    _TRACE_(FUNC_NAME<<" prm_properties_filename="<<prm_properties_filename);
    read(file);
    file.close();
}

void Properties::read(std::istream& is) {
    if (!is)
        throwCriticalException("unable to read from stream");

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

void Properties::write(std::string prm_properties_filename, const char *header) {
    std::ofstream ofs_properties(prm_properties_filename.c_str());
    write(ofs_properties, header);
    ofs_properties.close();
}

void Properties::write(std::ostream &os, const char *header) {
    if (header != nullptr) {
        os << '#' << header << std::endl;
    }
    os << '#' << "update " << Util::getSystemDateTimeStr() << std::endl;

    for (StrMap::iterator it = _mapProperties.begin(), end = _mapProperties.end(); it != end; ++it) {
        const std::string &key = (*it).first, &val = (*it).second;
        os << key << '=' << val << std::endl;
    }
}

void Properties::print(std::ostream &os) {
    StrMap::iterator it = _mapProperties.begin(), end = _mapProperties.end();
    for (; it != end; ++it)
        os << (*it).first << "=" << (*it).second << std::endl;
}

std::string Properties::getStr(std::string prm_key) {
    if (isExistKey(prm_key)) {
        std::string* r = NEW std::string(_mapProperties[prm_key].c_str());
        std::string val = *r; //コピー
        GGAF_DELETE(r);
        return val;
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

float Properties::getFloat(std::string prm_key) {
    if (isExistKey(prm_key)) {
        float ret = (float)atof(_mapProperties[prm_key].c_str());
        return ret;
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }

}
int Properties::getInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        int ret = (int)(atoi(_mapProperties[prm_key].c_str()));
        return ret;
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

uint32_t Properties::getUInt(std::string prm_key) {
    if (isExistKey(prm_key)) {
        uint32_t ret = (uint32_t)(strtoul(_mapProperties[prm_key].c_str(), 0, 0));
        return ret;
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool Properties::getBool(std::string prm_key) {
    if (isExistKey(prm_key)) {
        return UTIL::cnvBool(_mapProperties[prm_key]);
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

double Properties::getDouble(std::string prm_key) {
    if (isExistKey(prm_key)) {
        double ret = atof(_mapProperties[prm_key].c_str());
        return ret;
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

Rgb Properties::getRGB(std::string prm_key) {
    if (isExistKey(prm_key)) {
        Rgb rgb = Rgb(prm_key);
        return rgb; //2回コピーだが仕方ない。
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void Properties::setValue(std::string prm_key, int prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwCriticalException("Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void Properties::setValue(std::string prm_key, uint32_t prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void Properties::setValue(std::string prm_key, std::string prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = prm_value;
    } else {
        throwCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void Properties::setValue(std::string prm_key, float prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void Properties::setValue(std::string prm_key, double prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = XTOS(prm_value);
    } else {
        throwCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void Properties::setValue(std::string prm_key, bool prm_value) {
    if (isExistKey(prm_key)) {
        if (prm_value) {
            _mapProperties[prm_key] = "true";
        } else {
            _mapProperties[prm_key] = "false";
        }
    } else {
        throwCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

void Properties::setValue(std::string prm_key, Rgb prm_value) {
    if (isExistKey(prm_key)) {
        _mapProperties[prm_key] = prm_value.toStr();
    } else {
        throwCriticalException("プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool Properties::isExistKey(std::string prm_key) {
    return _mapProperties.find(prm_key) != _mapProperties.end() ? true :false;
}

