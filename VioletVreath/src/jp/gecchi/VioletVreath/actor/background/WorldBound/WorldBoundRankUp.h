#ifndef WORLDBOUNDRANKUP_H_
#define WORLDBOUNDRANKUP_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * �ʉ߃X�e�[�W�̐��E��� .
 * @version 1.00
 * @since 2011/10/05
 * @author Masatoshi Tsuge
 */
class WorldBoundRankUp : public GgafLib::WorldBoundActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    WorldBoundRankUp(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~WorldBoundRankUp();
};

}
#endif /*WORLDBOUNDRANKUP_H_*/

