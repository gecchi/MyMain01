#ifndef DAMAGEDISPBARH_
#define DAMAGEDISPBARH_
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"

namespace VioletVreath {

#define DISP_DELAY 180

class DamageDispBar : public GraphBar {

public:
    /** 内容量 */
    GraphBar* pSourceBar_;

    int aInt_my_ship_stamina_history_[DISP_DELAY];
    int aInt_my_ship_damage_history_[DISP_DELAY];
    int p_;

public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    DamageDispBar(const char* prm_name, GraphBar* prm_pTargetBar, GgafLib::AmountGraph* prm_pDamageDisp);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void addDamageVal(int prm_val);


    virtual ~DamageDispBar();
};

}
#endif /*DAMAGEDISPBARH_*/

