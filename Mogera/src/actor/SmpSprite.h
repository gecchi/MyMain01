#ifndef SMPSPRITE_H_
#define SMPSPRITE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"

namespace Mogera {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpSprite : public GgafLib::DefaultFramedSpriteActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    SmpSprite(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor);

    virtual ~SmpSprite();
};

}
#endif /*SMPSPRITE_H_*/

