#ifndef COSTDISPBAR_H_
#define COSTDISPBAR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace VioletVreath {

class CostDispBar : public GgafLib::GraphBarActor {

public:
    /** 内容量 */
    GgafLib::GraphBarActor* pSourceBar_;
public:

    /**
     *
     * @param prm_name
     * @param prm_pTargetSourceBar 表示元バー
     */
    CostDispBar(const char* prm_name, GgafLib::GraphBarActor* prm_pTargetSourceBar);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~CostDispBar();
};

}
#endif /*ENERGYBAR_H_*/

