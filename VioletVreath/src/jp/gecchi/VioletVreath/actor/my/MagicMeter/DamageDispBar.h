#ifndef DAMAGEDISPBARH_
#define DAMAGEDISPBARH_
#include "jp/ggaf/lib/actor/FramedHorizontalBarActor.h"

namespace VioletVreath {

class DamageDispBar : public GgafLib::FramedHorizontalBarActor {

public:
    /** ���e�� */
    GgafLib::FramedHorizontalBarActor* pSourceBar_;
    frame damege_disp_timer_;
    bool is_damege_disp_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQty config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    DamageDispBar(const char* prm_name, GgafLib::FramedHorizontalBarActor* prm_pTargetSourceBar);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    /**
     * �Ԃ̂΁[�Ń_���[�W�\��
     * @param prm_before_val �_���[�W�O�̐�
     * @param prm_after_val �_���[�W��̐�
     */
    void dispDamage(int prm_before_val, int prm_after_val);


    virtual ~DamageDispBar();
};

}
#endif /*DAMAGEDISPBARH_*/

