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
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;
    /** ���[�U���ˊԊu(frame) */
    int _laser_interval;
    /** ���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int _laser_length;
    /** ���[�U�[Way��(n�~n)�̈�ӂ̖{�� */
    int _laser_way;
    /** ���[�U�[�ƃ��[�U�[�̊Ԋu�J���p�x */
    angle _angClearance;
    /** �����]���p���x */
    angvelo _angveloTurn;


    struct PosLaser {
        int X;
        int Y;
        int Z;
    };
    /** ���[�U�[���˃��[�J�����W */
    PosLaser** _papaPosLaser;

    GgafDx9LibStg::LaserChipDispatcher*** _papapLaserChipDispatcher;

    /** �o���G�t�F�N�g */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_Appearance;

    EnemyAstraea(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    void processFinal() override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAstraea();
};

}
#endif /*ENEMYASTRAEA_H_*/

