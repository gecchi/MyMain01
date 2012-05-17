#ifndef VREATHMAGIC_H_
#define VREATHMAGIC_H_
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
    /** [r]呼吸間隔 */
    frame beat_time_[MMETER_MAX_LEVEL+1];
    /** [r]フレーム毎にvreathに加算する値。beat_time_[レベル]*2 フレーム分保持 */
    int* apaInt_vreath_per_frame_[MMETER_MAX_LEVEL+1];

public:
    VreathMagic(const char* prm_name, GgafLib::AmountGraph* prm_pMP);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override;
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) override;
    virtual void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) override;

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override;
    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) override;
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) override;

    virtual int effect(int prm_level) override;

    virtual void processEffectBegin(int prm_last_level, int prm_now_level) override;
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) override;
    virtual void processEffectFinish(int prm_justbefore_level) override;

    int calcTotalVreath(int prm_now_level, int prm_target_up_level);

    virtual ~VreathMagic();
};

}
#endif /*VREATHMAGIC_H_*/
