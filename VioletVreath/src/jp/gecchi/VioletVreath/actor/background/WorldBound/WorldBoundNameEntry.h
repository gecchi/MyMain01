#ifndef WORLDBOUNDNAMEENTRY_H_
#define WORLDBOUNDNAMEENTRY_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * �l�[���G���g���[���̐��E��� .
 * @version 1.00
 * @since 2012/10/14
 * @author Masatoshi Tsuge
 */
class WorldBoundNameEntry : public GgafLib::WorldBoundActor {

public:
    /**
     * �R���X�g���N�^
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

