#ifndef ENEMYMASSALIA_H_
#define ENEMYMASSALIA_H_
namespace MyStg2nd {

/**
 * �}�b�T���A  .
 */
class EnemyMassalia : public GgafDx9LibStg::DefaultMeshActor {

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

    StoreConnection* _pStoreCon_RefractionEffect;

    StoreConnection* _pStoreCon_DpEnemyMassaliaLaserChip;



    GgafDx9LibStg::LaserChipStore*** _papapLaserChipStore;

    /** �o���G�t�F�N�g */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_Appearance;

    EnemyMassalia(const char* prm_name);

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

    virtual ~EnemyMassalia();
};

}
#endif /*ENEMYMASSALIA_H_*/

