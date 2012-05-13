#ifndef LOCKONMAGIC_H_
#define LOCKONMAGIC_H_
namespace VioletVreath {

/**
 * 魔法「ロックオン」 .
 * @version 1.00
 * @since 2011/01/16
 * @author Masatoshi Tsuge
 */
class LockonMagic : public Magic {

public:
    LockonMagic(const char* prm_name, GgafLib::AmountGraph* prm_pMP);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processCastingBehavior(int prm_now_level, int prm_new_level)override {
    }

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) override {
    }

    virtual void processEffectBegin(int prm_last_level, int prm_now_level) override {
    }

    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) override {
    }

    virtual ~LockonMagic();
};

}
#endif /*LASERMAGIC_H_*/
