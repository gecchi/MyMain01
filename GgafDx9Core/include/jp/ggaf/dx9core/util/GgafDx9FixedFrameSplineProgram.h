#ifndef GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
#define GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * スプライン曲線、なめらかなフレーム指定移動のための情報セット
 */
class GgafDx9FixedFrameSplineProgram : public GgafDx9SplineProgram {

public:

    DWORD _SPframe_segment;
    int* _paDistace_to;
    velo* _paSPMoveVelocityTo;
    angvelo _angRotMove;

    /** オプション 0:絶対座標移動、1:始点をActorの現座標とみなし、そこからの相対座標移動 */
    int _option;
    int _X_relative;
    int _Y_relative;
    int _Z_relative;

    GgafDx9FixedFrameSplineProgram();


    /**
     *
     * @param prm_paaCriteriaPoint 基点配列
     * @param prm_point_num  基点配列の要素数
     * @param prm_accuracy  1基点の精度（荒い 1.0 ～ 0.0 細かい)、
     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
     *                      1の場合基点から次基点まで何も無い（直線）。
     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
     *                      0.1 とすると基点と基点の間に補完点は9つ。
     * @param prm_paaCriteriaPoint 始点～終点へ移動するのに許されるフレーム数
     * @param prm_angRotMove 旋回可能な1フレームあたりの回転角 (1000 が 1度)
     */
    GgafDx9FixedFrameSplineProgram(double prm_paaCriteriaPoint[][3],
                                   int prm_point_num,
                                   double prm_accuracy,
                                   DWORD prm_spent_frame,
                                   angvelo prm_angRotMove);

    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_pActor 対象のアクター
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void begin(GgafDx9GeometricActor* _pActor, int prm_option = 0);

    /**
     * 毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave();




    virtual ~GgafDx9FixedFrameSplineProgram();
};

}
#endif /*GGAFDX9FIXEDFRAMESPLINEPROGRAM_H_*/
