#ifndef DEFAULTMAGIC_H_
#define DEFAULTMAGIC_H_
namespace MyStg2nd {

class DefaultMagic : public Magic {

public:
    DefaultMagic(const char* prm_name,
          GgafDx9Core::GgafDx9GeometricActor* prm_pCaster,
          GgafDx9Core::GgafDx9GeometricActor* prm_pReceiver);

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

    virtual ~DefaultMagic();
};

}
#endif /*DEFAULTMAGIC_H_*/
