#ifndef ENEMYIDABASE_H_
#define ENEMYIDABASE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * �G�@�C�[�_�̊�� .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIdaBase : public GgafLib::DefaultGeometricActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyIdaBase(const char* prm_name);
    virtual void initialize() override;
    virtual void onActive() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onInactive() override;
    virtual ~EnemyIdaBase();
};
}
#endif /*ENEMYIDABASE_H_*/

