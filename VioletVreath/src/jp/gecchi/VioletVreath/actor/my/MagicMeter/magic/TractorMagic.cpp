#include "TractorMagic.h"

#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TractorMagic::TractorMagic(const char* prm_name, int* prm_pMP)
        : Magic(prm_name, prm_pMP,
                2,                    //max_level
                1000*4  , 1.0, 0.9,   //��{���@�R�X�g, �{�P���x�����̃R�X�g������  , ��у��x�����̃R�X�g�팸��
                1       , 1.0, 0.9,   //��{�r������  , �{�P���x�����̉r�����ԑ�����, ��у��x�����̉r�����ԍ팸��
                1       , 1.0, 0.9,   //��{��������  , �{�P���x�����̔������ԑ�����, ��у��x�����̔������ԍ팸��
                120*10  , 1.5,        //��{��������  , �{�P���x�����̎������Ԃ̏旦
                1       , 1.1         //��{�ێ��R�X�g, �{�P���x�����̈ێ��R�X�g�̏旦
            ) {

    //���l�̈Ӗ��� VreathMagic.cpp �̃R�����g�Q��
    lvinfo_[7].pno_ =  6;
    lvinfo_[6].pno_ = 14;
    lvinfo_[5].pno_ = 22;
    lvinfo_[4].pno_ = 30;
    lvinfo_[3].pno_ = 38;
    lvinfo_[2].pno_ = 46;
    lvinfo_[1].pno_ = 54;
    lvinfo_[0].pno_ = 62;

    is_tracting_ = false;
}

void TractorMagic::onReset() {
    Magic::onReset();
    is_tracting_ = false;
}

void TractorMagic::processCastBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processCastingCancel(int prm_now_level) {
}
void TractorMagic::processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) {
}

void TractorMagic::processInvokeBegin(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokingBehavior(int prm_now_level, int prm_new_level) {
}
void TractorMagic::processInvokingCancel(int prm_now_level) {

}
void TractorMagic::processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) {
    P_MYSHIP->effectFlush(30); //�t���b�V��
}

void TractorMagic::processEffectBegin(int prm_last_level, int prm_now_level) {
    if ( prm_now_level == 0) {
        is_tracting_ = false;
    } else {
        is_tracting_ = true;
    }
}
void TractorMagic::processEffectingBehavior(int prm_last_level, int prm_now_level) {
}

TractorMagic::~TractorMagic() {
}
