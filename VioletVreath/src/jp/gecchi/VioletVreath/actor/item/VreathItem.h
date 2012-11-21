#ifndef VREATHITEM_H_
#define VREATHITEM_H_

namespace VioletVreath {

/**
 * Vreath回復アイテム小 .
 * @version 1.00
 * @since 2011/11/21
 * @author Masatoshi Tsuge
 */
class VreathItem : public Item {
    /** 吸着差分座標 */
    int kDX_, kDY_, kDZ_;

public:

    enum {
        PROG_NOTIONG = 1, //何もしていない状態
        PROG_DRIFT      , //通常移動状態
        PROG_ATTACH     , //吸着中(未吸着)状態
        PROG_ABSORB     , //吸着中(吸着済)状態
    };


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

