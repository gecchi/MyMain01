#ifndef GGAF_LIB_FIXEDVELOCITYSPLINERIKISHALEADER_H_
#define GGAF_LIB_FIXEDVELOCITYSPLINERIKISHALEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

namespace GgafLib {

/**
 * 等速移動スプライン曲線移動の先導者。 .
 * 開始点～終了点まで、同じスピードで移動します。<BR>
 * 次の補完点までの距離を測り、現在の移動速度から、測った距離を減算し「残り移動距離」を求める。
 * 残り移動距離が0になれば、次の補完点に向きを変えながらまた距離を測る・・・を繰り返します。<BR>
 * 補完点の密度が薄いところでも濃いところでも移動速度に影響はありません。<BR>
 * そのように動作するよう、力車(GgafDx::Rikisha)に指示を出して移動を実現します。<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineRikishaLeader : public SplineLeader {

public:
    GgafDx::Rikisha* _pRikisha_target;
    /** [r]スプライン情報セット(splファイルの情報に相当)  */
    FixedVelocitySplineManufacture* _pFixedVeloSplManuf;
    /** [r]現在向かっている最中の補完点(基準点も含む)の数 */
    int _point_index;
    /** [r]基準速度で移動した場合のスプライン移動時の経過フレーム数 */
    float _leadning_float_frames;
    /** [r]次の変わり目となる補間点(基準点も含む)に到達する_leadning_fFrames */
    float _float_frame_of_next;
public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pRikisha 対象のアクターの力車
     */
    FixedVelocitySplineRikishaLeader(SplineManufacture* prm_pManufacture, GgafDx::Rikisha* prm_pRikisha_target);

    virtual void restart() override;

    /**
     * 毎フレームの振る舞いメソッド .
     * start() を行った同一フレームに behave() 実行を避けるといったことは不要。<BR>
     * start() を行った最初のbehave()は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    virtual void behave() override;


    virtual ~FixedVelocitySplineRikishaLeader();
};

}
#endif /*GGAF_LIB_FIXEDVELOCITYSPLINERIKISHALEADER_H_*/
