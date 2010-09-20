#ifndef MYTORPEDOTAIL_H_
#define MYTORPEDOTAIL_H_
namespace MyStg2nd {

class MyTorpedoTail : public GgafDx9LibStg::HomingLaserChip {


public:
    GgafDx9Core::GgafDx9GeometricActor* _pTarget;

    MyTorpedoTail(const char* prm_name);

    void initialize() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~MyTorpedoTail();

};

}
#endif /*MYTORPEDOTAIL_H_*/

