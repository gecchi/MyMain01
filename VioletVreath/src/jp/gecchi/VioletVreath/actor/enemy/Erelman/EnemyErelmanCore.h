#ifndef ENEMYERELMANCORE_H_
#define ENEMYERELMANCORE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/kind/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�����}���̃R�A .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanCore : public VvEnemyActor<GgafLib::DefaultMorphMeshActor> {

public:
    EnemyErelmanController* pController_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyErelmanCore(const char* prm_name, EnemyErelmanController* prm_pController);

    void onCreateModel() override;

    /**
     * �G�����}���̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�����}�����A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�����}���̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�����}���̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G�����}���̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyErelmanCore();
};

}
#endif /*ENEMYERELMANCORE_H_*/

