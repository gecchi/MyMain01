#ifndef VREATHITEM_H_
#define VREATHITEM_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/Item.h"

namespace VioletVreath {

/**
 * Vreath‰ñ•œƒAƒCƒeƒ€¬ .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class VreathItem : public Item {


public:
    enum {
        PROG_DRIFT      , //’ÊíˆÚ“®ó‘Ô
        PROG_ATTACH     , //‹z’…’†(–¢‹z’…)ó‘Ô
        PROG_ABSORB     , //‹z’…’†(‹z’…Ï)ó‘Ô
        PROG_BANPEI,
    };

    /** ‹z’…·•ªÀ•W */
    int kDX_, kDY_, kDZ_;
    /** •½sˆÚ“®x‰‡ */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    VreathItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~VreathItem();
};

}
#endif /*VREATHITEM_H_*/

