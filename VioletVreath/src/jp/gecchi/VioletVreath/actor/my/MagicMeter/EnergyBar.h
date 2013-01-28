#ifndef ENERGYBAR_H_
#define ENERGYBAR_H_
namespace VioletVreath {

class EnergyBar : public GraphBar {

public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    EnergyBar(const char* prm_name, GgafLib::AmountGraph* prm_pAmount);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void addVal(double prm_val);


    virtual ~EnergyBar();
};

}
#endif /*ENERGYBAR_H_*/

