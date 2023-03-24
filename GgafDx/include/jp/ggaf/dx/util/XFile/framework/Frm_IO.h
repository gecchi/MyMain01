/////////////////////////////////////////////////////////
// FRM_IO.h
// provides a load/save base class to be derived
//
/////////////////////////////////////////////////////////

#ifndef FRM_IO_H
#define FRM_IO_H
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/XFile/framework/frm_types.h"
#include <string>
#include <string.h>
#include <vector>
#include <fstream>

namespace Frm {
template<class T>
class IO {
public:
    IO(void) :
        _Type(IO_NOTYPE) {
    }
    virtual bool Load(std::string pFilename, T pT)=0;
//    virtual bool Save(std::string pFilename, T &pT)=0;/**/
//    virtual bool Load(std::string pFilename, std::vector<T> &pVT)=0;
//    virtual bool Save(std::string pFilename, std::vector<T> &pVT)=0;/**/
    void LoadInBuffer(std::string pFilename) {
        int length;
        std::ifstream fin(pFilename.c_str());
        fin.seekg(0, std::ios::end);
        length = fin.tellg();
        fin.seekg(0, std::ios::beg);

        Buffer = NEW char[length];
        // read data as a block:
        fin.read(Buffer, length);

        fin.close();
    }

    uint8_t _Type;
protected:
    char* Buffer;
    float TextToNum(char* pText) {
        float test = 0, num = 10;
        bool sign;

        int textsize = strlen(pText);
        unsigned char i = 0;

        sign = false;
        while ((sign == false) && (i < textsize)) {
            switch (pText[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '-':
            case '.':
                sign = true;
                break;
            default:
                i++;
                break;
            }
        }

        if (i >= textsize)
            return 0.0f;

        if (pText[i] == '-') {
            sign = true;
            i++;
        } else
            sign = false;

        while ((pText[i] >= '0') && (pText[i] <= '9')) {
            test *= num;
            test += (pText[i++] - '0');
        }
        num = 0.1f;
        if ((i < textsize) && (pText[i++] == '.'))
            while ((pText[i] >= '0') && (pText[i] <= '9')) {
                test += (pText[i++] - '0') * num;
                num *= 0.1f;
            }
        if (sign)
            test = -test;
        return test;
    }
    void Remove(char pDelimiter, char* pText) {
        char result[255];
        uint32_t i, j = 0;
        for (i = 0; i < strlen(pText); i++)
            if (pText[i] != pDelimiter)
                result[j++] = pText[i];
        result[j++] = '\0';
        memcpy(pText, result, j);
    }

};

}
#endif
