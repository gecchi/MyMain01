#ifndef GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#define GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * 等速移動による、スプライン曲線移動のための情報セット .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineManufacture : public SplineManufacture {

public:
    /** [r]現在の補完点(基準点も含む)から、次の補完点(or基準点)までの距離のテーブル */
    coord* _paDistance_to;
    /** [r]始点からn番目の補完点(基準点も含む)到達に必要なフレーム数のテーブル */
    float* _paFrame_need_at;
    /** [rw]旋回方法 */
    int _turn_way;
    /** [rw]旋回最適化有無 */
    bool _turn_optimize;
    /** [r]補完点(基準点も含む)の数 */
    int _point_index;

public:
    /**
     * コンストラクタ .
     * @param prm_source_file スプライン座標情報ファイル
     * @param prm_angveloRzRyMv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法(デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト true)
     */
    SteppedCoordSplineManufacture(const char* prm_source_file,
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = true );

    /**
     *
     * @param prm_pSplSrc スプライン座標情報オブジェクト
     * @param prm_angveloRzRyMv アクターの旋回角度
     * @param prm_turn_way アクターの旋回方法(デフォルト TURN_CLOSE_TO)
     * @param prm_turn_optimaize アクターの旋回の最適化オプション(デフォルト true)
     */
    SteppedCoordSplineManufacture(SplineSource* prm_pSplSrc,
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
     * インスタンスは SteppedCoordSplineKurokoLeader です。
     * @param prm_pKuroko スプライン移動させる対象アクター
     * @return SplineKurokoLeaderオブジェクト
     */
    SplineKurokoLeader* createKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko) override;

    virtual ~SteppedCoordSplineManufacture();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
