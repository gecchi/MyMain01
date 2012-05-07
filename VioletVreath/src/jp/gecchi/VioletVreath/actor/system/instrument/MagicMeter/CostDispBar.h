#ifndef COSTDISPBAR_H_
#define COSTDISPBAR_H_
namespace VioletVreath {

class CostDispBar : public GgafLib::DefaultBoardActor {

public:
    /** 内容量 */
    EnergyBar* pEnergyBar_;
    GgafLib::AmountGraph* pCostDisp_;
    float _fSize_BoardModelWidthPx;

    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    CostDispBar(const char* prm_name, EnergyBar* prm_pEnergyBar, GgafLib::AmountGraph* prm_pCostDisp);

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

