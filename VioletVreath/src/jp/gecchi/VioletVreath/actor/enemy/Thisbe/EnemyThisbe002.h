#ifndef ENEMYTHISBE002_H_
#define ENEMYTHISBE002_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {


/**
 * �G�@�V�Y�r�[ .
 * �q���x���g���[�U�[�������܂��B
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyThisbe002 :  public GgafLib::DefaultMorphMeshActor {
//class EnemyThisbe002 : public GgafLib::CubeMapMorphMeshActor {

    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_Shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_ShotEffect_;

public:
    enum {
        PROG_WAIT,
        PROG_OPEN,
        PROG_FIRE,
        PROG_CLOSE,
    };
    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyThisbe002(const char* prm_name);

    void onCreateModel() override;

    /**
     * �V�Y�r�[�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �V�Y�r�[���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �V�Y�r�[�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �V�Y�r�[�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �V�Y�r�[�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ���˒eDepository�ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pDepo
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_Shot_ = prm_pDepo;
    }

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pKurokoLeader
     */
    void setSplineKurokoLeader(GgafLib::SplineKurokoLeader* prm_pKurokoLeader) {
        pKurokoLeader_ = prm_pKurokoLeader;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_ShotEffect_ = prm_pDepo;
    }

    virtual ~EnemyThisbe002();
};

}
#endif /*ENEMYTHISBE002_H_*/

