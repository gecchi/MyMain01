#include "stdafx.h"
using namespace std;

using namespace GgafCore;

UINT32 GgafUtil::_timex = 0;

UINT32 GgafUtil::getSystemTime() {

    return timeGetTime();
    //return _timex++;
}

char* GgafUtil::getFileText(string prm_filename) {
    ifstream ifs(prm_filename.c_str());
    if (!ifs.is_open()) {
        return NULL;
    } else {
        UINT32 size = 0;
        // サイズを取得
        while (!ifs.eof()) {
            ifs.ignore();
            ++size;
        }
        ifs.clear();
        ifs.seekg(0, ios_base::beg);
        //サイズを指定して読込み
        char* pa_char = NEW char[size];
        ZeroMemory(pa_char, size);
        ifs.read(pa_char, size-1);
        return pa_char;
    }
}

