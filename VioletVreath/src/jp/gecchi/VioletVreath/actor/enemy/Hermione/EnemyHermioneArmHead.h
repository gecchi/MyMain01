#ifndef ENEMYHERMIONEARMHEAD_H_
#define ENEMYHERMIONEARMHEAD_H_
namespace VioletVreath {

/**
 * �G�@�w���~�I�l�̐G��̓��� .
 * �O���̐G��ɒ���b�b�I�I�I
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArmHead : public GgafLib::DefaultMeshSetActor {
public:
    enum {
        PROG_INIT         = 1,
        PROG_NOTHING,
        PROG_AIMING,

    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    angvelo aim_ang_velo_;
    angle aim_movable_limit_ang_;

    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�|�W�g�� */
    DepositoryConnection* pDpcon_;
    GgafCore::GgafActorDepository* pDepo_Fired_;


    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyHermioneArmHead(const char* prm_name);

    /**
     * �������X���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * �������X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �������X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �������X�̐U�镑�� .
     */
    void processBehavior() override;
    /**
     * �������X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �������X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    void config(angle prm_aim_movable_limit_ang,
                frame prm_aim_ang_velo) {
        aim_movable_limit_ang_ = prm_aim_movable_limit_ang;
        aim_ang_velo_ = prm_aim_ang_velo;
    }


    void execAim();
    virtual ~EnemyHermioneArmHead();
};

}
#endif /*ENEMYHERMIONEARMHEAD_H_*/

