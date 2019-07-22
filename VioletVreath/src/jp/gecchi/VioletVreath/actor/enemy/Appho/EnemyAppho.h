#ifndef ENEMYAPPHO_H_
#define ENEMYAPPHO_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�A�b�|�[ .
 * ���A�˂U�WK�̎G���̂悤�ɁA
 * ����āA�ڂ̑O�ɃX�[���Ɨ��āA
 * ������ƃE���E�����āA�X�[���Ɠ�����B
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class EnemyAppho : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** [r]�o�����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDx::GeoElem entry_pos_;
    /** [r]�E���E��������W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDx::GeoElem stagnating_pos_;
    /** [r]�ޏo���W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDx::GeoElem leave_pos_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAppho(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A�b�|�[�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A�b�|�[���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A�b�|�[�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A�b�|�[�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A�b�|�[�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyAppho();
};

}
#endif /*ENEMYAPPHO_H_*/

