#ifndef GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_
#define GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * 等速移動による、スプライン曲線移動のための情報セット .
 * 全てのアクターに共通するスプラインの情報はここに集約。<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineManufacture : public SplineManufacture {

public:
    /** [r]始点からn番目の補完点(基準点も含む)到達に必要なフレーム数のテーブル */
    float* _paFrame_need_at;
    /** [r]基準速度 */
    velo _velo_mvUnit;
    /** [rw]1フレームあたり旋回可能な回転角角速度 */
    angvelo _angvelo_rzry_mv;
        /** [rw]旋回方法 */
    int _turn_way;
    /** [rw]旋回最適化有無 */
    bool _turn_optimize;

public:
    /**
     * コンストラクタ .
     * @param prm_coord_data_file スプライン座標情報ファイル
     * @param prm_angvelo_rzry_mv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法(デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト false)
     */
    FixedVelocitySplineManufacture(const char* prm_coord_data_file,
                                   angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = false );

    /**
     *
     * @param prm_pSplSrc スプライン座標情報オブジェクト
     * @param prm_angvelo_rzry_mv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法(デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト false)
     */
    FixedVelocitySplineManufacture(SplineSource* prm_pSpl,
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
     * SplineLeader オブジェクトの生成 .
     * インスタンスは FixedVelocitySplineKurokoLeader です。
     * @param prm_pKuroko スプライン移動するための操作するオブジェクト
     * @return SplineLeader オブジェクト
     */
    SplineLeader* createKurokoLeader(GgafDxCore::GgafDxKuroko* prm_pKuroko) override;

    virtual ~FixedVelocitySplineManufacture();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
