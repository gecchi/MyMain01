#ifndef GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#define GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#include "GgafLibCommonHeader.h"
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
    /**
     * コンストラクタ .
     * @param prm_source_file スプライン座標情報ファイル
     */
    SteppedCoordSplineManufacture(const char* prm_source_file);

    /**
     * コンストラクタ .
     * @param prm_pSplSrc スプライン座標情報オブジェクト
     */
    SteppedCoordSplineManufacture(SplineSource* prm_pSplSrc);

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
