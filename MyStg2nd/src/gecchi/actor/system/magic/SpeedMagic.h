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

    virtual void processCastBegin() {
    }

    virtual void processCastingBehavior() {
    }

    virtual void processInvokeBegin() {
    }

    virtual void processInvokeingBehavior() {
    }

    virtual void processExpireBegin() {
    }

    virtual void processExpiringBehavior() {
    }

    virtual void processAbandonBegin() {
    }

    virtual void processOnAbandon(int prm_last_level) {
    }

    virtual ~SpeedMagic();
};

}
#endif /*LASERMAGIC_H_*/
