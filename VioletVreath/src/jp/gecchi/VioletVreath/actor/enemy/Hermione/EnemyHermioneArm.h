#ifndef ENEMYHERMIONEARM_H_
#define ENEMYHERMIONEARM_H_
namespace VioletVreath {

/**
 * �G�@�w���~�I�l�̐G���� .
 * @version 1.00
 * @since 2012/11/06
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArm : public GgafLib::DefaultMeshSetActor {
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

    angvelo aiming_ang_velo_;
    angle aiming_movable_limit_ang_;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyHermioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    /**
     * ���������i�C���X�^���X������ۏ؁j
     */
    virtual void initialize() override;

    /**
     * ���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    virtual void onActive() override;

    /**
     * �U�镑�� .
     */
    virtual void processBehavior() override;
    /**
     * �U�镑����̔��菈�� .
     */
    virtual void processJudgement() override;


    virtual void onInactive() override;

    /**
     * �r�̐߂̐ݒ� .
     * @param prm_aiming_movable_limit_ang �G�C�~���O���֐߉��p�x�����͈�(10 ���w��� -10 �` +10 �ƌ����ݒ�ɂȂ�)
     * @param prm_aiming_ang_velo �G�C�~���O���֐߉��p���x
     */
    virtual void config(angle prm_aiming_movable_limit_ang,
                        frame prm_aiming_ang_velo) {
        aiming_movable_limit_ang_ = prm_aiming_movable_limit_ang;
        aiming_ang_velo_ = prm_aiming_ang_velo;
    }
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~EnemyHermioneArm();
};

}
#endif /*ENEMYHERMIONEARM_H_*/
