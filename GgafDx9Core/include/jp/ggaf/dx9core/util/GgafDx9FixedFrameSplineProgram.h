#ifndef GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
#define GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * スプライン曲線、なめらかなフレーム指定移動のための情報セット
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedFrameSplineProgram : public GgafDx9SplineProgram {

public:
    /** １区間の使用可能フレーム */
    DWORD _SPframe_segment;
    /** 次の補完点までの距離のテーブル */
    int* _paDistace_to;
    /** 次の補完点到達に必要な移動速度のテーブル */
    velo* _paSPMoveVelocityTo;
    /** 方向転換に許されるRzRyの軸転速度 */
    angvelo _angFaceMove;
    /** 目標地点に到着までに設定されたフレーム数 */
    DWORD _spent_frame;

    /** オプション 0:絶対座標移動、1:始点をActorの現座標とみなし、そこからの相対座標移動 */
    int _option;
    int _X_relative;
    int _Y_relative;
    int _Z_relative;

    /**
     * コンストラクタ
     */
    GgafDx9FixedFrameSplineProgram();


    /**
     * コンストラクタ.
     * 引数から内部でGgafDx9Spline3Dを生成しスプライン曲線補完点を計算します。
     * GgafDx9Spline3Dオブジェクトの解放も内部で行われます。
     * @param prm_paaCriteriaPoint 基点配列
     * @param prm_point_num  基点配列の要素数
     * @param prm_accuracy  1基点の精度（荒い 1.0 ～ 0.0 細かい)、
     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
     *                      1の場合基点から次基点まで何も無い（直線）。
     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
     *                      0.1 とすると基点と基点の間に補完点は9つ。
     * @param prm_paaCriteriaPoint 始点～終点へ移動するのに許されるフレーム数
     * @param prm_angFaceMove 旋回可能な1フレームあたりの回転角 (1000 が 1度)
     */
    GgafDx9FixedFrameSplineProgram(double prm_paaCriteriaPoint[][3],
                                   int prm_point_num,
                                   double prm_accuracy,
                                   DWORD prm_spent_frame,
                                   angvelo prm_angFaceMove);
    /**
     * コンストラクタ.
     * 引数のGgafDx9Spline3Dを利用します。GgafDx9Spline3Dの解放は、呼び出し元で行ってください。
     * たくさんのオブジェクトに同じ動きをさせる場合は、こちらのコンストラクタで生成すべきです。
     * @param prm_sp スプライン曲線の補完点生成、保持クラスのインスタンス
     * @param prm_spent_frame 始点～終点へ移動するのに許されるフレーム数
     * @param prm_angFaceMove 旋回可能な1フレームあたりの回転角 (1000 が 1度)
     * @return
     */
    GgafDx9FixedFrameSplineProgram(GgafDx9Spline3D* prm_sp,
                                   DWORD prm_spent_frame,
                                   angvelo prm_angFaceMove);

    /**
     * 初期化関数 .
     * コンストラクタが利用。
     */
    void init();

    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_pActor 対象のアクター
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void begin(GgafDx9GeometricActor* _pActor, int prm_option = 0);

    /**
     * 移動実行メソッド .
     * 移動のために毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave();

    virtual ~GgafDx9FixedFrameSplineProgram();
};

}
#endif /*GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_*/
