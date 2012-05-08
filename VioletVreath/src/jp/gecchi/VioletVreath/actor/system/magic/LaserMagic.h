#ifndef LASERMAGIC_H_
#define LASERMAGIC_H_
namespace VioletVreath {

/**
 * 魔法「オプション」 .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class LaserMagic : public Magic {

public:
    LaserMagic(const char* prm_name, GgafLib::AmountGraph* prm_pMP);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processCastingBehavior(int prm_now_level, int prm_new_level)override {
    }

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) override {
    }

    virtual void processEffectBegin(int prm_last_level, int prm_now_level) override {
    }

    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) override {
    }

    virtual ~LaserMagic();
};

}
#endif /*LASERMAGIC_H_*/
