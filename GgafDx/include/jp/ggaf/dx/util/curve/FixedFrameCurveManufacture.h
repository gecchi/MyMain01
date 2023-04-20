#ifndef GGAF_DX_FIXEDFRAMECURVEMANUFACTURE_H_
#define GGAF_DX_FIXEDFRAMECURVEMANUFACTURE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

namespace GgafDx {

/**
 * 区間固定時間（フレーム）移動による、スプライン曲線移動のための情報セット .
 * 全てのアクターに共通するスプラインの情報はここに集約。
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameCurveManufacture : public CurveManufacture {

public:
    /** [r]１区間の使用可能フレーム */
    double _frame_of_segment;
    /** [r]次の補完点到達に必要な移動速度のテーブル */
    velo* _paSPMvVeloTo;
    /** [rw]1フレームあたり旋回可能な回転角角速度 */
    angvelo _angvelo_rzry_mv;
    /** [rw]旋回方法 */
    int _turn_way;
    /** [rw]旋回最適化有無 */
    bool _turn_optimize;
    /** [r]最終地点到着までのフレーム数 */
    frame _spent_frames;

public:
    /**
     * コンストラクタ .
     * @param prm_coord_spl_file スプライン座標情報ファイル
     * @param prm_spent_frames 始点(アクターの現座標ではない)～最終地点到着までのフレーム数
     * @param prm_angvelo_rzry_mv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法(デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト false)
     */
    FixedFrameCurveManufacture(const char* prm_coord_spl_file,
                                frame prm_spent_frames,
                                angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                                int prm_turn_way = TURN_CLOSE_TO,
                                bool prm_turn_optimaize = false );

    /**
     * コンストラクタ .
     * @param prm_pCurveSrc スプライン座標情報オブジェクト
     * @param prm_spent_frames 始点(アクターの現座標ではない)～最終地点到着までのフレーム数
     * @param prm_angvelo_rzry_mv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法 (デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト false)
     */
    FixedFrameCurveManufacture(CurveSource* prm_pCurve,
                               frame prm_spent_frames,
                               angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                               int prm_turn_way = TURN_CLOSE_TO,
                               bool prm_turn_optimaize = false );
    /**
     * 初期化（計算）処理 .
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     */
    void calculate() override;

    /**
     * 最終地点到着までのフレーム数を取得 .
     * @return
     */
    frame getSpentFrames() {
        return _spent_frames;
    }
    /**
     * 最終地点到着までのフレーム数を指定し、再計算する .
     * @param prm_spent_frames
     */
    void recalculateBySpentFrame(frame prm_spent_frames);

    /**
     * VehicleLeader オブジェクトの生成 .
     * インスタンスは FixedFrameCurveManufacture です。
     * @param prm_pLocoVehicle カーブ移動するための操作するオブジェクト
     * @return VehicleLeader オブジェクト
     */
    VehicleLeader* createLocoVehicleLeader(GgafDx::LocoVehicle* prm_pLocoVehicle) override;

    VehicleLeader* createCoordVehicleLeader(GgafDx::CoordVehicle* prm_pCoordVehicle) override;

    virtual ~FixedFrameCurveManufacture();
};

}
#endif /*GGAF_DX_FIXEDFRAMECURVEMANUFACTURE_H_*/
