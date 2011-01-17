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

    virtual ~LaserMagic();
};

}
#endif /*LASERMAGIC_H_*/
