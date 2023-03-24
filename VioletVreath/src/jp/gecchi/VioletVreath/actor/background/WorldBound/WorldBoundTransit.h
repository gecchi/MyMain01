#ifndef WORLDBOUNDTRANSIT_H_
#define WORLDBOUNDTRANSIT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * 通過ステージの世界空間 .
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class WorldBoundTransit : public GgafLib::WorldBoundActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBoundTransit(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~WorldBoundTransit();
};

}
#endif /*WORLDBOUNDTRANSIT_H_*/

