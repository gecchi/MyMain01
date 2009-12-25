#ifndef GGAFDX9SPLINEPROGRAM_H_
#define GGAFDX9SPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * スプライン曲線移動のための情報セット .
 * 補完点に移動するため、粒度が荒いとカクカクです。
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class GgafDx9SplineProgram : public GgafCore::GgafObject {

public:
    /** スプライン曲線の補完点生成、保持するクラス */
    GgafDx9Spline3D* _sp;
    /** begin()からの経過フレーム数 */
    DWORD _SPframe;
    /** 現在プログラム実行中であるかどうか */
    boolean _is_executing;
    /** 座標を操作する対象となるアクター */
    GgafDx9GeometricActor* _pActor_target;
    /** コンストラクタ内部でGgafDx9Spline3Dを生成した場合true/コンストラクタ引数にGgafDx9Spline3Dが渡された場合、false */
    bool _is_create_sp;

    /**
     * コンストラクタ .
     * GgafDx9Spline3Dオブジェクトの参照を後から設定して下さい。
     */
    GgafDx9SplineProgram();


    /**
     * コンストラクタ .
     * 引数から内部でGgafDx9Spline3Dを生成しスプライン曲線補完点を計算します。
     * GgafDx9Spline3Dオブジェクトの解放も内部で行われます。
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
     * コンストラクタ .
     * 引数のGgafDx9Spline3Dを利用します。GgafDx9Spline3Dの解放は、呼び出し元で行ってください。
     * たくさんのオブジェクトに同じ動きをさせる場合は、こちらのコンストラクタで生成すべきです。
     * @param prm_sp スプライン曲線の補完点生成、保持クラスのインスタンス
     */
    GgafDx9SplineProgram(GgafDx9Spline3D* prm_sp);


    virtual void setSpline(GgafDx9Spline3D* prm_sp);
    /**
     * スプライン曲線の補完点を移動するプログラムを実行開始
     * @param prm_pActor_target 対象のアクター
     * @param prm_option オプション 特に意味無し。下位実装拡張用
     */
    virtual void begin(GgafDx9GeometricActor* prm_pActor_target, int prm_option = 0);

    /**
     * 移動実行メソッド .
     * 移動を行うために、毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave();

    /**
     * スプライン移動プログラム実行中か
     * @return true:実行中 / false:実行が終了している
     */
    bool isExecuting() {
        return _is_executing;
    }

    virtual ~GgafDx9SplineProgram();
};

}
#endif /*GGAFDX9SPLINEPROGRAM_H_*/
