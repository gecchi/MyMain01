#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafProperties::PropertyMapT* GgafProperties::_pMapProperties = NULL;

UINT32 GgafProperties::MAX_SKIP_FRAME = 0;
int GgafProperties::DRAWNUM_TO_SLOWDOWN1 = 0;
int GgafProperties::DRAWNUM_TO_SLOWDOWN2 = 0;
float GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX = 55.0f;
void GgafProperties::load(string prm_properties_filename) {
    if (_pMapProperties == NULL) {
        _pMapProperties = NEW PropertyMapT();
        read(prm_properties_filename, _pMapProperties);
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
    _TRACE_("GgafProperties::DRAWNUM_TO_SLOWDOWN2="<<GgafProperties::FPS_TO_CLEAN_GARBAGE_BOX);
}
void GgafProperties::read(string filename, PropertyMapT* pMap)
{
    std::ifstream file(filename.c_str());
    if (!file)
        throwGgafCriticalException("unable to open properties file");
    read(file, pMap);
    file.close();
}

void GgafProperties::read(std::istream &is, PropertyMapT* pMap)
{
    if (!is)
        throwGgafCriticalException("unable to read from stream");

    int ch = 0, next = 0;

    ch = is.get();

    while (!is.eof())
    {
        switch (ch)
        {
        case '#' :
        case '!' :
			do  {
				ch = is.get();
			} while (!is.eof() && ch >= 0 && ch != '\n' && ch != '\r');
            continue;
        case '\n':
        case '\r':
        case ' ' :
        case '\t': ch = is.get(); continue;
        }

        // Read the key
        std::ostringstream key, val;

        while (!is.eof() && ch >= 0 && ch != '=' && ch != ':' &&
               ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
        {
            key << char(ch);
            ch = is.get();
        }

        while (!is.eof() && (ch == ' ' || ch == '\t'))
            ch = is.get();

        if (!is.eof() && (ch == '=' || ch == ':'))
            ch = is.get();

        while (!is.eof() && (ch == ' ' || ch == '\t'))
            ch = is.get();

        // Read the value
        while (!is.eof() && ch >= 0 && ch != '\n' && ch != '\r')
        {
            int next = 0;
//            if (ch == '\\')
//            {
//                ch = is.get();
//                switch (ch)
//                {
//                case '\r':
//                    ch = is.get();
//                    if (ch != '\n' && ch != ' ' && ch != '\t')
//                        continue;
//                    // fall through
//                case '\n':
//                    ch = is.get();
//                    while (!is.eof() && (ch == ' ' || ch == '\t')) { is >> ch; }
//                    continue;
//                case 't': ch = '\t'; next = is.get(); break;
//                case 'n': ch = '\n'; next = is.get(); break;
//                case 'r': ch = '\r'; next = is.get(); break;
//                case 'u':
//                    {
//                        ch = is.get();
//                        while (!is.eof() && ch == 'u') { is >> ch; }
//                        int d = 0;
//                    loop:
//                        for (int i = 0 ; !is.eof() && i < 4 ; i++)
//                        {
//                            next = is.get();
//                            switch (ch)
//                            {
//                            case '0': case '1': case '2': case '3': case '4':
//                            case '5': case '6': case '7': case '8': case '9':           d = (d << 4) +      ch - '0'; break;
//                            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': d = (d << 4) + 10 + ch - 'a'; break;
//                            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': d = (d << 4) + 10 + ch - 'A'; break;
//                            default:                                                                                  goto loop;
//                            }
//                            ch = is.get();
//                        }
//                        ch = d;
//                        break;
//                    }
//                default:
//                    //next = is.get();
//                    break;
//                }
//            }
//            else
                next = is.get();

            val << char(ch);
            ch = next;
        }
        //if (DEBUG)
            _TRACE_("key:" << key.str() << "|value:" << val.str());
        (*pMap)[key.str()] = val.str();
    }
}

void GgafProperties::write(const char *filename, PropertyMapT* pMap, const char *header)
{
    std::ofstream file(filename);
    write(file, pMap, header);
    file.close();
}

void GgafProperties::write(std::ostream &os, PropertyMapT* pMap, const char *header)
{
    if (header != NULL)
        os << '#' << header << std::endl;

    os << '#';
    os << " <date> " << std::endl;

    for (iterator it = pMap->begin(), end = pMap->end(); it != end; ++it)
    {
        const std::string &key = (*it).first,
                          &val = (*it).second;
        os << key << '=';

        bool empty = false;

        for (size_t i = 0, sz = val.size(); i < sz; i++)
        {
            char ch = val[i];

            switch (ch)
            {
            case '\\': os << '\\' << '\\'; break;
            case '\t': os << '\\' << 't';  break;
            case '\n': os << '\\' << 'n';  break;
            case '\r': os << '\\' << 'r';  break;
            default:
                if (ch < ' ' || ch >= 127 || (empty && ch == ' '))
                    os << '\\' << 'u'
                       << m_hex((ch >> 12) & 0x0f) << m_hex((ch >> 8) & 0x0f)
                       << m_hex((ch >>  4) & 0x0f) << m_hex((ch >> 0) & 0x0f);
                else
                    os << ch;
            }

            empty = false;
        }
        os << std::endl;
    }
}

void GgafProperties::print(std::ostream &os, PropertyMapT* pMap)
{
    iterator it = pMap->begin(), end = pMap->end();
    for (; it != end; ++it)
        os << (*it).first << "=" << (*it).second << std::endl;
}
//int GgafProperties::read(string prm_properties_filename) {
//    const char* pChar_Filename = prm_properties_filename.c_str();
//    FILE* pFile = NULL;
//    int r = 0;
//    try {
//        if (!pChar_Filename) {
//            _TRACE_("!pChar_Filename");
//            throw -1;
//        }
//        //errno_t e = fopen_s(&pFile, pChar_Filename, "r"); //WIN32
//        pFile = fopen(pChar_Filename, "r");
//        if (!pFile) {
//            _TRACE_("fopen(\""<<pChar_Filename<<"\", \"r\"); error:");
//            perror("fopen error:");
//            throw -2;
//        }
//        struct stat status;
//        if (stat(pChar_Filename, &status)) {
//            _TRACE_("stat(pChar_Filename, &status) error:");
//            perror("stat error:");
//            throw -3;
//        }
//        _TRACE_("status.st_size="<<status.st_size);
//
//        vector<char> vecBuffer(status.st_size + 1);
//        fread(&vecBuffer[0], vecBuffer.size(), 1, pFile);
//		for (int z = 1; z < 100; z++) {
//			vecBuffer[vecBuffer.size() - z] = '*';
//		}
//        vecBuffer[vecBuffer.size() - 1] = '\0';
//        _TRACE_("vecBuffer.size()="<<vecBuffer.size());
//        parse(&vecBuffer[0]);
//    } catch (int e) {
//        r = e;
//    }
//
//    if (pFile) {
//        fclose(pFile);
//    }
//    return r;
//}
//void GgafProperties::parse(char* p) {
//    char* pChar_Token = NULL;
//    string key;
//    string value;
//    bool _in_token = false;
//    for (; *p != '\0'; p++) {
//		_TRACE_("key p="<<(p[0]==0?'-':p[0])<<"/pChar_Token="<<(pChar_Token==0?"":pChar_Token)<<"/key="<<key<<"/value="<<value);
//        if (*p == '#') {
//            while (*p++ != '\n') {
//            } //空読み
//            p--;
//            pChar_Token = NULL;
//        } else if (*p == ' ' || *p == '\t') {
//            *p = '\0';
//        } else if (*p == '\n' || *p == '\r') {
//            *p = '\0';
//        } else if (*p == '=') {
//            *p = '\0';
//            key = pChar_Token;
//            pChar_Token = p + 1;
//
//            while (*p != '\n' && *p != '\r' && *p != '#') {
//                if (*p == ' ' || *p == '\t') {
//                    *p = '\0';
//                }
//                p++;
//            }
//            *p = '\0';
//            value = pChar_Token;
//            _pMapProperties->insert(_MAP_<string, string>::value_type(key, value));
//            pChar_Token = NULL;
//        } else {
//            if (!pChar_Token) {
//                pChar_Token = p;
//            }
//        }
//    }
//}

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

GgafRgb GgafProperties::getRGB(std::string prm_key) {
    if (isExistKey(prm_key)) {
        GgafRgb rgb = GgafRgb(prm_key);
        return rgb;
    } else {
        throwGgafCriticalException("GgafProperties::getRGB() Error! プロパティに、キー("<<prm_key<<")が存在しません。");
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
