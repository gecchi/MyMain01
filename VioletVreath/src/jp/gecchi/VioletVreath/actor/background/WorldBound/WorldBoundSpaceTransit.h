#ifndef WORLDBOUNDSPACETRANSIT_H_
#define WORLDBOUNDSPACETRANSIT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * �ʉ߃X�e�[�W�̐��E��� .
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class WorldBoundSpaceTransit : public GgafLib::WorldBoundActor {

public:
    /**
     * �R���X�g���N�^
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

