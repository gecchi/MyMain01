#ifndef STEPPEDCOORDSPLINESEQUENCE_H_
#define STEPPEDCOORDSPLINESEQUENCE_H_
namespace GgafLib {

/**
 * 等速移動スプライン曲線移動。 .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineSequence : public SplineSequence {

public:
    SteppedCoordSplineManufacture* _pFixedVeloSplManuf;

    /** [r]基準速度で移動した場合のスプライン移動時の経過フレーム数 */
    float _exec_fFrames;
    /** [r]次の変わり目となる補間点(基準点も含む)に到達する_exec_fFrames */
    float _fFrame_of_next;
    /** [r]補完点(基準点も含む)の数 */
    int _point_index;


    //計算用
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     * コンストラクタ .
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKurokoA 対象のアクターの黒子A
     */
    SteppedCoordSplineSequence(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pKurokoA 対象のアクターの黒子A
     * @param prm_sp 計算済みスプラインオブジェクト
     * @param prm_angveloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     * @return
     */
    SteppedCoordSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                               SplineLine* prm_sp,
                               angvelo prm_angveloRzRyMv);


    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void exec(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave() override;


    virtual ~SteppedCoordSplineSequence();
};

}
#endif /*FIXEDVELOCITYSPLINESEQUENCE_H_*/
