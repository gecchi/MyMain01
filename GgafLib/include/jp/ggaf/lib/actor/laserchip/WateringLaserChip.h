#ifndef GGAF_LIB_WATERINGLASERCHIP_H_
#define GGAF_LIB_WATERINGLASERCHIP_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * 水撒きレーザー用ポリラインのチップ .
 * 水撒きレーザーなどと表現しているが、正確には<BR>
 * ・発射座標任意（発射元座標が移動可能）<BR>
 * ・各チップの移動方向、速度共に固定<BR>
 * ・しかし、隣接するチップとチップが手を取り合い、角がとれて滑らかになる。チップ間に当たり判定が発生<BR>
 * というべきか、グラディウスＶのディレクションレーザー(TYPE2)と言うべきか、そんな感じ。<BR>
 * AxisVehicle で移動します。dispatch() したら、座標と AxisVehicle（各軸の移動速度）を設定して下さい。<BR>
 * @version 1.00
 * @since 2009/08/27
 * @author Masatoshi Tsuge
 */
class WateringLaserChip : public LaserChip {
    friend class LaserChipDepository;

public:
    WateringLaserChip(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * レーザーチップ出現時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onActive() メソッドも呼び出してください。
     */
    virtual void onActive() override;

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、座標計算後、最後に本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    virtual ~WateringLaserChip();

};

}
#endif /*GGAF_LIB_WATERINGLASERCHIP_H_*/

