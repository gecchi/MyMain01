#ifndef OPTIONMAGIC_H_
#define OPTIONMAGIC_H_
namespace VioletVreath {

/**
 * 魔法「オプション」 .
 * @version 1.00
 * @since 2009/05/20
 * @author Masatoshi Tsuge
 */
class OptionMagic : public Magic {

public:
    GgafDxCore::GgafDxDrawableActor** _papEffect;
    float _r_effect;
    int _old_level;
    OptionMagic(const char* prm_name, GgafLib::AmountGraph* prm_pMP);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override;
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level)override;
    virtual void processCastFinish(int prm_now_level, int prm_new_level) override;

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override;
    virtual void processInvokeingBehavior(int prm_now_level, int prm_new_level) override;
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level) override;

    virtual int effect(int prm_level) override;

    virtual void processEffectBegin(int prm_last_level, int prm_now_level) override;
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) override;
    virtual void processEffectFinish(int prm_justbefore_level) override;
//    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) override;


    virtual ~OptionMagic();
};

}
#endif /*OPTIONMAGIC_H_*/
