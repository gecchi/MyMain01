#ifndef ENEMYAIDABASE001_H_
#define ENEMYAIDABASE001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Aida/EnemyAidaBase.h"

namespace VioletVreath {

/**
 * 敵機アイーダの基盤その１ .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyAidaBase001 : public EnemyAidaBase {

public:

    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyAidaBase001(const char* prm_name);
    void initialize() override;
    void processBehavior() override;
    virtual ~EnemyAidaBase001();
};

}
#endif /*ENEMYAIDABASE_H_*/

