#ifndef WORLDBOUNDSPACETRANSIT_H_
#define WORLDBOUNDSPACETRANSIT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * 通過ステージの世界空間 .
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class WorldBoundSpaceTransit : public GgafLib::WorldBoundActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBoundSpaceTransit(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~WorldBoundSpaceTransit();
};

}
#endif /*WORLDBOUNDSPACETRANSIT_H_*/

