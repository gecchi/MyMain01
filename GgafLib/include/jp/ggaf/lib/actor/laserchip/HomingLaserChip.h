#ifndef HOMINGLASERCHIP_H_
#define HOMINGLASERCHIP_H_
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * ホーミングレーザー用ポリラインのチップ .
 * ホーミングレーザーなどとと表現しているが、正確には <BR>
 * ・発射座標位置固定（発射元座標が通常移動不可）<BR>
 * ・移動方向、速度は先頭チップがのみが決め、残りチップは単に追従する<BR>
 * と言うべきか、レイフォースのロックオンレーザーと言うべきか、そんな感じ。<BR>
 * 先頭のチップの動きを processBehaviorHeadChip() に実装して下さい。KurokoA で移動します。<BR>
 * dispatch() したら、座標と KurokoA（向き速度）を設定して下さい。<BR>
 * 先頭のチップの場合のみ、座標と KurokoA（向き速度）の設定が適用され、
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
    int _begining_X;
    int _begining_Y;
    int _begining_Z;
    angle _begining_RX;
    angle _begining_RY;
    angle _begining_RZ;
    int _prev_X;
    int _prev_Y;
    int _prev_Z;
    angle _prev_RX;
    angle _prev_RY;
    angle _prev_RZ;
    /** [r]発射開始座標固定か否か(true:固定、呼び元のlocate等を上書きして、最初の[0]の座標に強制上書き/false:非固定。スクロールシーン配下等の場合は false が良い */
    bool _is_fix_begin_pos;

public:
    HomingLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

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
#endif /*HOMINGLASERCHIP_H_*/

