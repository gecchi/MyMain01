#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TractorMagic::TractorMagic(const char* prm_name)
        : Magic(prm_name,
            2,          //max_level
            1000*4  , 0.9,   //��{���@�R�X�g , ��у��x������ rate
            60*3    , 0.9,   //��{�r������   , ��у��x������ rate
            60*2    , 0.9,   //��{��������   , ��у��x������ rate
            60*60*10,    0.0,   //��{��������, �e���x���̍팸����
            1.0     , 0.0    //��{�ێ��R�X�g , �e���x������ rate
        ) {
    //    |  0,   1,   2,   3 |
    //    |  4,   5,   6,   7 |
    //    |  8,   9,  10,  11 |
    //    | 12,  13,  14,  15 |
    //    | 16,  17,  18,  19 |
    //    | 20,  21,  22,  23 |
    //    | 24,  25,  26,  27 |
    //    | 28,  29,  30,  31 |
    //    | 32,  33,  34,  35 |
    //    | 36,  37,  38,  39 |
    //    | 40,  41,  42,  43 |
    //    | 44,  45,  46,  47 |
    //    | 48,  49,  50,  51 |
    //    | 52,  53,  54,  55 |
    //    | 56,  57,  58,  59 |
    //    | 60,  61,  62,  63 |
    _lvinfo[0]._pno = 3;
    _lvinfo[1]._pno = 28;
    _lvinfo[2]._pno = 24;
}

TractorMagic::~TractorMagic() {
}
