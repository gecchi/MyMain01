#ifndef WORLDBOUND001_H_
#define WORLDBOUND001_H_

#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * 世界空間 .
 * @version 1.00
 * @since 2010/06/16
 * @author Masatoshi Tsuge
 */
class WorldBound001 : public GgafLib::WorldBoundActor {

public:
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    WorldBound001(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~WorldBound001();
};

}
#endif /*WORLDBOUND001_H_*/

