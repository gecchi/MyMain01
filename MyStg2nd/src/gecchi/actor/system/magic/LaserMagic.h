#ifndef LASERMAGIC_H_
#define LASERMAGIC_H_
namespace MyStg2nd {

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

    virtual void processAbandoningBehavior() {
    }

    virtual ~LaserMagic();
};

}
#endif /*LASERMAGIC_H_*/
