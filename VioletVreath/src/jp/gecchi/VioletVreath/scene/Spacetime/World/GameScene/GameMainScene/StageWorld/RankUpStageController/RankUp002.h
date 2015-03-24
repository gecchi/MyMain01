#ifndef RANKUP002_H_
#define RANKUP002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"




namespace VioletVreath {

class RankUp002 : public RankUpStage {

public:
    RankUp002(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~RankUp002();
};

}
#endif /*RANKUP002_H_*/
