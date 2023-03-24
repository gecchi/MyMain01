#ifndef GGAF_LIB_HOMINGLASERCHIP_H_
#define GGAF_LIB_HOMINGLASERCHIP_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * ホーミングレーザー用ポリラインのチップ .
 * ホーミングレーザーなどと表現しているが、正確には <BR>
 * ・発射座標位置固定（発射元座標が通常移動不可）<BR>
 * ・移動方向、速度は先頭チップがのみが決め、残りチップは単に追従する<BR>
 * と言うべきか、レイフォースのロックオンレーザーと言うべきか、そんな感じ。<BR>
 * 先頭のチップの動きを processBehaviorHeadChip() に実装して下さい。VecVehicle で移動します。<BR>
 * dispatch() したら、座標と VecVehicle（向き速度）を設定して下さい。<BR>
 * 先頭のチップの場合のみ、座標と VecVehicle（向き速度）の設定が適用され、
 * それ以降のチップは一つ前方のチップの座標を強制トレースします。<BR>
 * @version 1.00
 * @since 2009/11/04
 * @author Masatoshi Tsuge
 */
class HomingLaserChip : public LaserChip {
    friend class LaserChipDepository;

public:
    /** 先導チップ（本当の先頭チップ）フラグ */
    bool _is_leader; //本当の先頭チップとは、レーザー移動中にちぎれて発生するにわか先頭チップでは無いという意味。
    int _begining_x;
    int _begining_y;
    int _begining_z;
    angle _begining_rx;
    angle _begining_ry;
    angle _begining_rz;
    angle _begining_rz_mv;
    angle _begining_ry_mv;
    velo _begining_velo_mv;
    int _prev_x;
    int _prev_y;
    int _prev_z;
    angle _prev_rx;
    angle _prev_ry;
    angle _prev_rz;
    angle _prev_rz_mv;
    angle _prev_ry_mv;
    velo _prev_velo_mv;
    /** [r]発射開始座標固定か否か(true:固定、呼び元の座標等を上書きして、最初の[0]の座標に強制上書き/false:非固定。スクロールシーン配下等の場合は false が良い */
    bool _is_fix_begin_pos;

public:
    HomingLaserChip(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    /**
     * ホーミングレーザーの先頭チップの動きを実装する .
     * 本当の先頭チップの場合はもちろんコールバックされるが、
     * にわか先頭チップ（ちぎれて急に先頭になったチップ）の場合もコールバックされます。
     */
    virtual void processBehaviorHeadChip() = 0;

    /**
     * レーザーチップ出現時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onActive() メソッドも呼び出してください。
     */
    virtual void onActive() override;

    /**
     * レーザーチップ消失時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onInactive() メソッドも呼び出してください。
     */
    virtual void onInactive() override;


    virtual ~HomingLaserChip();

};

}
#endif /*GGAF_LIB_HOMINGLASERCHIP_H_*/

