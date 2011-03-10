#ifndef TRACTORMAGIC_H_
#define TRACTORMAGIC_H_
namespace MyStg2nd {

/**
 * 魔法「アイテム引き寄せ」 .
 * @version 1.00
 * @since 2011/02/15
 * @author Masatoshi Tsuge
 */
class TractorMagic : public Magic {

public:
    TractorMagic(const char* prm_name);

    virtual void processCastBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processCastingBehavior(int prm_now_level, int prm_new_level)override {
    }

    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) override {
    }

    virtual void processInvokeingBehavior(int prm_now_level, int prm_new_level) override {
    }

    virtual void processEffectBegin(int prm_now_level) override {
    }

    virtual void processEffectingBehavior(int prm_now_level) override {
    }

    virtual void processOnLevelDown(int prm_last_high_level, int prm_new_low_level) override {
    }

    virtual ~TractorMagic();
};

}
#endif /*TRACTORMAGIC_H_*/
