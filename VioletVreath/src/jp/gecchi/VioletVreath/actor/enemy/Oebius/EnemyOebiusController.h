#ifndef ENEMYOEBIUSCONTROLLER_H_
#define ENEMYOEBIUSCONTROLLER_H_
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
class EnemyOebiusController : public GgafCore::GgafDestructActor {

public:

    enum {
        PROG_INIT  ,
        PROG_ENTRY_CORE ,
        PROG_WAIT01 ,
        PROG_ENTRY_FORMATION ,
        PROG_WAIT02 ,
        PROG_BANPEI,
    };

    EnemyOebiusCore* pOebiusCore_;
    FormationOebius* pFormationOebius_;
    GgafDxCore::GgafDxGeoElem entry_pos_;

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

    void scatterOebiusFormation();

    virtual ~EnemyOebiusController();
};

}
#endif /*ENEMYOEBIUSCONTROLLER_H_*/

