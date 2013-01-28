#ifndef VREATHBAR_H_
#define VREATHBAR_H_
namespace VioletVreath {

/**
 * VreathBar .
 * @version 1.00
 * @since 2012/05/11
 * @author Masatoshi Tsuge
 */
class VreathBar :  public GraphBar {

public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    VreathBar(const char* prm_name, GgafLib::AmountGraph* prm_pAmount);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void addVal(double prm_val);


    virtual ~VreathBar();
};

}
#endif /*VREATHBAR_H_*/

