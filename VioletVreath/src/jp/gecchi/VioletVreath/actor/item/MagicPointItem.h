#ifndef MAGICPOINTITEM_H_
#define MAGICPOINTITEM_H_
#include "jp/gecchi/VioletVreath/actor/item/Item.h"

namespace VioletVreath {

/**
 * MP回復アイテム小 .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem : public Item {
    /** 吸着差分座標 */
    int kDX_, kDY_, kDZ_;

public:
    enum {
        PROG_DRIFT      , //通常移動状態
        PROG_ATTACH     , //吸着中(未吸着)状態
        PROG_ABSORB     , //吸着中(吸着済)状態
    };

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
//        //画面外判定無し
//        return 0;
//    }
//
//    bool isOutOfUniverse() override {
//        //ゲーム座標範囲外判定無し
//        return false;
//    }
    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MagicPointItem();
};

}
#endif /*MAGICPOINTITEM_H_*/

