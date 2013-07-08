#ifndef ENEMYASSALIA_H_
#define ENEMYASSALIA_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Assalia/EnemyAssaliaBase.h"

namespace VioletVreath {

/**
 * マッサリア  .
 * 隕石群の隕石
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyAssalia : public EnemyAssaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyAssalia(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyAssalia();
};

}
#endif /*ENEMYASSALIA_H_*/

