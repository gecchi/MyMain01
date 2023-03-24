#ifndef WORLDBOUNDNAMEENTRY_H_
#define WORLDBOUNDNAMEENTRY_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * ネームエントリー時の世界空間 .
 * @version 1.00
 * @since 2012/10/14
 * @author Masatoshi Tsuge
 */
class WorldBoundNameEntry : public GgafLib::WorldBoundActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBoundNameEntry(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void fadein();

    void fadeout();

    virtual ~WorldBoundNameEntry();
};

}
#endif /*WORLDBOUNDNAMEENTRY_H_*/

