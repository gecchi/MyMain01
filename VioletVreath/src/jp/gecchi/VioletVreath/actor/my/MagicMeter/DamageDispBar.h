#ifndef DAMAGEDISPBARH_
#define DAMAGEDISPBARH_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace VioletVreath {

class DamageDispBar : public GgafLib::GraphBarActor {

public:
    /** 内容量 */
    GgafLib::GraphBarActor* pSourceBar_;
    frame damege_disp_timer_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config済みの PxQuantityオブジェクトの参照
     */
    DamageDispBar(const char* prm_name, GgafLib::GraphBarActor* prm_pTargetSourceBar);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void addDamage(int prm_val);


    virtual ~DamageDispBar();
};

}
#endif /*DAMAGEDISPBARH_*/

