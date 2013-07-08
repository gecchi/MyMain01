#ifndef ENEMYERMIONEARMBODY_H_
#define ENEMYERMIONEARMBODY_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArm.h"

namespace VioletVreath {

/**
 * �G�@�G�~�I�l�̐G��̓��� .
 * �O���̐G��ɒ���b�b�I�I�I
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArmBody : public EnemyErmioneArm {
public:

    EnemyErmioneArmBody(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyErmioneArmBody();
};

}
#endif /*ENEMYERMIONEARMBODY_H_*/

