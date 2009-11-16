#ifndef GGAFDX9SPLINEPROGRAM_H_
#define GGAFDX9SPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * スプライン曲線移動のための情報セット .
 * 補完点に移動するため、粒度が荒いとカクカクです。
 */
class GgafDx9SplineProgram : public GgafCore::GgafObject {

public:

    GgafDx9Spline3D* _sp;
    DWORD _SPframe;
    boolean _is_executing;
    GgafDx9GeometricActor* _pActor_target;
    bool _is_create_sp;

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
     */
    GgafDx9SplineProgram(double prm_paaCriteriaPoint[][3],
                         int prm_point_num,
                         double prm_accuracy);
    /**
     *
     * @param prm_sp
     * @return
     */
    GgafDx9SplineProgram(GgafDx9Spline3D* prm_sp);

    /**
     * スプライン曲線利用移動プログラム開始
     * @param prm_pActor_target 対象のアクター
     * @param prm_option オプション 特に意味無し。下位実装用
     */
    virtual void begin(GgafDx9GeometricActor* prm_pActor_target, int prm_option = 0);

    /**
     * 毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave();

    virtual ~GgafDx9SplineProgram();
};

}
#endif /*GGAFDX9SPLINEPROGRAM_H_*/
