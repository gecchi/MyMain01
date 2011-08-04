#ifndef GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
#define GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_
namespace GgafDx9Core {

/**
 * 等速移動スプライン曲線移動。 .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class GgafDx9FixedVelocitySplineProgram : public SplineProgram {

public:
    /** [r]現在の補完点(基準点も含む)から、次の補完点(or基準点)までの距離のテーブル */
    coord* _paDistace_to;
    /** [r]始点からn番目の補完点(基準点も含む)到達に必要なフレーム数のテーブル */
    float* _paFrame_need_at;
    /** [r]基準速度 */
    velo _veloMvUnit;
    /** [rw]1フレームあたり旋回可能な回転角角速度 */
    ang_velo _ang_veloRzRyMv;
    /** [r]基準速度で移動した場合のスプライン移動時の経過フレーム数 */
    float _fFrame_executing;
    /** [r]次の変わり目となる補間点(基準点も含む)に到達する_fFrame_executing */
    float _fFrame_next_point;
    /** [r]補完点(基準点も含む)の数 */
    int _point_index;
    /**
     * [r]オプション
     * 0:絶対座標移動。
     * 1:始点を現座標とし、スプライン座標群は相対移動で計算。
     * 2:始点を現座標とし、さらに現在の向き（_pKurokoA の _angRzMv, _angRyMv)でスプライン座標群をワールド変換。
     */
    int _option;


    //計算用定数
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     * コンストラクタ .
     * @param prm_pActor 対象のアクター
     * @return
     */
    GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor);

    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pActor 対象のアクター
     * @param prm_paaCriteriaPoint 基点配列
     * @param prm_point_num  基点配列の要素数
     * @param prm_accuracy  1基点の精度（荒い 1.0 ～ 0.0 細かい)、
     *                      基点と基点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
     *                      1.0を指定した場合、基点から次基点まで何も無い（直線で結ぶイメージ）。
     *                      0.5 とすると基点から次基点までに補完点は1つ入る。
     *                      0.1 とすると基点と基点の間に補完点は9つ入る（なめらかなカーブになる）。
     * @param prm_ang_veloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     */
    GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor,
                                      double prm_paaCriteriaPoint[][3],
                                      int prm_point_num,
                                      double prm_accuracy,
                                      ang_velo prm_ang_veloRzRyMv);

    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pActor 対象のアクター
     * @param prm_sp 計算済みスプラインオブジェクト
     * @param prm_ang_veloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     * @return
     */
    GgafDx9FixedVelocitySplineProgram(GgafDx9GeometricActor* prm_pActor,
                                      Spline3D* prm_sp,
                                      ang_velo prm_ang_veloRzRyMv);

    /**
     * 初期化（計算）処理.
     * コンストラクタより呼び出されます。
     */
    void init();

    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void begin(int prm_option = 0) override;

    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave() override;


    virtual ~GgafDx9FixedVelocitySplineProgram();
};

}
#endif /*GGAFDX9FIXEDVELOCITYSPLINEPROGRAM_H_*/
