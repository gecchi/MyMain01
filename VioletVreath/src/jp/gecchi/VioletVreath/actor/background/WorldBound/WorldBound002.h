#ifndef WORLDBOUND002_H_
#define WORLDBOUND002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * 世界空間 .
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBound002 : public GgafLib::WorldBoundActor {

public:
    float base_u_;
    float base_v_;

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBound002(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~WorldBound002();
};

}
#endif /*WORLDBOUND002_H_*/

