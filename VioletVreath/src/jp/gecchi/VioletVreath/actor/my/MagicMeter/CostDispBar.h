#ifndef COSTDISPBAR_H_
#define COSTDISPBAR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/FramedHorizontalBarActor.h"

namespace VioletVreath {

class CostDispBar : public GgafLib::FramedHorizontalBarActor {

public:
    /** ���e�� */
    GgafLib::FramedHorizontalBarActor* pSourceBar_;
public:

    /**
     *
     * @param prm_name
     * @param prm_pTargetSourceBar �\�����o�[
     */
    CostDispBar(const char* prm_name, GgafLib::FramedHorizontalBarActor* prm_pTargetSourceBar);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processPreDraw() override;

    void onInactive() override;

    virtual ~CostDispBar();
};

}
#endif /*ENERGYBAR_H_*/

