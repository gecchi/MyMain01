#ifndef ASSEMBLYMAGIC_H_
#define ASSEMBLYMAGIC_H_
namespace MyStg2nd {

/**
 * 魔法「集合」 .
 * @version 1.00
 * @since 2011/02/15
 * @author Masatoshi Tsuge
 */
class AssemblyMagic : public Magic {

public:
    AssemblyMagic(const char* prm_name, MagicMeter* prm_pMagicMeter);

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

    virtual ~AssemblyMagic();
};

}
#endif /*ASSEMBLYMAGIC_H_*/
