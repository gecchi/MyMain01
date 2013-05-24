#ifndef ENEMYADELHEID_H_
#define ENEMYADELHEID_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�A�[�f���n�C�h .
 * ���A��68K�̂R�ʂ̘A�Ȃ����ґ��̓G�̉��I
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class EnemyAdelheid : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT,
        PROG_SPLINE_MOVING,
        PROG_AFTER_LEAD,
        PROG_AFTER_LEAD_MOVING,
    };
    enum {
        PROG2_WAIT,
        PROG2_OPEN,
        PROG2_SHOT,
        PROG2_CLOSE,
    };
    enum {
        MPH_CLOSE,
        MPH_OPEN,
    };
    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    /** �X�v���C���ړ��̃V�[�N�G���X */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �V���b�g�̃f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepoShot_;
    /** �V���b�g�J�n���� */
    frame shot_begin_frame_;
    /** �V���b�g�֘A�̐i����� */
    GgafCore::GgafProgress* pProg2_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAdelheid(const char* prm_name);

    void onCreateModel() override;

    void nextFrame() override;

    void config(GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
                GgafCore::GgafActorDepository* prm_pDepoShot);

    /**
     * �A�[�f���n�C�h�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A�[�f���n�C�h�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A�[�f���n�C�h�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A�[�f���n�C�h�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A�[�f���n�C�h�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �V���b�g������ .
     */
    void open_shot();



    virtual ~EnemyAdelheid();
};

}
#endif /*ENEMYADELHEID_H_*/

