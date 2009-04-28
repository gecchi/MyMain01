#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public DefaultMeshEnemyActor {

private:

public:
    int _shot_interval;
    int _laser_length;
    int _cnt_laserchip;

    GgafDx9Core::angvelo _angveloTurn;
    LaserChipRotationActor* _pLaserChipRotation;


    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g��
     * @param prm_model ���f����
     */
    EnemyAstraea(const char* prm_name);

    void initialize();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    bool isOffScreen();

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

