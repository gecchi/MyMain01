#ifndef ZAKO_H_
#define ZAKO_H_

#include "jp/gecchi/VioletVrain/actor/kind/VvEnemyActor.h"
#include "jp/gecchi/VioletVrain/VioletVrain.h"

#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVrain {

/**
 * テスト
 * @author Masatoshi Tsuge
 */
class Zako : public VvEnemyActor<GgafLib::DefaultSpriteActor> {

public:
    Zako(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onReset() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~Zako();

    static GgafCore::Status* resetZakoStatus(GgafCore::Status* p) {
        _TRACE_("むっはー");
        return nullptr;
    }
};

}
#endif /*ZAKO_H_*/

