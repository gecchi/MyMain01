#ifndef ENEMYLASERCHIP001_H_
#define ENEMYLASERCHIP001_H_
namespace MyStg2nd {

class EnemyLaserChip001 : public GgafDx9LibStg::HomingLaserChip {


public:
    EnemyLaserChip001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize() override;

    void onActive() override;

    void processBehaviorHeadChip();



    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }

    /**
     * ��OverRide �ł���
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    virtual ~EnemyLaserChip001();

};

}
#endif /*ENEMYLASERCHIP001_H_*/

