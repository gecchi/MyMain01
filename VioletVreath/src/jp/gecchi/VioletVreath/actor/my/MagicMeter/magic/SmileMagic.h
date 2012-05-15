#ifndef SMILEMAGIC_H_
#define SMILEMAGIC_H_
namespace VioletVreath {

/**
 * ñÇñ@ÅuSmileÅv .
 * @version 1.00
 * @since 2012/05/15
 * @author Masatoshi Tsuge
 */
class SmileMagic : public Magic {

    EffectSmileMagic001* pEffect_;

public:
    SmileMagic(const char* prm_name, GgafLib::AmountGraph* prm_pMP);

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

    virtual ~SmileMagic();
};

}
#endif /*SMILEMAGIC_H_*/
