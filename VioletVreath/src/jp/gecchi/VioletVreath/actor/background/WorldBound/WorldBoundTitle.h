#ifndef WORLDBOUNDTITLE_H_
#define WORLDBOUNDTITLE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * タイトルの世界空間 .
 * @version 1.00
 * @since 2012/01/10
 * @author Masatoshi Tsuge
 */
class WorldBoundTitle : public GgafLib::WorldBoundActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBoundTitle(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void fadein();

    virtual ~WorldBoundTitle();
};

}
#endif /*WORLDBOUNDTITLE_H_*/

