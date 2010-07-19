#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public GgafDx9LibStg::DefaultMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int _cnt_laserchip;

public:
    /** �����]���Ԋu(frame) */
    int _shot_interval;
    /** ���˃��[�U�[�`�b�v�̐� */
    int _laser_length;
    /** Way��     */
    int _laser_way;

    angle* _paWayRz;
    angle* _paWayRy;
    /** �����]���p���x */
    angvelo _angveloTurn;

    LaserChipDispatcher*** _papapLaserChipDispatcher;

    EnemyAstraea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    bool isOutOfGameSpace() override;

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

