#include "jp/ggaf/core/util/Util.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include <fstream>
#include <time.h>
#include <math.h>
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

using namespace GgafCore;

uint32_t Util::_timex = 0;

uint32_t Util::getSystemTime() {

    return timeGetTime();
    //return _timex++;
}

char* Util::getFileText(std::string prm_filename) {
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
int g_count=0;

int32_t Util::_rnd_int32_(int32_t prm_from, int32_t prm_to) {
#ifdef MY_DEBUG
    if (prm_from > prm_to) {
        MessageBox(nullptr, "Util::_rnd_int32_() from toの大小がおかしい", "不本意な事態", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND|MB_TOPMOST);
    }
#endif
    return ((int32_t)(CmRandomNumberGenerator::getInstance()->genrand_real2() * (prm_to - prm_from + 1) ) + prm_from );
    //↑[N3551 Random Number Generation in C++11] を読んで焦って修正、今まで剰余使ってたし！ 2013/03/22
}
double Util::_rnd_double_(double prm_from, double prm_to) {
#ifdef MY_DEBUG
    if (prm_from > prm_to) {
        MessageBox(nullptr, "Util::_rnd_double_() from toの大小がおかしい", "不本意な事態", MB_OK|MB_ICONQUESTION|MB_SETFOREGROUND|MB_TOPMOST);
    }
#endif
    return (CmRandomNumberGenerator::getInstance()->genrand_real1() * (prm_to - prm_from) ) + prm_from ;
}

double Util::_cbrt_(double x) {
    double stv, dx, last, diff, v3;
    stv = x >= 0.0 ? sqrt(x) : -sqrt(-x);
    dx = stv * 0.1;
    if (x == 0.0) return 0.0; // i knnow comparing float
    if (x < stv * stv * stv) dx = -dx;
    while (1) {
        last = stv;

        while (1) {
            v3 = stv * stv * stv;
            if (dx > 0 && x < v3) break;
            if (dx < 0 && x > v3) break;
            // 立方根と近似値の大小関係が変化したら内側の無限ループから抜ける
            stv += dx;
        }
        diff = stv - last;
        if ((diff > -0.0000001) && (diff < 0.0000001)) break;
        dx = -dx * 0.1;
    }
    return (stv);
}

bool Util::cnvBool(std::string& prm_str) {
    const char* s = prm_str.c_str();
    bool ret;
    if (strcmp(s, "false") == 0 ||
        strcmp(s, "off")   == 0 ||
        strcmp(s, "no")    == 0 ||
        strcmp(s, "False") == 0 ||
        strcmp(s, "Off")   == 0 ||
        strcmp(s, "No")    == 0 ||
        strcmp(s, "FALSE") == 0 ||
        strcmp(s, "OFF")   == 0 ||
        strcmp(s, "NO")    == 0 ||
        strcmp(s, "0")     == 0
    ) {
        ret = false;
    } else if (
        strcmp(s, "true") == 0 ||
        strcmp(s, "on")   == 0 ||
        strcmp(s, "yes")  == 0 ||
        strcmp(s, "True") == 0 ||
        strcmp(s, "On")   == 0 ||
        strcmp(s, "Yes")  == 0 ||
        strcmp(s, "TRUE") == 0 ||
        strcmp(s, "ON")   == 0 ||
        strcmp(s, "YES")  == 0 ||
        strcmp(s, "1")    == 0
    ) {
        ret = true;
    } else {
        throwCriticalException("Util::cnvBool() prm_str="<<prm_str<<" は bool に変換できません" );
    }
    return ret;
}

std::string Util::getFileBaseNameWithoutExt(const char* prm_filepath) {
    std::string basename = Util::getFileBaseName(prm_filepath);
    int p = (int)basename.find_first_of('.');
    if (p == 0) {
        //ドット始まりのファイル名
        return "";
    } else if (p < 0) {
        //ピリオドなしのファイル名
        return basename;
    } else {
        std::string res = std::string(basename.substr(0, p));
        return res;
    }
}


std::string Util::getFileBaseName(const char* prm_filepath) {
    int p = (int)strlen(prm_filepath) - 1;
    if (p < 0) {
        return "";
    }
    if (prm_filepath[p] == '/' || prm_filepath[p] == '\\') {
        p--;
    }
    std::string res;
    while (! (p < 0 || prm_filepath[p] == '/' || prm_filepath[p] == '\\')) {
        res += prm_filepath[p--];
    }
    char* cstr = NEW char[res.size() + 1];
    strcpy(cstr, res.c_str());
    Util::reverseStr(cstr);
    res = std::string(cstr);
    GGAF_DELETEARR(cstr);
    return res;
}

std::string Util::getFileDirName(const char* prm_filepath) {
    int p = (int)strlen(prm_filepath) - 1;
    if (p < 0) {
        return "";
    }
    if (prm_filepath[p] == '/' || prm_filepath[p] == '\\') {
        p--;
    }
    std::string res;
    while (!(p < 0 || prm_filepath[p] == '/' || prm_filepath[p] == '\\')) {
        p--;
    }
    res.assign(prm_filepath, p);
    return res;
}

std::string Util::getFileExt(const char* prm_filepath) {
    std::string basename = Util::getFileBaseName(prm_filepath);
    int epos = (int)basename.find_last_of('.');
    if (epos < 0) {
        return "";
    }
    std::string res = basename.substr(epos + 1);
    return res;
//    return basename.substr(epos + 1, basename.length() - epos);
}

void Util::reverseStr(char* str) {
    std::string tmp = str;
    char* p = (char*)tmp.c_str();
    for (int i = (int)strlen(str) - 1, j = 0; i >= 0; i--, j++) {
        str[i] = p[j];
    }
}

void Util::strReplace(std::string& str, const std::string& from, const std::string& to) {
    std::string::size_type pos = 0;
    while ( (pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}

std::string Util::padZeroStr(int prm_data_num, int prm_total_keta) {
    std::ostringstream oss;
    oss.setf(std::ios::right);
    oss.fill('0');
    oss.width(prm_total_keta);
    oss << prm_data_num;
    return oss.str();
}

std::string Util::getSystemDateTimeStr() {
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

