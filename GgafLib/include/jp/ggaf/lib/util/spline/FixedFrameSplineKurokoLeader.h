#ifndef FIXEDFRAMESPLINEKUROKOLEADER_H_
#define FIXEDFRAMESPLINEKUROKOLEADER_H_
namespace GgafLib {

/**
 * 固定時間（フレーム）スプライン曲線移動の先導者。 .
 * 開始点～終了点まで、決められた時間で移動します。<BR>
 * 中間の補完点～次の補完点までを、均等に割った時間で移動します。<BR>
 * 補完点の密度が薄いところは移動速度増。<BR>
 * 補完点の密度が濃いところは移動速度減。<BR>
 * そのように動作するよう、黒衣A(GgafDxCore::GgafDxKurokoA)に指示を出して移動を実現します。<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineKurokoLeader : public SplineKurokoLeader {

public:
    /** [r]スプライン情報セット(splファイルの情報に相当) */
    FixedFrameSplineManufacture* _pFixedFrameSplManuf;

    //計算用定数
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;
    frame _hosei_frames;
    /** 前回の_point_index */
    int _prev_point_index;

public:
    /**
     *
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKurokoA
     */
    FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture,
                                 GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    FixedFrameSplineKurokoLeader(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                                 SplineLine* prmpSpl,
                                 frame prm_spent_frame,
                                 angvelo prm_angveloRzRyMv);
    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void start(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * 移動実行メソッド .
     * start() を行った同一フレームに behave() 実行を避けるといったことは不要。<BR>
     * start() を行った最初の behave() は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    void behave() override;

    /**
     * 補完点の座標を取得する .
     * @param prm_point_index 補完点のインデックス (0～)
     * @param out_X 対応するX座標(戻り値)
     * @param out_Y 対応するY座標(戻り値)
     * @param out_Z 対応するZ座標(戻り値)
     */
    void getPointCoord(int prm_point_index, coord& out_X, coord& out_Y, coord& out_Z) override;

    virtual ~FixedFrameSplineKurokoLeader();
};

}
#endif /*FIXEDFRAMESPLINEKUROKOLEADER_H_*/
