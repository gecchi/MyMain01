#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public GgafDx9LibStg::DefaultMorphMeshActor {

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

    GgafDx9Core::angle* _paWayRz;
    GgafDx9Core::angle* _paWayRy;
    /** �����]���p���x */
    GgafDx9Core::angvelo _angveloTurn;

    LaserChipDispatcher*** _papapLaserChipDispatcher;

    EnemyAstraea(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }
    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    int isOutOfGameSpace() override;

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

