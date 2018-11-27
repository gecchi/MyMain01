#ifndef DAMAGEDISPBARH_
#define DAMAGEDISPBARH_
#include "jp/ggaf/lib/actor/FramedHorizontalBarActor.h"

namespace VioletVreath {

class DamageDispBar : public GgafLib::FramedHorizontalBarActor {

public:
    /** 内容量 */
    GgafLib::FramedHorizontalBarActor* pSourceBar_;
    frame damege_disp_timer_;
    bool is_damege_disp_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQty config済みの PxQuantityオブジェクトの参照
     */
    DamageDispBar(const char* prm_name, GgafLib::FramedHorizontalBarActor* prm_pTargetSourceBar);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    /**
     * 赤のばーでダメージ表示
     * @param prm_before_val ダメージ前の数
     * @param prm_after_val ダメージ後の数
     */
    void dispDamage(int prm_before_val, int prm_after_val);


    virtual ~DamageDispBar();
};

}
#endif /*DAMAGEDISPBARH_*/

