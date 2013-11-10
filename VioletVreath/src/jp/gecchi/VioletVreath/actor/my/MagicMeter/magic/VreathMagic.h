#ifndef VREATHMAGIC_H_
#define VREATHMAGIC_H_
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

namespace VioletVreath {

/**
 * ���@�uVreath�v .
 * @version 1.00
 * @since 2012/05/08
 * @author Masatoshi Tsuge
 */
class VreathMagic : public Magic {

    EffectVreathMagic001* pEffect_;

public:
    /** [r]���x�����P�ċz�̎��� */
    frame beat_time_[MMETER_MAX_LEVEL+1];
    /** [r]�e���x���ł̃t���[������vreath�ɉ��Z����l�Bbeat_time_[���x��]*2 �t���[�����ێ� */
    int* apaInt_vreath_per_frame_[MMETER_MAX_LEVEL+1];
    /** [r]�e���x���ł̃t���[�����ɉ��Z�����Vreath�旦 */
    double r_add_vreath_[MMETER_MAX_LEVEL+1];
    /** [r]�e���x���̍ŏI�I�ɑ�����Vreath�l(�����\���p�̂���) */
    int aInt_total_vreath_[MMETER_MAX_LEVEL+1];

public:
    VreathMagic(const char* prm_name, int* prm_pMP);

    void onReset() override;

    void processCastBegin(int prm_now_level, int prm_new_level) override;
    void processCastingBehavior(int prm_now_level, int prm_new_level) override;
    void processCastingCancel(int prm_now_level) override;
    void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) override;

    void processInvokeBegin(int prm_now_level, int prm_new_level) override;
    void processInvokingBehavior(int prm_now_level, int prm_new_level) override;
    void processInvokingCancel(int prm_now_level) override;
    void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) override;

    void processEffectBegin(int prm_last_level, int prm_now_level) override;
    void processEffectingBehavior(int prm_last_level, int prm_now_level) override;

    int calcTotalVreath(int prm_now_level, int prm_target_up_level);

    virtual ~VreathMagic();
};

}
#endif /*VREATHMAGIC_H_*/
