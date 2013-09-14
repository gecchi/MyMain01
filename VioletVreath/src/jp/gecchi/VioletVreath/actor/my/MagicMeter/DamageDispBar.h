#ifndef DAMAGEDISPBARH_
#define DAMAGEDISPBARH_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace VioletVreath {

class DamageDispBar : public GgafLib::GraphBarActor {

public:
    /** ���e�� */
    GgafLib::GraphBarActor* pSourceBar_;
    frame damege_disp_timer_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
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

