#ifndef SEACTOR3_H_
#define SEACTOR3_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * テストキャラクタ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SeActor3 : public GgafLib::DefaultMeshActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    SeActor3(const char* prm_name);

    /**
     * キャラの初期処理 .
     */
    void initialize() override;

    /**
     * キャラの振る舞い処理 .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker);

    virtual ~SeActor3();
};

}
#endif /*SEACTOR3_H_*/

