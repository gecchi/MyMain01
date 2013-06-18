#ifndef ENEMYAIDABASE_H_
#define ENEMYAIDABASE_H_
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * 敵機アイーダの基盤 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyAidaBase : public GgafLib::DefaultGeometricActor {

public:

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAidaBase(const char* prm_name);
    virtual void initialize() override;
    virtual void onActive() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onInactive() override;
    virtual ~EnemyAidaBase();
};

}
#endif /*ENEMYAIDABASE_H_*/

