#ifndef GGAF_DX_STEPPEDCOORDSPLINEMANUFACTURE_H_
#define GGAF_DX_STEPPEDCOORDSPLINEMANUFACTURE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/spline/SplineManufacture.h"

namespace GgafDx {

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
     * @param prm_coord_data_file スプライン座標情報ファイル
     */
    SteppedCoordSplineManufacture(const char* prm_coord_data_file);

    /**
     * コンストラクタ .
     * @param prm_pSplSrc スプライン座標情報オブジェクト
     */
    SteppedCoordSplineManufacture(SplineSource* prm_pSpl);

    /**
     * 初期化（計算）処理 .
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     */
    void calculate() override;

    /**
     * SplineLeader オブジェクトの生成 .
     * インスタンスは SteppedCoordSplineVecDriverLeader です。
     * @param GgafDx::GeoDriver スプライン移動するための操作するオブジェクト
     * @return SplineLeader オブジェクト
     */
    SplineLeader* createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) override;

    virtual ~SteppedCoordSplineManufacture();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
