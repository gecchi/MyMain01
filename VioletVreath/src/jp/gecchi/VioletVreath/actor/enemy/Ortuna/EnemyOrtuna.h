#ifndef ENEMYORTUNA_H_
#define ENEMYORTUNA_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�I���g�D�i .
 * �r���[�|�C���g�Q�ʐ��ʂ��烏�������o�鋛�G���݂����Ȃ��
 * @version 1.00
 * @since 2013/08/05
 * @author Masatoshi Tsuge
 */
class EnemyOrtuna : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    /** [r]�o�����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDx::GeoElem entry_pos_;
    /** [r]�܂�Ԃ����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDx::GeoElem stagnating_pos_;

    frame stagnating_pos_frames_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOrtuna(const char* prm_name);

    void onCreateModel() override;

    /**
     * �I���g�D�i�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �I���g�D�i���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �I���g�D�i�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �I���g�D�i�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �I���g�D�i�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOrtuna();
};

}
#endif /*ENEMYAPPHO_H_*/

