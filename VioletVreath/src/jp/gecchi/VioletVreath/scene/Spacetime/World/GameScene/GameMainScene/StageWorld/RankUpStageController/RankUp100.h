#ifndef RANKUP100_H_
#define RANKUP100_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"

namespace VioletVreath {

class RankUp100 : public RankUpStage {

public:
    RankUp100(const char* prm_name);
    /**
     * ��������
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~RankUp100();
};

}
#endif /*RANKUP100_H_*/
