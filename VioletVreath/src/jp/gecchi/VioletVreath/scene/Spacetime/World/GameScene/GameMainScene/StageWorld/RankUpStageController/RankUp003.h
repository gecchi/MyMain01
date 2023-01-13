#ifndef RANKUP003_H_
#define RANKUP003_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"




namespace VioletVreath {

class RankUp003 : public RankUpStage {

public:
    RankUp003(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~RankUp003();
};

}
#endif /*RANKUP003_H_*/
