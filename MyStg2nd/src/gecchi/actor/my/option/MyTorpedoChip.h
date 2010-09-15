#ifndef MYTORPEDOCHIP_H_
#define MYTORPEDOCHIP_H_
namespace MyStg2nd {

class MyTorpedoChip : public GgafDx9LibStg::HomingLaserChip {


public:
    MyTorpedoChip(const char* prm_name);

    void initialize() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~MyTorpedoChip();

};

}
#endif /*MYTORPEDOCHIP_H_*/

