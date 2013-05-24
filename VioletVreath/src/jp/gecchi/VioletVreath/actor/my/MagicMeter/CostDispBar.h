#ifndef COSTDISPBAR_H_
#define COSTDISPBAR_H_
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"

namespace VioletVreath {

class CostDispBar : public GraphBar {

public:
    /** ���e�� */
    GraphBar* pSourceBar_;
    GgafLib::AmountGraph* pCostValue_;

public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config�ς݂� AmountGraph�I�u�W�F�N�g�̎Q��
     */
    CostDispBar(const char* prm_name, GraphBar* prm_pTargetBar, GgafLib::AmountGraph* prm_pCostDisp);

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

