#ifndef ENEMYOZARTIA_H_
#define ENEMYOZARTIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"


namespace VioletVreath {

/**
 * �G�@�I�[�c�@���e�B�A .
 * ������ƌ������^�@�̗\��B
 * @version 1.00
 * @since 2013/10/01
 * @author Masatoshi Tsuge
 */
class EnemyOzartia : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    /** �V���b�g�֘A�̃t�F�[�Y */
    GgafCore::Phase* pPhase2_;

    bool is_hit_;

    GgafCore::ActorDepository* pDepo_shot01_;
    GgafLib::LaserChipDepository*  pDepo_shot02_;

    GgafDx::GeoElem posMvTarget_;

    bool faceto_ship_;

    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader01_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOzartia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �I�[�c�@���e�B�A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �I�[�c�@���e�B�A���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �I�[�c�@���e�B�A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �I�[�c�@���e�B�A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �I�[�c�@���e�B�A�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOzartia();
};

}
#endif /*ENEMYOZARTIA_H_*/

