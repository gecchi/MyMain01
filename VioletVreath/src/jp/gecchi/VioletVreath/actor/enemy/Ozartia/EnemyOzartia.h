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

    enum {
        PROG1_INIT   ,
        PROG1_ENTRY  ,
        PROG1_STAY   ,
        PROG1_MV_POS0 ,
        PROG1_MV_POS1 ,
        PROG1_MV_POS2 ,
        PROG1_MV_POS3 ,
        PROG1_MV_POS4 ,
        PROG1_MV_POS5 ,
        PROG1_MOVE_START ,
        PROG1_MOVING ,
        PROG1_SP_MV01 ,
        PROG1_LEAVE ,
        PROG_BANPEI1_,
    };

    enum {
        PROG2_WAIT ,
        PROG2_SHOT01_01 ,
        PROG2_SHOT01_02 ,
        PROG2_SHOT02 ,
        PROG2_SHOT03 ,
        PROG2_SHOT04 ,
        PROG2_BANPEI,
    };

    enum {
        MPH_CLOSE  ,
        MPH_SHOT01 ,
        MPH_SHOT02 ,
        MPH_SHOT03 ,
        MPH_SHOT04 ,
    };

    enum {
        SE_ENTRY,
        SE_DAMAGED ,
        SE_UNDAMAGED,
        SE_EXPLOSION,
        SE_SHOT01 ,
        SE_SHOT02 ,
        SE_SHOT03 ,
        SE_SHOT04 ,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** �V���b�g�֘A�̐i����� */
    GgafCore::GgafProgress* pProg2_;

    bool is_hit_;

    GgafCore::GgafActorDepository* pDepo_shot01_;
    GgafLib::LaserChipDepository*  pDepo_shot02_;

    GgafDxCore::GgafDxGeoElem posMvTarget_;

    bool faceang_to_ship_;

    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineKurokoLeader* pKurokoLeader01_;

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

