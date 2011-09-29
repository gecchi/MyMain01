#ifndef FIXEDFRAMESPLINESEQUENCE_H_
#define FIXEDFRAMESPLINESEQUENCE_H_
namespace GgafLib {

/**
 * 固定時間（フレーム）スプライン曲線移動。 .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineSequence : public SplineSequence {

public:

    FixedFrameSplineManufacture* _pFixedFrameSplManuf;

    //計算用定数
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     *
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKurokoA
     */
    FixedFrameSplineSequence(SplineManufacture* prm_pManufacture,
                             GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    FixedFrameSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                             SplineLine* prmpSpl,
                             frame prm_spent_frame,
                             ang_velo prm_ang_veloRzRyMv);
    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void exec(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * 移動実行メソッド .
     * 移動のために毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave() override;

    virtual ~FixedFrameSplineSequence();
};

}
#endif /*FIXEDFRAMESPLINESEQUENCE_H_*/
