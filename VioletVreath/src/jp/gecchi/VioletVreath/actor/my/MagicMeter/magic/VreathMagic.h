#ifndef VREATHMAGIC_H_
#define VREATHMAGIC_H_
namespace VioletVreath {

/**
 * ñÇñ@ÅuVreathÅv .
 * @version 1.00
 * @since 2012/05/08
 * @author Masatoshi Tsuge
 */
class VreathMagic : public Magic {

    EffectVreathMagic001* pEffect_;

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

    virtual ~VreathMagic();
};

}
#endif /*VREATHMAGIC_H_*/
