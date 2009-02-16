#include "framework\Frm_Tbuff.h"

TBuff* TBuff::_Instance = 0;

TBuff* TBuff::GetInstance(void) {
    if (TBuff::_Instance == 0)
        TBuff::_Instance = new TBuff;
    return TBuff::_Instance;
}

void TBuff::Set(const char* pText) {
    memcpy(_Info, pText, strlen(pText));
}

const char* TBuff::Get(void) {
    return _Info;
}

void TBuff::Reset(void) {
    memset(_Info, '\0', 512);
}

