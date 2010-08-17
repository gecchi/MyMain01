#ifndef GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
#define GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * 固定時間（フレーム）スプライン曲線移動。 .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedFrameSplineProgram : public GgafDx9SplineProgram {

public:
    /** [r]１区間の使用可能フレーム */
    frame _SPframe_segment;
    /** [r]次の補完点までの距離のテーブル */
    int* _paDistace_to;
    /** [r]次の補完点到達に必要な移動速度のテーブル */
    velo* _paSPMvVeloTo;
    /** [rw]方向転換に許されるRzRyの軸転速度 */
    angvelo _angveloRzRyMv;
    /** [r]目標地点に到着までに設定されたフレーム数 */
    frame _spent_frame;
    /**
     * [r]オプション
     * 0:絶対座標移動。
     * 1:始点を現座標とし、スプライン座標群は相対移動で計算。
     * 2:始点を現座標とし、さらに現在の向き（_pMover の _angRzMv, _angRyMv)でスプライン座標群をワールド変換。
     */
    int _option;

    //計算用定数
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     * コンストラクタ
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9GeometricActor* prm_pActor);


    /**
     * コンストラクタ.
     * 固定時間移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * 引数から内部でGgafDx9Spline3Dを生成しスプライン曲線補完点を計算します。
     * GgafDx9Spline3Dオブジェクトの解放も内部で行われます。
     * @param prm_pActor 対象のアクター
     * @param prm_paaCriteriaPoint 基点配列
     * @param prm_point_num  基点配列の要素数
     * @param prm_accuracy  1基点の精度（荒い 1.0 ～ 0.0 細かい)、
     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
     *                      1.0を指定した場合、基点から次基点まで何も無い（直線で結ぶイメージ）。
     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
     *                      0.1 とすると基点と基点の間に補完点は9つ入る（なめらかなカーブになる）。
     * @param prm_spent_frame 始点～終点へ移動するのに費やすフレーム数
     * @param prm_angveloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9GeometricActor* prm_pActor,
                                   double prm_paaCriteriaPoint[][3],
                                   int prm_point_num,
                                   double prm_accuracy,
                                   frame prm_spent_frame,
                                   angvelo prm_angveloRzRyMv);
    /**
     * コンストラクタ.
     * 固定時間移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * 引数のGgafDx9Spline3Dを利用します。GgafDx9Spline3Dの解放は、呼び出し元で行ってください。
     * たくさんのオブジェクトに同じGgafDx9Spline3Dの動きをさせる場合は、
     * こちらのコンストラクタで生成すべきです。
     * @param prm_pActor 対象のアクター
     * @param prm_sp スプライン曲線の補完点生成、保持クラスのインスタンス
     * @param prm_spent_frame 始点～終点へ移動するのに許されるフレーム数
     * @param prm_angveloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     * @return
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9GeometricActor* prm_pActor,
                                   GgafDx9Spline3D* prm_sp,
                                   frame prm_spent_frame,
                                   angvelo prm_angveloRzRyMv);

    /**
     * 初期化関数 .
     * コンストラクタが利用。
     */
    void init();

    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void begin(int prm_option = 0) override;

    /**
     * 移動実行メソッド .
     * 移動のために毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave() override;

    virtual ~GgafDx9FixedFrameSplineProgram();
};

}
#endif /*GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_*/
