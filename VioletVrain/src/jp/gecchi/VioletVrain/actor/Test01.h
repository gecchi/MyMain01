#ifndef TEST01_H_
#define TEST01_H_

#include "jp/gecchi/VioletVrain/actor/kind/VvEnemyActor.h"
#include "jp/gecchi/VioletVrain/VioletVrain.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVrain {

/**
 * テスト
 * @author Masatoshi Tsuge
 */
class Test01 : public VvEnemyActor<GgafLib::DefaultSpriteActor> {

public:
    Test01(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onReset() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~Test01();

    static GgafCore::Status* resetTest01Status(GgafCore::Status* p) {
        _TRACE_("むっはー");
        return nullptr;
    }
};

}
#endif /*TEST01_H_*/

