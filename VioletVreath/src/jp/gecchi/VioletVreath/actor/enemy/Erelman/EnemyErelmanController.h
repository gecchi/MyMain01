#ifndef ENEMYERELMANCONTROLLER_H_
#define ENEMYERELMANCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/actor/ex/GgafDestructActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"


namespace VioletVreath {

/**
 * エビウスのコアと、エビウス編隊を管理クラス基底 .
 * @version 1.00
 * @since 2015/01/19
 * @author Masatoshi Tsuge
 */
class EnemyErelmanController : public GgafCore::GgafDestructActor {

public:
    EnemyErelmanCore* pErelmanCore_;
    FormationErelman* pFormationErelman_;
    GgafDxCore::GgafDxGeoElem entry_pos_;

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

    virtual ~EnemyErelmanController();
};

}
#endif /*ENEMYERELMANCONTROLLER_H_*/

