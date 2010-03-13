#include "stdafx.h"
using namespace std;

using namespace GgafCore;

map<string, string>* GgafProperties::_pMapProperties = NULL;

DWORD* GgafProperties::MAX_SKIP_FRAME = NULL;

void GgafProperties::load(string prm_properties_filename) {
    if (_pMapProperties == NULL) {
        _pMapProperties = NEW map<string, string>();
        int ret = read(prm_properties_filename);
        if (ret != 0) {
            throwGgafCriticalException("GgafProperties::load() Error! "<<prm_properties_filename<<"のread()に失敗。ステート→"<<ret);
        }
    }

    MAX_SKIP_FRAME = getDWORD("MAX_SKIP_FRAME");

    _TRACE_("GGAF_PROPERTY(MAX_SKIP_FRAME)="<<GGAF_PROPERTY(MAX_SKIP_FRAME));
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
            _pMapProperties->insert(map<string, string>::value_type(key, value));
            pChar_Token = NULL;
        } else {
            if (!pChar_Token) {
                pChar_Token = p;
            }
        }
    }
}

void GgafProperties::clean() {
    DELETE_IMPOSSIBLE_NULL(MAX_SKIP_FRAME);
    DELETE_IMPOSSIBLE_NULL(_pMapProperties);
}

string* GgafProperties::getStr(string prm_key) {
    if (isExistKey(prm_key)) {
        string* ret = NEW string((*_pMapProperties)[prm_key].c_str());
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getStr() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}
float* GgafProperties::getFloat(string prm_key) {
    if (isExistKey(prm_key)) {
        float* ret = NEW float(atof((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }

}
int* GgafProperties::getInt(string prm_key) {
    if (isExistKey(prm_key)) {
        int* ret = NEW int(atoi((*_pMapProperties)[prm_key].c_str()));
        return ret;
    } else {
        throwGgafCriticalException("GgafProperties::getInt() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

DWORD* GgafProperties::getDWORD(string prm_key) {
    if (isExistKey(prm_key)) {
        DWORD* dwRet = NEW DWORD((DWORD)(atoi((*_pMapProperties)[prm_key].c_str())));
        return dwRet;
    } else {
        throwGgafCriticalException("GgafProperties::getDWORD() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool* GgafProperties::getBool(string prm_key) {
    if (isExistKey(prm_key)) {
        bool* bRet = NULL;
        if (strcmp((*_pMapProperties)[prm_key].c_str(), "true") == 0) {
            bRet = NEW bool(true);
        } else {
            bRet = NEW bool(false);
        }
        return bRet;
    } else {
        throwGgafCriticalException("GgafProperties::getBool() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

double* GgafProperties::getDouble(string prm_key) {
    if (isExistKey(prm_key)) {
        double* dRet = NEW double(atof((*_pMapProperties)[prm_key].c_str()));
        return dRet;
    } else {
        throwGgafCriticalException("GgafProperties::getDouble() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
    }
}

bool GgafProperties::isExistKey(string prm_key) {
    map<string, string>::iterator itr;
    itr = _pMapProperties->find(prm_key);
    if (itr != _pMapProperties->end()) {
        return true;
    } else {
        return false;
    }
}
