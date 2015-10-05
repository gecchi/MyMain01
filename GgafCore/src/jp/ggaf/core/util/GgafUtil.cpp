#include "jp/ggaf/core/util/GgafUtil.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include <fstream>
#include <time.h>
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

using namespace GgafCore;

uint32_t GgafUtil::_timex = 0;

uint32_t GgafUtil::getSystemTime() {

    return timeGetTime();
    //return _timex++;
}

char* GgafUtil::getFileText(std::string prm_filename) {
    std::ifstream ifs(prm_filename.c_str());
    if (!ifs.is_open()) {
        return nullptr;
    } else {
        uint32_t size = 0;
        // サイズを取得
        while (!ifs.eof()) {
            ifs.ignore();
            ++size;
        }
        ifs.clear();
        ifs.seekg(0, std::ios_base::beg);
        //サイズを指定して読込み
        char* pa_char = NEW char[size];
        ZeroMemory(pa_char, size);
        ifs.read(pa_char, size-1);
        return pa_char;
    }
}

int32_t GgafUtil::_rnd_int32_(int32_t prm_from, int32_t prm_to) {
#ifdef MY_DEBUG
    if (prm_from > prm_to) {
        MessageBox(nullptr, "GgafUtil::_rnd_int32_() from toの大小がおかしい", "不本意な事態", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND|MB_TOPMOST);
    }
#endif
    return ((int32_t)(GgafCore::CmRandomNumberGenerator::getInstance()->genrand_real2() * (prm_to - prm_from + 1) ) + prm_from );
    //↑[N3551 Random Number Generation in C++11] を読んで焦って修正、今まで剰余使ってたし！ 2013/03/22
}

void GgafUtil::readProperties(std::string filename, GgafStrMap& mapStr) {
    std::ifstream file(filename.c_str());
    if (!file) {
        throwGgafCriticalException("GgafUtil::readProperties() ファイルが見つかりません。 filename="<<filename);
    }
    _TRACE_("GgafUtil::readProperties..."<<filename);
    GgafUtil::readProperties(file, mapStr);
    file.close();
}

void GgafUtil::readProperties(std::istream& is, GgafStrMap& mapStr) {
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
        mapStr[key.str()] = val.str();
    }
}

void GgafUtil::writeProperties(const char *filename, GgafStrMap& mapStr, const char *header) {
    std::ofstream file(filename);
    GgafUtil::writeProperties(file, mapStr, header);
    file.close();
}

void GgafUtil::writeProperties(std::ostream &os, GgafStrMap& mapStr, const char *header) {
    if (header != nullptr) {
        os << '#' << header << std::endl;
    }
    os << '#' << "update " << GgafUtil::getSystemDateTimeStr() << std::endl;

    for (GgafStrMap::iterator it = mapStr.begin(), end = mapStr.end(); it != end; ++it) {
        const std::string &key = (*it).first, &val = (*it).second;
        os << key << '=' << val << std::endl;
    }
}

void GgafUtil::printProperties(std::ostream &os, GgafStrMap& mapStr) {
    GgafStrMap::iterator it = mapStr.begin(), end = mapStr.end();
    for (; it != end; ++it)
        os << (*it).first << "=" << (*it).second << std::endl;
}


bool GgafUtil::isExistKey(std::string prm_key, GgafStrMap& mapStr) {
    GgafStrMap::iterator itr = mapStr.find(prm_key);
    if (itr != mapStr.end()) {
        return true;
    } else {
        return false;
    }
}

bool GgafUtil::cnvBool(std::string prm_str) {
    bool ret;
    if (strcmp(prm_str.c_str(), "false") == 0 ||
        strcmp(prm_str.c_str(), "off")   == 0 ||
        strcmp(prm_str.c_str(), "no")    == 0 ||
        strcmp(prm_str.c_str(), "False") == 0 ||
        strcmp(prm_str.c_str(), "Off")   == 0 ||
        strcmp(prm_str.c_str(), "No")    == 0 ||
        strcmp(prm_str.c_str(), "FALSE") == 0 ||
        strcmp(prm_str.c_str(), "OFF")   == 0 ||
        strcmp(prm_str.c_str(), "NO")    == 0 ||
        strcmp(prm_str.c_str(), "0")     == 0
    ) {
        ret = false;
    } else {
        ret = true;
    }
    return ret;
}

std::string GgafUtil::getFileBaseNameWithoutExt(const char* prm_filepath) {
    std::string basename = GgafUtil::getFileBaseName(prm_filepath);
    int p = (int)basename.find_first_of('.');
    if (p == 0) {
        //ドット始まりのファイル名
        return "";
    } else if (p < 0) {
        //ピリオドなしのファイル名
        return basename;
    } else {
        return basename.substr(0, p);
    }
}


std::string GgafUtil::getFileBaseName(const char* prm_filepath) {
    int p = (int)strlen(prm_filepath) - 1;
    if (p < 0) {
        return "";
    }
    if (prm_filepath[p] == '/' || prm_filepath[p] == '\\') {
        p--;
    }
    std::string res;
    while (!(prm_filepath[p] == '/' || prm_filepath[p] == '\\')) {
        res += prm_filepath[p--];
    }
    GgafUtil::reverseStr((char*)res.c_str());
    return res;
}

std::string GgafUtil::getFileDirName(const char* prm_filepath) {
    int p = (int)strlen(prm_filepath) - 1;
    if (p < 0) {
        return "";
    }
    if (prm_filepath[p] == '/' || prm_filepath[p] == '\\') {
        p--;
    }
    std::string res;
    while (!(prm_filepath[p] == '/' || prm_filepath[p] == '\\')) {
        p--;
    }
    res.assign(prm_filepath, p);
    return res;
}

std::string GgafUtil::getFileExt(const char* prm_filepath) {
    std::string basename = GgafUtil::getFileBaseName(prm_filepath);
    int epos = (int)basename.find_last_of('.');
    if (epos < 0) {
        return "";
    }
    return basename.substr(epos + 1, basename.length() - epos);
}

char* GgafUtil::reverseStr(char* str) {
    std::string tmp = str;
    char* p = (char*)tmp.c_str();
    for (int i = (int)strlen(str) - 1, j = 0; i >= 0; i--, j++)
        str[i] = p[j];
    return (&str[0]);
}
void GgafUtil::strReplace(std::string& str, const std::string& from, const std::string& to) {
    std::string::size_type pos = 0;
    while (pos = str.find(from, pos), pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}

std::string GgafUtil::padZeroStr(int prm_data_num, int prm_total_keta) {
    std::ostringstream oss;
    oss.setf(std::ios::right);
    oss.fill('0');
    oss.width(prm_total_keta);
    oss << prm_data_num;
    return oss.str();
}

std::string GgafUtil::getSystemDateTimeStr() {
    struct tm *date;
    time_t now;
    time(&now);
    date = localtime(&now);
    char buf[20];
    sprintf(buf, "%04d/%02d/%02d %02d:%02d:%02d",
            date->tm_year + 1900, date->tm_mon + 1, date->tm_mday,
            date->tm_hour, date->tm_min, date->tm_sec);
    std::string str(buf);
    return str;
}

