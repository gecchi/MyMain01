#ifndef SMPACTOR2_H_
#define SMPACTOR2_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpActor2 : public GgafLib::DefaultMeshActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    SmpActor2(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor);

    virtual ~SmpActor2();
};

}
#endif /*SMPACTOR2_H_*/

