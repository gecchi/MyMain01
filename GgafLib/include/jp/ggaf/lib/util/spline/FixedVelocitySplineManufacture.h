#ifndef FIXEDVELOCITYSPLINEMANUFACTURE_H_
#define FIXEDVELOCITYSPLINEMANUFACTURE_H_
namespace GgafLib {

/**
 * 等速移動による、スプライン曲線移動のための情報セット .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineManufacture : public SplineManufacture {

public:
    /** [r]現在の補完点(基準点も含む)から、次の補完点(or基準点)までの距離のテーブル */
    coord* _paDistace_to;
    /** [r]始点からn番目の補完点(基準点も含む)到達に必要なフレーム数のテーブル */
    float* _paFrame_need_at;
    /** [r]基準速度 */
    velo _veloMvUnit;
    /** [rw]1フレームあたり旋回可能な回転角角速度 */
    ang_velo _ang_veloRzRyMv;
        /** [rw]旋回方法 */
    int _turn_way;
    /** [rw]旋回最適化有無 */
    bool _turn_optimize;
    /** [r]補完点(基準点も含む)の数 */
    int _point_index;

    /**
     * コンストラクタ .
     * @param prm_source_file スプライン座標情報ファイル
     * @param prm_ang_veloRzRyMv アクターの旋回角度
     */
    FixedVelocitySplineManufacture(const char* prm_source_file,
                                   ang_velo prm_ang_veloRzRyMv = (D90ANG/9),
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = true );

    FixedVelocitySplineManufacture(SplineSource* prm_pSplSrc,
                                   ang_velo prm_ang_veloRzRyMv = (D90ANG/9),
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = true );

    /**
     * 初期化（計算）処理 .
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     */
    void calculate() override;

    /**
     * SplineSequenceオブジェクトの生成 .
     * インスタンスは FixedVelocitySplineSequence です。
     * @param prm_pKurokoA スプライン移動させる対象アクター
     * @return SplineSequenceオブジェクト
     */
    SplineSequence* createSplineSequence(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) override;

    virtual ~FixedVelocitySplineManufacture();
};

}
#endif /*FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
