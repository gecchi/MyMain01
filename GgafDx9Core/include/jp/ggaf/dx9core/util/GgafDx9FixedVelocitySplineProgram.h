#ifndef GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
#define GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * スプライン曲線、なめらかな等速移動のための情報セット
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedVelocitySplineProgram : public GgafDx9SplineProgram {

public:

    int* _paDistace_to;
    float* _paFrame_need_at;
    velo _veloMoveUnit; //単位速度
    angvelo _angFaceMove;
    float _fFrame_executing;
    float _fFrame_next_point;
    //float _fSPPointFrame;
    int _point_index;

    /** オプション 0:絶対座標移動、1:始点をActorの現座標とみなし、そこからの相対座標移動 */
    int _option;

    int _X_relative;
    int _Y_relative;
    int _Z_relative;

    GgafDx9FixedVelocitySplineProgram();


    /**
     * コンストラクタ
     * 移動のための必要な情報を計算し、オブジェクトに溜め込みます。
     * @param prm_paaCriteriaPoint 基点配列
     * @param prm_point_num  基点配列の要素数
     * @param prm_accuracy  1基点の精度（荒い 1.0 ～ 0.0 細かい)、
     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
     *                      1の場合基点から次基点まで何も無い（直線）。
     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
     *                      0.1 とすると基点と基点の間に補完点は9つ。
     * @param prm_veloMove 移動速度
     * @param prm_angFaceMove 旋回可能な1フレームあたりの回転角 (1000 が 1度)
     */
    GgafDx9FixedVelocitySplineProgram(double prm_paaCriteriaPoint[][3],
                                      int prm_point_num,
                                      double prm_accuracy,
                                      angvelo prm_angFaceMove);

    GgafDx9FixedVelocitySplineProgram(GgafDx9Spline3D* prm_sp,
                                      angvelo prm_angFaceMove);


    void init();

    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_pActor 対象のアクター
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void begin(GgafDx9GeometricActor* prm_pActor, int prm_option = 0);

    /**
     * 毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave();


    virtual ~GgafDx9FixedVelocitySplineProgram();
};

}
#endif /*GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_*/
