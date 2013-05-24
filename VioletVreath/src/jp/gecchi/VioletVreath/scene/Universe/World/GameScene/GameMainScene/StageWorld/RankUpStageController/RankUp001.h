#ifndef RANKUP001_H_
#define RANKUP001_H_
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"

namespace VioletVreath {

class RankUp001 : public RankUpStage {

public:
    RankUp001(const char* prm_name);
    /**
     * ��������
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~RankUp001();
};

}
#endif /*RANKUP001_H_*/
