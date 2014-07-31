#ifndef ENEMYUNOMIA_H_
#define ENEMYUNOMIA_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�E�[�m�~�A .
 * n * m �̕ґ��B
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class EnemyUnomia : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        PROG_ENTRY      ,
        PROG_SPLINE_MOVE,
        PROG_MOVE01_1   ,
        PROG_MOVE01_2   ,
        PROG_LEAVE      ,
        PROG_BANPEI,
    };

    enum {
        SE_EXPLOSION ,
    };

    /** �ړ��X�v���C���̃V�[�N�G���X�v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_shotEffect_;

    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyUnomia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �E�[�m�~�A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �E�[�m�~�A�̏�ԃ��Z�b�g���� .
     */
    void onReset() override;

    /**
     * �E�[�m�~�A�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �E�[�m�~�A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �E�[�m�~�A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �E�[�m�~�A�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     *
     * @param prm_pKurokoLeader
     * @param prm_pDepo_shot
     * @param prm_pDepo_shotEffect
     */
    virtual void config(
            GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
            GgafCore::GgafActorDepository* prm_pDepo_shot,
            GgafCore::GgafActorDepository* prm_pDepo_shotEffect
            );


    virtual ~EnemyUnomia();
};

}
#endif /*ENEMYUNOMIA_H_*/

