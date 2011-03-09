#ifndef TORPEDOMAGIC_H_
#define TORPEDOMAGIC_H_
namespace MyStg2nd {

/**
 * ñÇñ@ÅuãõóãÅv .
 * @version 1.00
 * @since 2011/01/16
 * @author Masatoshi Tsuge
 */
class TorpedoMagic : public Magic {

public:
    TorpedoMagic(const char* prm_name, magic_point* prm_pMP, MagicMeter* prm_pMagicMeter);

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

    virtual ~TorpedoMagic();
};

}
#endif /*LASERMAGIC_H_*/
