#ifndef OPTIONMAGIC_H_
#define OPTIONMAGIC_H_
namespace MyStg2nd {

/**
 * 魔法「オプション」 .
 * @version 1.00
 * @since 2009/05/20
 * @author Masatoshi Tsuge
 */
class OptionMagic : public Magic {

public:
    GgafDx9Core::GgafDx9DrawableActor** _papEffect;
    float _r_effect;
    int _old_level;
    OptionMagic(const char* prm_name, magic_point* prm_pMP, MagicMeter* prm_pMagicMeter);

    virtual void processCastBegin() override;

    virtual void processCastingBehavior() override;

    virtual void processInvokeBegin() override;

    virtual void processInvokeingBehavior() override;

    virtual void processEffectBegin() override;

    virtual void processEffectingBehavior() override;

    virtual void processOnAbandon(int prm_last_level) override;


    virtual ~OptionMagic();
};

}
#endif /*OPTIONMAGIC_H_*/
