#ifndef SPLINEMANUFACTURE_H_
#define SPLINEMANUFACTURE_H_
namespace GgafDx9LibStg {

/**
 * スプライン曲線移動のための情報セット .
 * 補完点に移動するため、粒度が荒いとカクカクです。
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineManufacture : public GgafCore::GgafObject {
private:
    SplineSourceConnection* _pSplineSourceConnection;
    SplineSource* _pSplineSource;
public:

    /** スプライン曲線の補完点生成、保持するクラス */
    Spline3D* _sp;
//    /** [r]１区間の使用可能フレーム */
//    frame _SPframe_segment;

//    /** begin()からの経過フレーム数 */
//    frame _SPframe;
//    /** 現在プログラム実行中であるかどうか */
//    bool _is_executing;
//    /** 座標を操作する対象となるアクター */
//    GgafDx9Core::GgafDx9GeometricActor* _pActor_target;
    /** コンストラクタ内部でSpline3Dを生成した場合true/コンストラクタ引数にSpline3Dが渡された場合、false */
    bool _is_create_sp;
//    /** [r]始点X座標 */
//    coord _X_begin;
//    /** [r]始点Y座標 */
//    coord _Y_begin;
//    /** [r]始点Z座標 */
//    coord _Z_begin;
    float _rate_X;
    float _rate_Y;
    float _rate_Z;

//    /**
//     * コンストラクタ .
//     * Spline3Dオブジェクトの参照を後から設定して下さい。（setSpline() メソッドで）
//     * @param prm_pActor_target 対象のアクター
//     */
//    SplineManufacture(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_target);
//
//
//    /**
//     * コンストラクタ .
//     * 引数から内部でSpline3Dを生成しスプライン曲線補完点を計算します。
//     * Spline3Dオブジェクトの解放も内部で行われます。
//     * @param prm_pActor_target 対象のアクター
//     * @param prm_paaCriteriaPoint 基点配列
//     * @param prm_point_num  基点配列の要素数
//     * @param prm_accuracy  1基点の精度（荒い 1.0 〜 0.0 細かい)、
//     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
//     *                      1の場合基点から次基点まで何も無い（直線）。
//     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
//     *                      0.1 とすると基点と基点の間に補完点は9つ。
//     */
//    SplineManufacture(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_target,
//                         double prm_paaCriteriaPoint[][3],
//                         int prm_point_num,
//                         double prm_accuracy);
    /**
     * コンストラクタ .
     * 引数の生成済みSpline3Dオブジェクトを利用します。Spline3Dの解放は、呼び出し元で行ってください。
     * たくさんのオブジェクトに同じ動きをさせる場合は、こちらのコンストラクタで生成すべきです。
     * @param prm_pActor_target 対象のアクター
     * @param prm_sp スプライン曲線の補完点生成、保持クラスのインスタンス
     */
//    SplineManufacture(GgafDx9Core::GgafDx9GeometricActor* prm_pActor,
//                      Spline3D* prm_sp,
//                      frame prm_spent_frame,
//                      ang_velo prm_ang_veloRzRyMv);
    SplineManufacture();
    SplineManufacture(char* prm_idstr, const char* prm_sourceid);


    /**
     * 各補完点を読み込み時、X軸方向、Y軸方向、Z軸方向それぞれに割合を乗じ、補正します .
     * デフォルトは adjustAxisRate(1.0, 1.0, 1.0) となります。<BR>
     * <b>[注意]</b><BR>
     * 内部で、adjustCoodOffset() よりも先に 本メソッドの adjustAxisRate() が考慮されます。<BR>
     * 軸方向の倍率補正 ＞ 平行移動補正 の順番です。<BR>
     * @param prm_rate_X X軸方向補正割合
     * @param prm_rate_Y Y軸方向補正割合
     * @param prm_rate_Z Z軸方向補正割合
     */
    virtual void adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z);


//    /**
//     * 対象アクター(_pActor_target)の座標を、スプラインの一番最初の基点座標で設定する .
//     * begin(0) の場合、つまり「絶対座標移動スプライン」の場合、有効な設定となりうるでしょう。<BR>
//     * 「絶対座標移動スプライン」あまり意味がありません。<BR>
//     */
//    void setAbsoluteBeginCoordinate();

    /**
     * 後からスプラインオブジェクトを設定。
     * @param prm_sp
     */
    virtual void setSpline(Spline3D* prm_sp);

//    /**
//     * スプライン曲線の補完点を移動するプログラムを実行開始
//     * @param prm_option オプション 特に意味無し。下位実装拡張用
//     */
//    virtual void begin(int prm_option = 0);
//
//    /**
//     * 移動実行メソッド .
//     * 移動を行うために、毎フレームこのメソッドを呼び出す必要があります。
//     */
//    virtual void behave();
//
//    /**
//     * スプライン移動プログラム実行中か
//     * @return true:実行中 / false:実行が終了している
//     */
//    bool isExecuting() {
//        return _is_executing;
//    }
    virtual void calculate() = 0;
    virtual SplineProgram* createSplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor) = 0;


    virtual ~SplineManufacture();
};

}
#endif /*SPLINEMANUFACTURE_H_*/
