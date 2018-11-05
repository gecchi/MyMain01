#ifndef ENEMYDELHEID_H_
#define ENEMYDELHEID_H_

#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�f���w�C�h .
 * ���A��68K�̂R�ʂ̘A�Ȃ����ґ��̓G�̉��I
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class EnemyDelheid : public GgafLib::DefaultMassMorphMeshActor {

public:
    /** �X�v���C���ړ��̃V�[�N�G���X */
    GgafLib::SplineLeader* pKurokoLeader_;
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

    void config(GgafLib::SplineLeader* prm_pKurokoLeader,
                GgafCore::GgafActorDepository* prm_pDepoShot);

    /**
     * �f���w�C�h�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �f���w�C�h���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �f���w�C�h�̐U�镑�� .
     */
    void processBehavior() override;
    void processSettlementBehavior() override;
    /**
     * �f���w�C�h�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �f���w�C�h�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �V���b�g������ .
     */
    void open_shot();



    virtual ~EnemyDelheid();
};

}
#endif /*ENEMYDELHEID_H_*/

