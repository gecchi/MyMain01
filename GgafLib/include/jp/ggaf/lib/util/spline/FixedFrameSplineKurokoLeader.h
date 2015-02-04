#ifndef GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_
#define GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * 固定時間（フレーム）スプライン曲線移動の先導者。 .
 * 開始点～終了点まで、決められた時間で移動します。<BR>
 * 中間の補完点～次の補完点までを、均等に割った時間で移動します。<BR>
 * 補完点の密度が薄いところは移動速度増。<BR>
 * 補完点の密度が濃いところは移動速度減。<BR>
 * そのように動作するよう、黒衣(GgafDxCore::GgafDxKuroko)に指示を出して移動を実現します。<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineKurokoLeader : public SplineKurokoLeader {

public:
    /** [r]スプライン情報セット(splファイルの情報に相当) */
    FixedFrameSplineManufacture* _pFixedFrameSplManuf;
    /** _leading_framesに加算される補正フレーム */
    frame _hosei_frames;
    /** [r]現在向かっている最中の補完点(基準点も含む)の数 */
    int _point_index;
    /** 前回の_point_index */
    int _prev_point_index;
    /** start()からの経過フレーム数 */
    frame _leading_frames;
public:
    /**
     *
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKuroko
     */
    FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture,
                                 GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    FixedFrameSplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                 SplineLine* prm_pSpl,
                                 frame prm_spent_frame,
                                 angvelo prm_angveloRzRyMv);

    virtual void restart() override;

    /**
     * 移動実行メソッド .
     * start() を行った同一フレームに behave() 実行を避けるといったことは不要。<BR>
     * start() を行った最初の behave() は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    virtual void behave() override;


    virtual ~FixedFrameSplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_*/
