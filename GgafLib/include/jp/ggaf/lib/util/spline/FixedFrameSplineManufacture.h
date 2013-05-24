#ifndef FIXEDFRAMESPLINEMANUFACTURE_H_
#define FIXEDFRAMESPLINEMANUFACTURE_H_
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * 区間固定時間（フレーム）移動による、スプライン曲線移動のための情報セット .
 * 全てのアクターに共通するスプラインの情報はここに集約。
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineManufacture : public SplineManufacture {

public:
    /** [r]１区間の使用可能フレーム */
    float _fFrame_of_segment;
    /** [r]次の補完点到達に必要な移動速度のテーブル */
    velo* _paSPMvVeloTo;
    /** [rw]1フレームあたり旋回可能な回転角角速度 */
    angvelo _angveloRzRyMv;
    /** [rw]旋回方法 */
    int _turn_way;
    /** [rw]旋回最適化有無 */
    bool _turn_optimize;
    /** [r]最終地点到着までのフレーム数 */
    frame _spent_frame;

public:
    /**
     * コンストラクタ .
     * @param prm_source_file スプライン座標情報ファイル
     * @param prm_spent_frame 始点(アクターの現座標ではない)～最終地点到着までのフレーム数
     * @param prm_angveloRzRyMv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法(デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト true)
     */
    FixedFrameSplineManufacture(const char* prm_source_file,
                                frame prm_spent_frame,
                                angvelo prm_angveloRzRyMv = (D90ANG/9),
                                int prm_turn_way = TURN_CLOSE_TO,
                                bool prm_turn_optimaize = true );

    /**
     * コンストラクタ .
     * @param prm_pSplSrc スプライン座標情報オブジェクト
     * @param prm_spent_frame 始点(アクターの現座標ではない)～最終地点到着までのフレーム数
     * @param prm_angveloRzRyMv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法 (デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト true)
     */
    FixedFrameSplineManufacture(SplineSource* prm_pSplSrc,
                                frame prm_spent_frame,
                                angvelo prm_angveloRzRyMv = (D90ANG/9),
                                int prm_turn_way = TURN_CLOSE_TO,
                                bool prm_turn_optimaize = true );
    /**
     * 初期化（計算）処理 .
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     */
    void calculate() override;

    /**
     * SplineKurokoLeaderオブジェクトの生成 .
     * インスタンスは FixedFrameSplineManufacture です。
     * @param prm_pKurokoA スプライン移動させる対象アクター
     * @return SplineKurokoLeaderオブジェクト
     */
    SplineKurokoLeader* createKurokoLeader(GgafDxCore::GgafDxKurokoA* prm_pKurokoA) override;

    virtual ~FixedFrameSplineManufacture();
};

}
#endif /*FIXEDFRAMESPLINEMANUFACTURE_H_*/
