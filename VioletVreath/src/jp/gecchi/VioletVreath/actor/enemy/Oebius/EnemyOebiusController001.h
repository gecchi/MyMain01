#ifndef ENEMYOEBIUSCONTROLLER001_H_
#define ENEMYOEBIUSCONTROLLER001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "EnemyOebiusController.h"

namespace VioletVreath {

/**
 * エビウスのコアと、エビウス編隊を管理その１ .
 * シーンに追加するアクターはこのアクターです。
 * @version 1.00
 * @since 2015/01/21
 * @author Masatoshi Tsuge
 */
class EnemyOebiusController001 : public EnemyOebiusController {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOebiusController001(const char* prm_name);

    virtual ~EnemyOebiusController001();
};

}
#endif /*ENEMYOEBIUSCONTROLLER001_H_*/

