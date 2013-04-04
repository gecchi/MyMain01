#ifndef FIXEDVELOCITYSPLINEKUROKOSTEPPER_H_
#define FIXEDVELOCITYSPLINEKUROKOSTEPPER_H_
namespace GgafLib {

/**
 * 等速移動スプライン曲線移動。 .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineKurokoStepper : public SplineKurokoStepper {

public:
    FixedVelocitySplineManufacture* _pFixedVeloSplManuf;

    /** [r]基準速度で移動した場合のスプライン移動時の経過フレーム数 */
    float _exec_fFrames;
    /** [r]次の変わり目となる補間点(基準点も含む)に到達する_exec_fFrames */
    float _fFrame_of_next;
    //計算用
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKurokoA 対象のアクターの黒衣A
     */
    FixedVelocitySplineKurokoStepper(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pKurokoA 対象のアクターの黒衣A
     * @param prm_sp 計算済みスプラインオブジェクト
     * @param prm_angveloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     * @return
     */
    FixedVelocitySplineKurokoStepper(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                                     SplineLine* prm_sp,
                                     angvelo prm_angveloRzRyMv);


    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void start(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * 毎フレームの振る舞いメソッド .
     * start() を行った同一フレームに behave() 実行を避けるといったことは不要。<BR>
     * start() を行った最初のbehave()は、『現在の座標→ポイント[0]』への処理となります。<BR>
     */
    void behave() override;


    virtual ~FixedVelocitySplineKurokoStepper();
};

}
#endif /*FIXEDVELOCITYSPLINEKUROKOSTEPPER_H_*/
