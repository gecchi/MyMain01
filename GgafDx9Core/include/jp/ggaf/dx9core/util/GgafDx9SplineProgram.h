#ifndef GGAFDX9SPLINEPROGRAM_H_
#define GGAFDX9SPLINEPROGRAM_H_
namespace GgafDx9Core {

class GgafDx9SplineProgram : public GgafCore::GgafObject {

public:

    GgafDx9Spline3D* _sp;
    DWORD _SPframe_segment;
    DWORD _SPframe;
    int* _paSPDistaceTo;
    velo* _paSPMoveVelocityTo;
    boolean _is_executing;
    GgafDx9GeometricActor* _pActor_executing;
    angvelo _angRotMove;

    /** 相対移動フラグ */
    boolean _is_relative;
    int _X_relative;
    int _Y_relative;
    int _Z_relative;

    GgafDx9SplineProgram();


    /**
     *
     * @param prm_paaCriteriaPoint 基点配列
     * @param prm_point_num  基点配列の要素数
     * @param prm_accuracy  1基点の精度（荒い 1.0 ～ 0.0 細かい)、
     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
     *                      1の場合基点から次基点まで何も無い（直線）。
     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
     *                      0.1 とすると基点と基点の間に補完点は9つ。
     * @param prm_paaCriteriaPoint 始点から終点へ移動するのに費やすフレーム数
     * @param prm_angRotMove 補完点への方向ベクトルにターゲンティングする際の、旋回可能な1フレームあたりの回転移動角
     */
    GgafDx9SplineProgram(double prm_paaCriteriaPoint[][3],
                         int prm_point_num,
                         double prm_accuracy,
                         DWORD prm_spent_frame,
                         angvelo prm_angRotMove);


    void beginSplineCurveAbsolute(GgafDx9GeometricActor* _pActor);
    void beginSplineCurveRelative(GgafDx9GeometricActor* _pActor);
    void behave();


    /**
     *
     * @param prm_paaCriteriaPoint 基点配列
     * @param prm_point_num  基点配列の要素数
     * @param prm_accuracy  1基点の精度（荒い 1.0 ～ 0.0 細かい)、
     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
     *                      1の場合基点から次基点まで何も無い（直線）。
     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
     *                      0.1 とすると基点と基点の間に補完点は9つ。
     * @param prm_paaCriteriaPoint 基点から基点へ移動するのに費やすフレーム数
     */

    virtual ~GgafDx9SplineProgram();
};

}
#endif /*GGAFDX9SPLINEPROGRAM_H_*/
