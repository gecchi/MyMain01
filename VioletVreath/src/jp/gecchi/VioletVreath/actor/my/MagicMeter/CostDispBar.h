#ifndef COSTDISPBAR_H_
#define COSTDISPBAR_H_
namespace VioletVreath {

class CostDispBar : public GraphBar {

public:
    /** 内容量 */
    GraphBar* pSourceBar_;
    GgafLib::AmountGraph* pCostValue_;
    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    CostDispBar(const char* prm_name, GraphBar* prm_pTargetBar, GgafLib::AmountGraph* prm_pCostDisp);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void addVal(double prm_val);


    virtual ~CostDispBar();
};

}
#endif /*ENERGYBAR_H_*/

