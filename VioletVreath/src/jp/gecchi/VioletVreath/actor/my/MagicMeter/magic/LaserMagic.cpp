#include "stdafx.h"
#include "LaserMagic.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

LaserMagic::LaserMagic(const char* prm_name, AmountGraph* prm_pMP)
    : Magic(prm_name, prm_pMP,
            2,          //max_level
            1000*4  , 0.9,   //��{���@�R�X�g , ��у��x������ rate
            60*3    , 0.9,   //��{�r������   , ��у��x������ rate
            60*2    , 0.9,   //��{��������   , ��у��x������ rate
            60*60*10, 1.0,   //��{��������   , �{�P���x�����̎������Ԃ̏旦
            0       , 1.0    //��{�ێ��R�X�g , �{�P���x�����̈ێ��R�X�g�̏旦
           ) {

    //���l�̈Ӗ��� VreathMagic.cpp �̃R�����g�Q��
    lvinfo_[7].pno_ =  68;
    lvinfo_[6].pno_ =  76;
    lvinfo_[5].pno_ =  84;
    lvinfo_[4].pno_ =  92;
    lvinfo_[3].pno_ = 100;
    lvinfo_[2].pno_ = 108;
    lvinfo_[1].pno_ = 116;
    lvinfo_[0].pno_ = 124;
}

LaserMagic::~LaserMagic() {
}
