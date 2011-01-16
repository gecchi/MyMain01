#ifndef SPEEDMAGIC_H_
#define SPEEDMAGIC_H_
namespace MyStg2nd {

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

    virtual void processAbandoningBehavior() {
    }

    virtual ~SpeedMagic();
};

}
#endif /*LASERMAGIC_H_*/
