#ifndef ENEMYANTIOPE_H_
#define ENEMYANTIOPE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�A���e�B�I�y .
 * �����Ɣ������̏u���̂悤�ȃC���[�W�̓���
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class EnemyAntiope :
    public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** ���s�ړ����x�x�N�g�� */
    GgafDx::GeoElem mv_velo_twd_;
    /** ���� */
    EnemyAntiope* pP_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAntiope(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

    void onCreateModel() override;

    /**
     * �A���e�B�I�y�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A���e�B�I�y���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A���e�B�I�y�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A���e�B�I�y�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A���e�B�I�y�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAntiope();
};

}
#endif /*ENEMYANTIOPE_H_*/

