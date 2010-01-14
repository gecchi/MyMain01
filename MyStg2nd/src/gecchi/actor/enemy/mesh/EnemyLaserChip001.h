#ifndef ENEMYLASERCHIP001_H_
#define ENEMYLASERCHIP001_H_
namespace MyStg2nd {

class EnemyLaserChip001 : public HomingLaserChip {


public:
    EnemyLaserChip001(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    void onActive();

    void processBehaviorHeadChip();



    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pOtherActor);


    virtual ~EnemyLaserChip001();

};

}
#endif /*ENEMYLASERCHIP001_H_*/

