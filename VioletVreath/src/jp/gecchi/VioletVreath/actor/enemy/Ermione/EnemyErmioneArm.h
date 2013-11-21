#ifndef ENEMYERMIONEARM_H_
#define ENEMYERMIONEARM_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�G�~�I�l�̐G���� .
 * @version 1.00
 * @since 2012/11/06
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArm : public GgafLib::DefaultMeshSetActor {
public:
    enum {
        PROG_INIT   ,
        PROG_WAITING,
        PROG_NOTHING,
        PROG_AIMING ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    angvelo aiming_ang_velo_;
    angle aiming_movable_limit_ang_;
    frame behave_frames_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErmioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

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

    virtual ~EnemyErmioneArm();
};

}
#endif /*ENEMYERMIONEARM_H_*/

