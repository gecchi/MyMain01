#ifndef COSTDISPBAR_H_
#define COSTDISPBAR_H_
namespace VioletVreath {

class CostDispBar : public GgafLib::DefaultBoardActor {

public:
    /** ���e�� */
    EnergyBar* pEnergyBar_;
    GgafLib::AmountGraph* pCostDisp_;
    float _fSize_BoardModelWidthPx;

    /**
     *
     * @param prm_name
     * @param prm_pAmount config�ς݂� AmountGraph�I�u�W�F�N�g�̎Q��
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

