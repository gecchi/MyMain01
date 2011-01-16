#ifndef TORPEDOMAGIC_H_
#define TORPEDOMAGIC_H_
namespace MyStg2nd {

class TorpedoMagic : public Magic {

public:
    TorpedoMagic(const char* prm_name);

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

    virtual ~TorpedoMagic();
};

}
#endif /*LASERMAGIC_H_*/
