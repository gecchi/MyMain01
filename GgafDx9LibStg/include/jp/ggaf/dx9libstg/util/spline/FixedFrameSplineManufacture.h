#ifndef FIXEDFRAMESPLINEMANUFACTURE_H_
#define FIXEDFRAMESPLINEMANUFACTURE_H_
namespace GgafDx9LibStg {

/**
 * 区間固定時間（フレーム）移動による、スプライン曲線移動のための情報セット .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineManufacture : public SplineManufacture {

public:
    /** [r]１区間の使用可能フレーム */
    frame _SPframe_segment;
    /** [r]次の補完点までの距離のテーブル */
    coord* _paDistace_to;
    /** [r]次の補完点到達に必要な移動速度のテーブル */
    velo* _paSPMvVeloTo;
    /** [rw]1フレームあたり旋回可能な回転角角速度 */
    ang_velo _ang_veloRzRyMv;
    /** [r]最終地点到着までのフレーム数 */
    frame _spent_frame;
    /**
     * コンストラクタ .
     * @param prm_source_file スプライン座標情報ファイル
     * @param prm_spent_frame 最終地点到着までのフレーム数
     * @param prm_ang_veloRzRyMv アクターの旋回角度
     */
    FixedFrameSplineManufacture(const char* prm_source_file, frame prm_spent_frame, ang_velo prm_ang_veloRzRyMv);
    FixedFrameSplineManufacture(SplineSource* prm_pSplineSource, frame prm_spent_frame, ang_velo prm_ang_veloRzRyMv);

    /**
     * 初期化（計算）処理 .
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     */
    void calculate() override;

    /**
     * SplineSequenceオブジェクトの生成 .
     * インスタンスは FixedFrameSplineManufacture です。
     * @param prm_pForWhichActor スプライン移動させる対象アクター
     * @return SplineSequenceオブジェクト
     */
    SplineSequence* createSplineSequence(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor) override;

    virtual ~FixedFrameSplineManufacture();
};

}
#endif /*FIXEDFRAMESPLINEMANUFACTURE_H_*/
