#include "jp/ggaf/core/Properties.h"

#include <fstream>
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/Util.h"
#include <Shlwapi.h>


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
    std::ifstream ifs_properties(prm_properties_filename.c_str());

    std::vector<std::string> lines;
    for (std::string line; std::getline(ifs_properties, line); ){
        lines.push_back(line);
    }
    ifs_properties.close();

    std::ofstream outs(prm_properties_filename.c_str());
    if (header != nullptr) {
        outs << '#' << header << std::endl;
    }
    outs << '#' << "update " << Util::getSystemDateTimeStr() << std::endl;
    StrMap mapProperties = _mapProperties;
    for (int i = 0; i < (int)lines.size(); i++) {
        std::string line = lines[i];
        std::istringstream ins(line);
        int ch = 0;

        ch = ins.get();

        switch (ch) {
            case '#':
            case '!':
                do {
                    ch = ins.get();
                } while (!ins.eof() && ch >= 0 && ch != '\n' && ch != '\r');
                //そのまま書く
                outs << line << std::endl;
                continue;
            case '\n':
            case '\r':
            case ' ':
            case '\t':
                ch = ins.get();
                //そのまま書く
                outs << line << std::endl;
                continue;
        }

        std::ostringstream key, val;

        while (!ins.eof() && ch >= 0 && ch != '=' && ch != ':' && ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {
            key << char(ch);
            ch = ins.get();
        }

        while (!ins.eof() && (ch == ' ' || ch == '\t'))
            ch = ins.get();

        if (!ins.eof() && (ch == '=' || ch == ':'))
            ch = ins.get();

        while (!ins.eof() && (ch == ' ' || ch == '\t'))
            ch = ins.get();

        while (!ins.eof() && ch >= 0 && ch != '\n' && ch != '\r') {
            int next = 0;
            next = ins.get();
            val << char(ch);
            ch = next;
        }
        // key.str()  が存在するか？
        bool is_break = false;
        for (StrMap::iterator it = mapProperties.begin(), end = mapProperties.end(); it != end; ++it) {
            const std::string &prop_key = (*it).first, &prop_val = (*it).second;
            if (prop_key == key.str()) {
                //存在したので上書き
                outs << prop_key << '=' << prop_val << std::endl;
                mapProperties.erase(it);
                is_break = true;
                break;
            }
        }
        if (is_break) {
            continue;
        } else {
            //存在しないのでそのまま書く
            outs << line << std::endl;
        }
    }

    //余りを最後に
    outs << "#remaining..." << std::endl;
    for (StrMap::iterator it = mapProperties.begin(), end = mapProperties.end(); it != end; ++it) {
        const std::string &prop_key = (*it).first, &prop_val = (*it).second;
        outs << prop_key << '=' << prop_val << std::endl;
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

