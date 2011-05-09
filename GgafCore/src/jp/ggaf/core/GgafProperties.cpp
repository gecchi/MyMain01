#include "stdafx.h"
using namespace std;

using namespace GgafCore;

_MAP_<string, string>* GgafProperties::_pMapProperties = NULL;

UINT32 GgafProperties::MAX_SKIP_FRAME = 0;
int GgafProperties::DRAWNUM_TO_SLOWDOWN1 = 0;
int GgafProperties::DRAWNUM_TO_SLOWDOWN2 = 0;
float GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = 55.0f;
void GgafProperties::load(string prm_properties_filename) {
    if (_pMapProperties == NULL) {
        _pMapProperties = NEW _MAP_<string, string>();
        int ret = read(prm_properties_filename);
        if (ret != 0) {
            throwGgafCriticalException("GgafProperties::load() Error! "<<prm_properties_filename<<"のread()に失敗。ステート→"<<ret);
        }
    }

    GgafProperties::MAX_SKIP_FRAME = getUInt("MAX_SKIP_FRAME");
    GgafProperties::DRAWNUM_TO_SLOWDOWN1 = getInt("DRAWNUM_TO_SLOWDOWN1");
    GgafProperties::DRAWNUM_TO_SLOWDOWN2 = getInt("DRAWNUM_TO_SLOWDOWN2");
    GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = getFloat("FPS_TO_CLEAN_GARBAGE_BOX");
    _TRACE_("GgafProperties::MAX_SKIP_FRAME="<<GgafProperties::MAX_SKIP_FRAME);
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN1="<<GgafProperties::DRAWNUM_TO_SLOWDOWN1);
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN2="<<GgafProperties::DRAWNUM_TO_SLOWDOWN2);
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN2="<<GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX);
}

int GgafProperties::read(string prm_properties_filename) {
    const char* pChar_Filename = prm_properties_filename.c_str();
    FILE* pFile = NULL;
    int r = 0;
    try {
        if (!pChar_Filename) {
            _TRACE_("!pChar_Filename");
            throw -1;
        }
        //errno_t e = fopen_s(&pFile, pChar_Filename, "r"); //WIN32
        pFile = fopen(pChar_Filename, "r");
        if (!pFile) {
            _TRACE_("fopen(\""<<pChar_Filename<<"\", \"r\"); error:");
            perror("fopen error:");
            throw -2;
        }
        struct stat status;
        if (stat(pChar_Filename, &status)) {
            _TRACE_("stat(pChar_Filename, &status) error:");
            perror("stat error:");
            throw -3;
        }
        vector<char> vecBuffer(status.st_size + 1);
        fread(&vecBuffer[0], vecBuffer.size(), 1, pFile);
        vecBuffer[vecBuffer.size() - 1] = '\0';

        parse(&vecBuffer[0]);
    } catch (int e) {
        r = e;
    }

    if (pFile) {
        fclose(pFile);
    }
    return r;
}
void GgafProperties::parse(char* p) {
    char* pChar_Token = NULL;
    string key;
    string value;
    for (; *p != '\0'; p++) {
        if (*p == '#') {
            while (*p++ != '\n') {
            } //空読み
            p--;
            pChar_Token = NULL;
        } else if (*p == '\n' || *p == '\r') {
            *p = '\0';
        } else if (*p == '=') {
            *p = '\0';
            key = pChar_Token;
            pChar_Token = p + 1;
            while (*p != '\n' && *p != '\r' && *p != '#') {
                p++;
            }
            *p = '\0';
            value = pChar_Token;
            _pMapProperties->insert(_MAP_<string, string>::value_type(key, value));
            pChar_Token = NULL;
        } else {
            if (!pChar_Token) {
                pChar_Token = p;
            }
        }
    }
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
        bool ret;
        if (strcmp((*_pMapProperties)[prm_key].c_str(), "true") == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "on")   == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "yes")  == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "True") == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "On")   == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "Yes")  == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "TRUE") == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "ON")   == 0 ||
            strcmp((*_pMapProperties)[prm_key].c_str(), "YES")  == 0
        ) {
            ret = true;
        } else {
            ret = false;
        }
        return ret;
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

bool GgafProperties::isExistKey(string prm_key) {
    _MAP_<string, string>::iterator itr;
    itr = _pMapProperties->find(prm_key);
    if (itr != _pMapProperties->end()) {
        return true;
    } else {
        return false;
    }
}
