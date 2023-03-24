#ifndef VREATHMAGIC_H_
#define VREATHMAGIC_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

namespace VioletVreath {

/**
 * 魔法「Vreath」 .
 * @version 1.00
 * @since 2012/05/08
 * @author Masatoshi Tsuge
 */
class VreathMagic : public Magic {

    EffectVreathMagic001* pEffect_;

public:
    /** [r]レベル毎１呼吸の時間 */
    frame beat_time_[MMETER_MAX_LEVEL+1];
    /** [r]各レベルでのフレーム毎にvreathに加算する値。beat_time_[レベル]*2 フレーム分保持 */
    int* apaInt_vreath_per_frame_[MMETER_MAX_LEVEL+1];
    /** [r]各レベルでのフレーム毎に加算されるVreath乗率 */
    double r_add_vreath_[MMETER_MAX_LEVEL+1];
    /** [r]各レベルの最終的に増えるVreath値(増分表示用のため) */
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
