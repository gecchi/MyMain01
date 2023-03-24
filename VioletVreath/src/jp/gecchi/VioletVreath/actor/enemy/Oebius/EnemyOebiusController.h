#ifndef ENEMYOEBIUSCONTROLLER_H_
#define ENEMYOEBIUSCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/actor/ex/DestructActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"


namespace VioletVreath {

/**
 * エビウスのコアと、エビウス編隊を管理クラス基底 .
 * @version 1.00
 * @since 2015/01/19
 * @author Masatoshi Tsuge
 */
class EnemyOebiusController : public GgafCore::DestructActor {

public:
    EnemyOebiusCore* pOebiusCore_;
    FormationOebius* pFormationOebius_;
    GgafDx::GeoElem entry_pos_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyOebiusController(const char* prm_name, EnemyOebiusCore* prm_pCore, FormationOebius* prm_pFormation);

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

    virtual ~EnemyOebiusController();
};

}
#endif /*ENEMYOEBIUSCONTROLLER_H_*/

