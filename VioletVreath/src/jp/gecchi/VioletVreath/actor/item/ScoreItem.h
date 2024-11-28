#ifndef SCOREITEM_H_
#define SCOREITEM_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"
#include "jp/gecchi/VioletVreath/actor/VvItemActor.hpp"

namespace VioletVreath {

/**
 * Score回復アイテム小 .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class ScoreItem : public VvItemActor<GgafLib::DefaultMassMeshActor> {

public:
    /** 吸着差分座標 */
    int kDX_, kDY_, kDZ_;
public:
    ScoreItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

    virtual void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~ScoreItem();
};

}
#endif /*SCOREITEM_H_*/

