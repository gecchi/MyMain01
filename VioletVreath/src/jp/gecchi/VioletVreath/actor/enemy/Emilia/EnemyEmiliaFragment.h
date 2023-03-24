#ifndef ENEMYASSALIAFRAGMENT_H_
#define ENEMYASSALIAFRAGMENT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/EnemyEmiliaBase.h"

namespace VioletVreath {

/**
 * �G�~���A�f��  .
 * 覐΂̒f��
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class EnemyEmiliaFragment : public EnemyEmiliaBase {

protected:
    /**
     * �j�󂳂ꂽ���̏����R�[���o�b�N .
     * @param prm_pOther �j�󂳂ꂽ����̃A�N�^�[
     */
    void processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) override;

public:
    EnemyEmiliaFragment(const char* prm_name);

    void onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) override;

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyEmiliaFragment();
};

}
#endif /*ENEMYASSALIAFRAGMENT_H_*/

