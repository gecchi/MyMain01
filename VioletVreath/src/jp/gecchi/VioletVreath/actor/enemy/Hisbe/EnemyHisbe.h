#ifndef ENEMYHISBE_H_
#define ENEMYHISBE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {


/**
 * �G�@�q�Y�r�[ .
 * �q���x���g���[�U�[�������܂��B
 * @version 1.00
 * @since 2012/06/29
 * @author Masatoshi Tsuge
 */
class EnemyHisbe :  public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {
//class EnemyHisbe : public VvEnemyActor<GgafLib::CubeMapMorphMeshActor> {

    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineLeader* pRikishaLeader_;
    /** �e�X�g�b�N */
    GgafCore::ActorDepository* pDepo_shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::ActorDepository* pDepo_effect_;


    DepositoryConnection* pConn_pDepoStore_laser_set;

    GgafLib::LaserChipDepository* pLaserChipDepo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyHisbe(const char* prm_name);

    void onCreateModel() override;

    /**
     * �q�Y�r�[�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �q�Y�r�[���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �q�Y�r�[�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �q�Y�r�[�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �q�Y�r�[�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ���˒eDepository�ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pDepo
     */
    void setDepository_Shot(GgafCore::ActorDepository* prm_pDepo) {
        pDepo_shot_ = prm_pDepo;
    }

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pRikishaLeader
     */
    void setSplineRikishaLeader(GgafLib::SplineLeader* prm_pRikishaLeader) {
        pRikishaLeader_ = prm_pRikishaLeader;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pDepo
     */
    void setDepository_ShotEffect(GgafCore::ActorDepository* prm_pDepo) {
        pDepo_effect_ = prm_pDepo;
    }

    virtual ~EnemyHisbe();
};

}
#endif /*ENEMYHISBE_H_*/

