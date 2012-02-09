#ifndef MAGICPOINTITEM_H_
#define MAGICPOINTITEM_H_

namespace MyStg2nd {

/**
 * MP回復アイテム小 .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem : public Item {
    /** 吸着差分座標 */
    int _kDX, _kDY, _kDZ;

public:
    MagicPointItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

//    int isOutOfView() override {
//        //画面外判定無し
//        return 0;
//    }
//
//    bool isOutOfUniverse() override {
//        //ゲーム座標範囲外判定無し
//        return false;
//    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MagicPointItem();
};

}
#endif /*MAGICPOINTITEM_H_*/

