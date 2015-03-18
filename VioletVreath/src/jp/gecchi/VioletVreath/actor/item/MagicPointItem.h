#ifndef MAGICPOINTITEM_H_
#define MAGICPOINTITEM_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/Item.h"

namespace VioletVreath {

/**
 * MP‰ñ•œƒAƒCƒeƒ€¬ .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem : public Item {

public:
    enum {
        PROG_DRIFT      , //’ÊíˆÚ“®ó‘Ô
        PROG_ATTACH     , //‹z’…’†(–¢‹z’…)ó‘Ô
        PROG_ABSORB     , //‹z’…’†(‹z’…Ï)ó‘Ô
        PROG_BANPEI,
    };

    enum {
        SE_GET_ITEM ,
    };

    /** •½sˆÚ“®x‰‡ */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;
    /** ‹z’…·•ªÀ•W */
    int kDX_, kDY_, kDZ_;
public:
    MagicPointItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

//    int isOutOfView() override {
//        //‰æ–ÊŠO”»’è–³‚µ
//        return 0;
//    }
//
//    bool isOutOfUniverse() const override {
//        //ƒQ[ƒ€À•W”ÍˆÍŠO”»’è–³‚µ
//        return false;
//    }
    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MagicPointItem();
};

}
#endif /*MAGICPOINTITEM_H_*/

