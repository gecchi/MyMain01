#ifndef SCOREITEM_H_
#define SCOREITEM_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/item/Item.h"

namespace VioletVreath {

/**
 * Score๑ACeฌ .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class ScoreItem : public Item {

public:
    enum {
        PROG_DRIFT      , //สํฺฎ๓ิ
        PROG_ATTACH     , //z(ขz)๓ิ
        PROG_ABSORB     , //z(zฯ)๓ิ
        PROG_BANPEI,
    };
    /** zทชภW */
    int kDX_, kDY_, kDZ_;
    /** ฝsฺฎx */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;
public:
    ScoreItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~ScoreItem();
};

}
#endif /*SCOREITEM_H_*/

