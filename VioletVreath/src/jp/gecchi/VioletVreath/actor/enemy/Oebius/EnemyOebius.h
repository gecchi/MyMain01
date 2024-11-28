#ifndef ENEMYOEBIUS_H_
#define ENEMYOEBIUS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�G�r�E�X .
 * ���r�E�X�̑т̕ґ��v��
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class EnemyOebius : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafDx::VehicleLeader* pVehicleLeader_;

    bool scatter_flg_;

    frame delay_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOebius(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G�r�E�X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�r�E�X���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�r�E�X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�r�E�X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    void onInactive() override;

    /**
     * �U��U��ɂȂ� .
     */
    void scatter();


    virtual ~EnemyOebius();
};

}
#endif /*ENEMYOEBIUS_H_*/

