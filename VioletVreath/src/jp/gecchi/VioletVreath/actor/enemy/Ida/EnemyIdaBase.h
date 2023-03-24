#ifndef ENEMYIDABASE_H_
#define ENEMYIDABASE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * 敵機イーダの基盤 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIdaBase : public GgafLib::DefaultGeometricActor {

public:
    /**
     * コンストラクタ
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

