#ifndef ENEMYTHAGORAS_H_
#define ENEMYTHAGORAS_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�^�S���X .
 * �g�����W�b�g���x���P
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class EnemyThagoras : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** �ړ��X�v���C���v���O���� */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** �ۓ�(�X�P�[��)�𓯊�������ׂ̃_�~�[�A�N�^�[ */
    GgafLib::DefaultGeometricActor* pActor4Sc_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyThagoras(const char* prm_name);

    void onCreateModel() override;

    /**
     * �^�S���X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �^�S���X���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �^�S���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �^�S���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �^�S���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyThagoras();
};

}
#endif /*ENEMYTHAGORAS_H_*/

