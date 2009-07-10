#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public GgafDx9LibStg::DefaultMeshSetActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int _cnt_laserchip;

public:
    /** �����]���Ԋu(frame) */
    int _shot_interval;
    /** ���˃��[�U�[�`�b�v�̐� */
    int _laser_length;
    /** �����]���p���x */
    GgafDx9Core::angvelo _angveloTurn;

    LaserChipDispatcher* _pLaserChipDispatcher;

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

