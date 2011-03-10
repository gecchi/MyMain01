#ifndef SPEEDMAGIC_H_
#define SPEEDMAGIC_H_
namespace MyStg2nd {

/**
 * 魔法「スピード」 .
 * @version 1.00
 * @since 2011/01/16
 * @author Masatoshi Tsuge
 */
class SpeedMagic : public Magic {

public:
    SpeedMagic(const char* prm_name);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processCastingBehavior(int prm_now_level, int prm_new_level)override {
    }

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processInvokeingBehavior(int prm_now_level, int prm_new_level) override {
    }

    virtual void processEffectBegin(int prm_now_level) override {
    }

    virtual void processEffectingBehavior(int prm_now_level) override {
    }

    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) override {
    }

    virtual ~SpeedMagic();
};

}
#endif /*LASERMAGIC_H_*/
