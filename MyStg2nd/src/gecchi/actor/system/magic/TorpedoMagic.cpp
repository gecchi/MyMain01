#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TorpedoMagic::TorpedoMagic(const char* prm_name, MagicMeter* prm_pMagicMeter) : Magic(prm_name, prm_pMagicMeter,
                                                        2,          //max_level
                                                        4*1000,     //cost_base
                                                        5*60*60,  //time_of_casting_base
                                                        1*60*60   //time_of_invoking
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
    _lvinfo[1]._pno = 36;
    _lvinfo[2]._pno = 32;
}

TorpedoMagic::~TorpedoMagic() {
}
