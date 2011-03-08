#ifndef MAGICPOINTITEM001_H_
#define MAGICPOINTITEM001_H_




namespace MyStg2nd {

/**
 * アイテム .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem001 : public Item {
    /** 吸着差分座標 */
    int _kDX, _kDY, _kDZ;

public:
    MagicPointItem001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

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

    virtual ~MagicPointItem001();
};

}
#endif /*MAGICPOINTITEM001_H_*/

