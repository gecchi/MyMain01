#ifndef LASERMAGIC_H_
#define LASERMAGIC_H_
namespace MyStg2nd {

/**
 * 魔法「オプション」 .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class LaserMagic : public Magic {

public:
    LaserMagic(const char* prm_name);

    virtual void processCastBegin() override {
    }

    virtual void processCastingBehavior() override {
    }

    virtual void processInvokeBegin() override {
    }

    virtual void processInvokeingBehavior() override {
    }

    virtual void processExpireBegin() override {
    }

    virtual void processExpiringBehavior() override {
    }

    virtual void processOnAbandon(int prm_last_level) override {
    }

    virtual ~LaserMagic();
};

}
#endif /*LASERMAGIC_H_*/
