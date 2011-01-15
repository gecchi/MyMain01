#ifndef OPTIONMAGIC_H_
#define OPTIONMAGIC_H_
namespace MyStg2nd {

class OptionMagic : public Magic {

public:
    OptionMagic(const char* prm_name);

    virtual void processCastBegin() override;

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

    virtual void processAbandonBegin() override;

    virtual void processAbandoningBehavior() override {
    }

    virtual ~OptionMagic();
};

}
#endif /*OPTIONMAGIC_H_*/
