#ifndef VREATHITEM_H_
#define VREATHITEM_H_

namespace VioletVreath {

/**
 * Vreath‰ñ•œƒAƒCƒeƒ€¬ .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class VreathItem : public Item {
    /** ‹z’…·•ªÀ•W */
    int kDX_, kDY_, kDZ_;

public:
    enum {
        PROG_NOTIONG = 1, //‰½‚à‚µ‚Ä‚¢‚È‚¢ó‘Ô
        PROG_DRIFT      , //’ÊíˆÚ“®ó‘Ô
        PROG_ATTACH     , //‹z’…’†(–¢‹z’…)ó‘Ô
        PROG_ABSORB     , //‹z’…’†(‹z’…Ï)ó‘Ô
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

