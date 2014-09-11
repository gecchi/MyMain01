#ifndef GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#define GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * 等速移動スプライン曲線移動の先導者。 .
 * 開始点〜終了点まで、同じスピードで移動します。<BR>
 * 次の補完点までの距離を測り、現在の移動速度から、測った距離を減算し「残り移動距離」を求める。
 * 残り移動距離が0になれば、次の補完点に向きを変えながらまた距離を測る・・・を繰り返します。<BR>
 * 補完点の密度が薄いところでも濃いところでも移動速度に影響はありません。<BR>
 * そのように動作するよう、黒衣(GgafDxCore::GgafDxKuroko)に指示を出して移動を実現します。<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineKurokoLeader : public SplineKurokoLeader {
private:
    void restart();

public:
    /** [r]スプライン情報セット(splファイルの情報に相当)  */
    FixedVelocitySplineManufacture* _pFixedVeloSplManuf;

    /** [r]基準速度で移動した場合のスプライン移動時の経過フレーム数 */
    float _leadning_fFrames;
    /** [r]次の変わり目となる補間点(基準点も含む)に到達する_leadning_fFrames */
    float _fFrame_of_next;
    //計算用
    float _sinRzMv_begin;
    float _cosRzMv_begin;
    float _sinRyMv_begin;
    float _cosRyMv_begin;
    angle _ang_rz_mv_begin;
    angle _ang_ry_mv_begin;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKuroko 対象のアクターの黒衣
     */
    FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pKuroko 対象のアクターの黒衣
     * @param prm_sp 計算済みスプラインオブジェクト
     * @param prm_angveloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     */
    FixedVelocitySplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                    SplineLine* prm_sp,
                                    angvelo prm_angveloRzRyMv);


    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション ABSOLUTE_COORD:絶対座標移動
     *                              RELATIVE_COORD:始点をActorの現座標とみなし、そこからの相対座標移動
     *                              RELATIVE_DIRECTION:始点をActorの現座標とみなし、
     *                                                 アクターの現在向き（_pKuroko の _ang_rz_mv, _ang_ry_mv)でスプライン座標群をワールド変換。
     * @param prm_max_loop 繰り返し回数。0以下で無限ループ
     */
    void start(SplinTraceOption prm_option, int prm_max_loop = 1) override;



    /**
     * 毎フレームの振る舞いメソッド .
     * start() を行った同一フレームに behave() 実行を避けるといったことは不要。<BR>
     * start() を行った最初のbehave()は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    void behave() override;

    /**
     * 補完点の座標を取得する .
     * @param prm_point_index 補完点のインデックス (0〜)
     * @param out_x 対応するX座標(戻り値)
     * @param out_y 対応するY座標(戻り値)
     * @param out_z 対応するZ座標(戻り値)
     */
    void getPointCoord(int prm_point_index, coord& out_x, coord& out_y, coord& out_z) override;

    virtual ~FixedVelocitySplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/
