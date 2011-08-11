#ifndef FIXEDFRAMESPLINESEQUENCE_H_
#define FIXEDFRAMESPLINESEQUENCE_H_
namespace GgafDx9LibStg {

/**
 * 固定時間（フレーム）スプライン曲線移動。 .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineSequence : public SplineSequence {

public:

    FixedFrameSplineManufacture* _pFixedFrameSplineManufacture;

    //計算用定数
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    FixedFrameSplineSequence(SplineManufacture* prm_pManufacture,
                             GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA);

    FixedFrameSplineSequence(GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA,
                             Spline3D* prmpSpl,
                             frame prm_spent_frame,
                             ang_velo prm_ang_veloRzRyMv);
    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void exec(int prm_option = 0) override;

    /**
     * 移動実行メソッド .
     * 移動のために毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave() override;

    virtual ~FixedFrameSplineSequence();
};

}
#endif /*FIXEDFRAMESPLINESEQUENCE_H_*/
