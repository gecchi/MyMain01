#ifndef ENEMYOZARTIA_H_
#define ENEMYOZARTIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"


namespace VioletVreath {

/**
 * �G�@�I�[�c�@���e�B�A .
 * ������ƌ������^�@�̗\��B
 * @version 1.00
 * @since 2013/10/01
 * @author Masatoshi Tsuge
 */
class EnemyOzartia : public GgafLib::DefaultMorphMeshActor {

public:
    /** �V���b�g�֘A�̐i����� */
    GgafCore::GgafProgress* pProg2_;

    bool is_hit_;

    GgafCore::GgafActorDepository* pDepo_shot01_;
    GgafLib::LaserChipDepository*  pDepo_shot02_;

    GgafDxCore::GgafDxGeoElem posMvTarget_;

    bool faceto_ship_;

    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineLeader* pKurokoLeader01_;

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
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOzartia();
};

}
#endif /*ENEMYOZARTIA_H_*/

