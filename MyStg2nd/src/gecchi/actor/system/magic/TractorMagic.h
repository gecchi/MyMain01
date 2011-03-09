#ifndef TRACTORMAGIC_H_
#define TRACTORMAGIC_H_
namespace MyStg2nd {

/**
 * 魔法「アイテム引き寄せ」 .
 * @version 1.00
 * @since 2011/02/15
 * @author Masatoshi Tsuge
 */
class TractorMagic : public Magic {

public:
    TractorMagic(const char* prm_name, magic_point* prm_pMP, MagicMeter* prm_pMagicMeter);

    virtual void processCastBegin() override {
    }

    virtual void processCastingBehavior() override {
    }

    virtual void processInvokeBegin() override {
    }

    virtual void processInvokeingBehavior() override {
    }

    virtual void processEffectBegin() override {
    }

    virtual void processEffectingBehavior() override {
    }

    virtual void processOnAbandon(int prm_last_level) override {
    }

    virtual ~TractorMagic();
};

}
#endif /*TRACTORMAGIC_H_*/
