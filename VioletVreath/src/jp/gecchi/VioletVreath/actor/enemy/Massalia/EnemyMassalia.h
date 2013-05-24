#ifndef ENEMYMASSALIA_H_
#define ENEMYMASSALIA_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaBase.h"

namespace VioletVreath {

/**
 * �}�b�T���A  .
 * 覐ΌQ��覐�
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyMassalia : public EnemyMassaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyMassalia(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyMassalia();
};

}
#endif /*ENEMYMASSALIA_H_*/

