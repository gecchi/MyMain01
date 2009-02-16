/////////////////////////////////////////////////////////
// Frm_Tbuff.h
//
//
/////////////////////////////////////////////////////////

#ifndef FRM_TBUFF_H
#define FRM_TBUFF_H
#include "GgafCommonHeader.h"
#include <mem.h>
#include <string.h>

class TBuff {
public:
    static TBuff* GetInstance(void);
    void Set(const char* pText);
    const char* Get(void);
    void Reset(void);
    char _TraceName[512];
private:
    static TBuff* _Instance;
    char _Info[512];
    TBuff(void) {
        Reset();
        memset(_TraceName, '\0', 512);
    }
};

#endif
