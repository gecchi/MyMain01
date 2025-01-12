#ifndef MAGICPOINTITEM_H_
#define MAGICPOINTITEM_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"
#include "jp/gecchi/VioletVreath/actor/VvItemActor.hpp"


namespace VioletVreath {

/**
 * MP回復アイテム小 .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem : public VvItemActor<GgafLib::DefaultMassMeshActor> {

public:
    /** 吸着差分座標 */
    int kDX_, kDY_, kDZ_;
public:
    MagicPointItem(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

//    int isOutOfView() override {
//        //画面外判定無し
//        return 0;
//    }
//
//    bool isOutOfSpacetime() const override {
//        //ゲーム座標範囲外判定無し
//        return false;
//    }
    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;

    virtual ~MagicPointItem();
};

}
#endif /*MAGICPOINTITEM_H_*/

