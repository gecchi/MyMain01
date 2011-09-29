#ifndef FIXEDVELOCITYSPLINESEQUENCE_H_
#define FIXEDVELOCITYSPLINESEQUENCE_H_
namespace GgafLib {

/**
 * 等速移動スプライン曲線移動。 .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineSequence : public SplineSequence {

public:
    FixedVelocitySplineManufacture* _pFixedVeloSplManuf;

//    /** [r]現在の補完点(基準点も含む)から、次の補完点(or基準点)までの距離のテーブル */
//    coord* _paDistace_to;
//    /** [r]始点からn番目の補完点(基準点も含む)到達に必要なフレーム数のテーブル */
//    float* _paFrame_need_at;
    /** [r]基準速度 */
//    velo _veloMvUnit;
//    /** [rw]1フレームあたり旋回可能な回転角角速度 */
//    ang_velo _ang_veloRzRyMv;
    /** [r]基準速度で移動した場合のスプライン移動時の経過フレーム数 */
    float _exec_fFrames;
    /** [r]次の変わり目となる補間点(基準点も含む)に到達する_exec_fFrames */
    float _fFrame_of_next;
    /** [r]補完点(基準点も含む)の数 */
    int _point_index;


    //計算用
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    /**
     *
     * @param prm_pManufacture calculate()済みのSplineManufactureを設定すること
     * @param prm_pKurokoA
     */
    FixedVelocitySplineSequence(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);
//    /**
//     * コンストラクタ .
//     * 後から色々設定する場合のコンストラクタ
//     * @param prm_pActor 対象のアクター
//     */
//    FixedVelocitySplineSequence(GgafDxCore::GgafDxGeometricActor* prm_pActor);
//
//    /**
//     * コンストラクタ .
//     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
//     * @param prm_pActor 対象のアクター
//     * @param prm_paaCriteriaPoint 制御点配列
//     * @param prm_point_num  制御点配列の要素数
//     * @param prm_accuracy  1制御点の精度（荒い 1.0 ～ 0.0 細かい)、
//     *                      制御点と制御点の間を1とした場合の、補完点の入り具合（細やかさ）を指定。
//     *                      1.0を指定した場合、制御点から次制御点まで何も無い（直線で結ぶイメージ）。
//     *                      0.5 とすると制御点から次制御点までに補完点は1つ入る。
//     *                      0.1 とすると制御点と制御点の間に補完点は9つ入る（なめらかなカーブになる）。
//     * @param prm_ang_veloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
//     */
//    FixedVelocitySplineSequence(GgafDxCore::GgafDxGeometricActor* prm_pActor,
//                               double prm_paaCriteriaPoint[][3],
//                               int prm_point_num,
//                               double prm_accuracy,
//                               ang_velo prm_ang_veloRzRyMv);
//
    /**
     * コンストラクタ .
     * 等速移動のための必要な情報を事前計算し、オブジェクトに溜め込みます。
     * @param prm_pActor 対象のアクター
     * @param prm_sp 計算済みスプラインオブジェクト
     * @param prm_ang_veloRzRyMv 1フレームあたりの旋回可能な回転角角速度 (1000 が 1度)
     * @return
     */
    FixedVelocitySplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                               SplineLine* prm_sp,
                               ang_velo prm_ang_veloRzRyMv);


    /**
     * スプライン曲線利用のフレーム数指定移動プログラム開始
     * @param prm_option オプション 0:絶対座標移動／1:始点をActorの現座標とみなし、そこからの相対座標移動
     */
    void exec(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    void behave() override;


    virtual ~FixedVelocitySplineSequence();
};

}
#endif /*FIXEDVELOCITYSPLINESEQUENCE_H_*/
