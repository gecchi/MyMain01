#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

OptionMagic::OptionMagic(const char* prm_name) : Magic(prm_name,
                                                          8,          //max_level
                                                          4*1000,     //cost_base
                                                          5*60*60,    //time_of_casting_base
                                                          1*60*60     //time_of_invoking
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
    _lvinfo[1]._pno = 61;
    _lvinfo[2]._pno = 57;
    _lvinfo[3]._pno = 53;
    _lvinfo[4]._pno = 49;
    _lvinfo[5]._pno = 45;
    _lvinfo[6]._pno = 49;
    _lvinfo[7]._pno = 45;
    _lvinfo[8]._pno = 41;

    _lvinfo[0]._time_of_abandon = 300*60*60;
    _lvinfo[1]._time_of_abandon = 300*60*60;
    _lvinfo[2]._time_of_abandon = 300*60*60;
    _lvinfo[3]._time_of_abandon = 300*60*60;
    _lvinfo[4]._time_of_abandon = 300*60*60;
    _lvinfo[5]._time_of_abandon = 300*60*60;
    _lvinfo[6]._time_of_abandon = 300*60*60;
    _lvinfo[7]._time_of_abandon = 300*60*60;
    _lvinfo[8]._time_of_abandon = 300*60*60;

}
void OptionMagic::processCastBegin() {
    _cast_speed = 60;
    if (_new_level > _level) {
        _cost = _cost_base * (_new_level - _level) * 0.8 ; //‚QŠ„ˆø
    } else {
        _cost = -1.0f * _cost_base * (_level - _new_level) * 0.5;
    }


    P_MYOPTIONCON->setNumOption(_new_level);
    commit();
}

void OptionMagic::processCastingBehavior() {

}

void OptionMagic::processOnAbandon(int prm_last_level) {
    P_MYOPTIONCON->setNumOption(_new_level);
    commit();
}

OptionMagic::~OptionMagic() {
}
