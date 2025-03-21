#ifndef ENEMYERELMANCONTROLLER003_H_
#define ENEMYERELMANCONTROLLER003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "EnemyErelmanController.h"

namespace VioletVreath {

/**
 * エレルマンのコアと、エレルマン編隊を管理その１ .
 * シーンに追加するアクターはこのアクターです。
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanController003 : public EnemyErelmanController {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErelmanController003(const char* prm_name);

    virtual void onCoreHit() override;

    virtual ~EnemyErelmanController003();
};

}
#endif /*ENEMYERELMANCONTROLLER003_H_*/

