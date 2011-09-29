#ifndef MYTORPEDOTAIL_H_
#define MYTORPEDOTAIL_H_
namespace MyStg2nd {

/**
 * 魚雷の移動軌跡エフェクト .
 * @version 1.00
 * @since 2010/09/21
 * @author Masatoshi Tsuge
 */
class MyTorpedoTail : public GgafLib::HomingLaserChip {

public:
    /** [r]軌跡を描く元の魚雷オブジェクト */
    MyTorpedo* _pMyTorpedo;

    /**
     *
     * @param prm_name
     * @param prm_pMyTorpedo 軌跡を描く元の魚雷オブジェクト
     * @return
     */
    MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pMyTorpedo);

    void initialize() override;

    void onInactive() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義 .
     */
    void processBehaviorHeadChip() override;


    virtual ~MyTorpedoTail();

};

}
#endif /*MYTORPEDOTAIL_H_*/

