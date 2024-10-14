#ifndef SMPPIEGRAPHSPRITE_H_
#define SMPPIEGRAPHSPRITE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/PieGraphSpriteActor.h"

namespace Mogera {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpPieGraphSprite : public GgafLib::PieGraphSpriteActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    SmpPieGraphSprite(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor);

    virtual ~SmpPieGraphSprite();
};

}
#endif /*SMPPIEGRAPHSPRITE_H_*/

