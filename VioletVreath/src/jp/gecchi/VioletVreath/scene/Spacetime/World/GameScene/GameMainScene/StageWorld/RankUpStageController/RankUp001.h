#ifndef RANKUP001_H_
#define RANKUP001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"

namespace VioletVreath {

class RankUp001 : public RankUpStage {

public:
    RankUp001(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~RankUp001();
};

}
#endif /*RANKUP001_H_*/
