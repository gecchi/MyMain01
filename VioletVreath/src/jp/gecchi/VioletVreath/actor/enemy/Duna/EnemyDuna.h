#ifndef ENEMYDUNA_H_
#define ENEMYDUNA_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�h�D�[�i(�쐬���I) .
 * ���[���N���X�^�̃R�[���h�A�C�̂悤�ȓ����ɒ���b�I�I�B
 * @version 1.00
 * @since 2013/08/22
 * @author Masatoshi Tsuge
 */
class EnemyDuna : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    GgafDx::GeoElem next_pos_;
    int nprog_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyDuna(const char* prm_name);

    void onCreateModel() override;

    /**
     * �h�D�[�i�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �h�D�[�i���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �h�D�[�i�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �h�D�[�i�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �h�D�[�i�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyDuna();
};

}
#endif /*ENEMYDUNA_H_*/

