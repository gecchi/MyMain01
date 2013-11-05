#ifndef ENEMYDELHEID_H_
#define ENEMYDELHEID_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�f���n�C�h .
 * ���A��68K�̂R�ʂ̘A�Ȃ����ґ��̓G�̉��I
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class EnemyDelheid : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT,
        PROG_SPLINE_MOVING,
        PROG_AFTER_LEAD,
        PROG_AFTER_LEAD_MOVING,
        PROG_BANPEI,
    };
    enum {
        PROG2_WAIT,
        PROG2_OPEN,
        PROG2_SHOT,
        PROG2_CLOSE,
        PROG_BANPEI2_,
    };
    enum {
        MPH_CLOSE,
        MPH_OPEN,
    };
    enum {
        SE_DAMAGED  ,
        SE_UNDAMAGED,
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
    EnemyDelheid(const char* prm_name);

    void onCreateModel() override;

    void nextFrame() override;

    void config(GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
                GgafCore::GgafActorDepository* prm_pDepoShot);

    /**
     * �f���n�C�h�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �f���n�C�h�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �f���n�C�h�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �f���n�C�h�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �f���n�C�h�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �V���b�g������ .
     */
    void open_shot();



    virtual ~EnemyDelheid();
};

}
#endif /*ENEMYDELHEID_H_*/

