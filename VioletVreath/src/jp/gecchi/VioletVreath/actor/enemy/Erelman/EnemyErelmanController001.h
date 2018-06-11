#ifndef ENEMYERELMANCONTROLLER001_H_
#define ENEMYERELMANCONTROLLER001_H_
#include "VioletVreath.h"
#include "EnemyErelmanController.h"

namespace VioletVreath {

/**
 * エビウスのコアと、エビウス編隊を管理その１ .
 * シーンに追加するアクターはこのアクターです。
 * @version 1.00
 * @since 2015/01/21
 * @author Masatoshi Tsuge
 */
class EnemyErelmanController001 : public EnemyErelmanController {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErelmanController001(const char* prm_name);

    virtual ~EnemyErelmanController001();
};

}
#endif /*ENEMYERELMANCONTROLLER001_H_*/

