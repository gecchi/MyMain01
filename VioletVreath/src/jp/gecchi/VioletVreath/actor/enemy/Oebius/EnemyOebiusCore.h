#ifndef ENEMYOEBIUSCORE_H_
#define ENEMYOEBIUSCORE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�r�E�X�̃R�A .
 * @version 1.00
 * @since 2014/11/11
 * @author Masatoshi Tsuge
 */
class EnemyOebiusCore : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    EnemyOebiusController* pController_;

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

    /**
     * �G�r�E�X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOebiusCore();
};

}
#endif /*ENEMYOEBIUSCORE_H_*/

