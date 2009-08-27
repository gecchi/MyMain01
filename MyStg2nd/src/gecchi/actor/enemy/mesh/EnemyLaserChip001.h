#ifndef ENEMYLASERCHIP001_H_
#define ENEMYLASERCHIP001_H_
namespace MyStg2nd {

class EnemyLaserChip001 : public CurveLaserChip {


public:
    EnemyLaserChip001(const char* prm_name);

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize();

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~EnemyLaserChip001();

};

}
#endif /*ENEMYLASERCHIP001_H_*/

