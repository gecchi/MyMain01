#ifndef VREATHITEM_H_
#define VREATHITEM_H_

namespace VioletVreath {

/**
 * Vreath๑ACeฌ .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class VreathItem : public Item {
    /** zทชภW */
    int kDX_, kDY_, kDZ_;

public:
    enum {
        PROG_DRIFT      , //สํฺฎ๓ิ
        PROG_ATTACH     , //z(ขz)๓ิ
        PROG_ABSORB     , //z(zฯ)๓ิ
    };

public:
    VreathItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~VreathItem();
};

}
#endif /*VREATHITEM_H_*/

