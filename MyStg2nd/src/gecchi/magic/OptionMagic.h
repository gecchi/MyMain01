#ifndef OPTIONMAGIC_H_
#define OPTIONMAGIC_H_
namespace MyStg2nd {

class OptionMagic : public DefaultMagic {

public:
    OptionMagic(const char* prm_name,
          GgafDx9Core::GgafDx9UntransformedActor* prm_pCaster,
          GgafDx9Core::GgafDx9UntransformedActor* prm_pReceiver);

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

    virtual ~OptionMagic();
};

}
#endif /*OPTIONMAGIC_H_*/
