#ifndef LOCKONMAGIC_H_
#define LOCKONMAGIC_H_
namespace MyStg2nd {

class LockonMagic : public Magic {

public:
    LockonMagic(const char* prm_name);

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

    virtual ~LockonMagic();
};

}
#endif /*LASERMAGIC_H_*/
