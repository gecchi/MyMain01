#ifndef ENEMYOEBIUSCONTROLLER002_H_
#define ENEMYOEBIUSCONTROLLER002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "EnemyOebiusController.h"

namespace VioletVreath {

/**
 * エビウスのコアと、エビウス編隊を管理その２ .
 * シーンに追加するアクターはこのアクターです。
 * @version 1.00
 * @since 2015/01/21
 * @author Masatoshi Tsuge
 */
class EnemyOebiusController002 : public EnemyOebiusController {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOebiusController002(const char* prm_name);

    virtual ~EnemyOebiusController002();
};

}
#endif /*ENEMYOEBIUSCONTROLLER002_H_*/

