#ifndef ENEMYASTRAEA_H_
#define ENEMYASTRAEA_H_
namespace MyStg2nd {

#define ASTRAEA_PROG_MOVE  1
#define ASTRAEA_PROG_TURN  2
#define ASTRAEA_PROG_FIRE  3

/**
 * �A�X�g���G�A .
 */
class EnemyAstraea : public GgafDx9LibStg::DefaultMeshActor {

private:
    /** ���ˍς݃��[�U�[�`�b�v�� */
    int _cnt_laserchip;
public:
    /** ���[�U���ˊԊu(frame) */
    int _laser_interval;
    /** ���˃��[�U�[�`�b�v�̐��i���[�U�[�����j */
    int _laser_length;
    /** ���[�U�[Way��(n�~n)�̈�ӂ̖{�� */
    int _laser_way;
    /** ���[�U�[�ƃ��[�U�[�̊Ԋu�J���p�x */
    angle _angClearance;
    /** �����]���p���x */
    ang_velo _ang_veloTurn;


    struct PosLaser {
        int X;
        int Y;
        int Z;
    };
    /** ���[�U�[���˃��[�J�����W */
    PosLaser** _papaPosLaser;

    StoreConnection* _pCon_RefractionEffectStore;

    StoreConnection* _pCon_LaserChipStoreDp;



    GgafDx9LibStg::LaserChipStore*** _papapLaserChipStore;

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

