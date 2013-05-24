#ifndef WORLDBOUNDSPACERANKUP_H_
#define WORLDBOUNDSPACERANKUP_H_
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * 通過ステージの世界空間 .
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class WorldBoundSpaceRankUp : public GgafLib::WorldBoundActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBoundSpaceRankUp(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~WorldBoundSpaceRankUp();
};

}
#endif /*WORLDBOUNDSPACERANKUP_H_*/

