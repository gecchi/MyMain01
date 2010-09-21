#ifndef MYTORPEDOTAIL_H_
#define MYTORPEDOTAIL_H_
namespace MyStg2nd {

class MyTorpedoTail : public GgafDx9LibStg::HomingLaserChip {


public:
//    GgafDx9Core::GgafDx9GeometricActor* _pTarget;
    MyTorpedo* _pMyTorpedo;
    MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pMyTorpedo);

    void initialize() override;

    void onInactive() override;

    void onActive() override;

    /**
     * �擪�`�b�v�̓������`
     */
    void processBehaviorHeadChip() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~MyTorpedoTail();

};

}
#endif /*MYTORPEDOTAIL_H_*/

