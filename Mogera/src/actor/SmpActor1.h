#ifndef SMPACTOR1_H_
#define SMPACTOR1_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace Mogera {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpActor1 : public GgafLib::DefaultMeshSetActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    SmpActor1(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker);

    virtual ~SmpActor1();
};

}
#endif /*SMPACTOR1_H_*/

