#ifndef GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#define GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * 等速移動スプライン曲線移動の先導者。 .
 * 開始点～終了点まで、同じスピードで移動します。<BR>
 * 次の補完点までの距離を測り、現在の移動速度から、測った距離を減算し「残り移動距離」を求める。
 * 残り移動距離が0になれば、次の補完点に向きを変えながらまた距離を測る・・・を繰り返します。<BR>
 * 補完点の密度が薄いところでも濃いところでも移動速度に影響はありません。<BR>
 * そのように動作するよう、黒衣(GgafDxCore::GgafDxKuroko)に指示を出して移動を実現します。<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineKurokoLeader : public SplineKurokoLeader {


public:
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
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKuroko 対象のアクターの黒衣
     */
    FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* prm_pKuroko);

    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pKuroko 対象のアクターの黒衣
     * @param prm_sp 計算済みスプラインオブジェクト
     * @param prm_angveloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     */
    FixedVelocitySplineKurokoLeader(GgafDxCore::GgafDxKuroko* prm_pKuroko,
                                    SplineLine* prm_sp,
                                    angvelo prm_angveloRzRyMv);

    virtual void restart() override;

    /**
     * 毎フレームの振る舞いメソッド .
     * start() を行った同一フレームに behave() 実行を避けるといったことは不要。<BR>
     * start() を行った最初のbehave()は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    virtual void behave() override;


    virtual ~FixedVelocitySplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/
