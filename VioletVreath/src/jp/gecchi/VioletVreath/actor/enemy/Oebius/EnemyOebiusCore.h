#ifndef ENEMYOEBIUSCORE_H_
#define ENEMYOEBIUSCORE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�r�E�X�̃R�A .
 * @version 1.00
 * @since 2014/11/11
 * @author Masatoshi Tsuge
 */
class EnemyOebiusCore : public GgafLib::DefaultMorphMeshActor {

public:

    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_WAIT01 ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };

    enum {
        SE_DAMAGED  ,
        SE_UNDAMAGED  ,
        SE_EXPLOSION,
        SE_FIRE,
    };

    EnemyOebiusController* pController_;

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOebiusCore(const char* prm_name, EnemyOebiusController* prm_pController);

    void onCreateModel() override;

    /**
     * �G�r�E�X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�r�E�X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
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

    /**
     * �G�r�E�X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOebiusCore();
};

}
#endif /*ENEMYOEBIUSCORE_H_*/

