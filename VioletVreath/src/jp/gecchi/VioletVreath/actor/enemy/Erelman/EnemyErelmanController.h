#ifndef ENEMYERELMANCONTROLLER_H_
#define ENEMYERELMANCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/actor/ex/DestructActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * エレルマンのコアと、エレルマン編隊を管理クラス基底 .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class EnemyErelmanController : public GgafCore::DestructActor {

public:
    EnemyErelmanCore* pErelmanCore_;
    FormationErelman* pFormationErelman_;
    GgafDx::GeoElem entry_pos_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyErelmanController(const char* prm_name, EnemyErelmanCore* prm_pCore, FormationErelman* prm_pFormation);

    void setPosition(coord x, coord y, coord z) {
        entry_pos_.x = x;
        entry_pos_.y = y;
        entry_pos_.z = z;
    }

    /**
     *
     */
    void initialize() override;

    /**
     *
     */
    void onActive() override;

    /**
     *
     */
    void processBehavior() override;

    /**
     * コアがヒットしたときのコールバック .
     */
    virtual void onCoreHit() {
    }

    virtual ~EnemyErelmanController();
};

}
#endif /*ENEMYERELMANCONTROLLER_H_*/

