#ifndef GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#define GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

namespace GgafDx {

/**
 * 座標移動による、スプライン曲線移動のための情報セット .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordCurveManufacture : public CurveManufacture {

public:
    /**
     * コンストラクタ .
     * @param prm_coord_data_file スプライン座標情報ファイル
     */
    SteppedCoordCurveManufacture(const char* prm_coord_data_file);

    /**
     * コンストラクタ .
     * @param prm_pCurveSrc スプライン座標情報オブジェクト
     */
    SteppedCoordCurveManufacture(CurveSource* prm_pCurve);

    /**
     * 初期化（計算）処理 .
     * プロパティを変更した場合、内部テーブル情報を更新するために
     * 一度実行する必要があります。
     */
    void calculate() override;

    /**
     * DriverLeader オブジェクトの生成 .
     * インスタンスは SteppedCoordCurveVecDriverLeader です。
     * @param GgafDx::GeoDriver スプライン移動するための操作するオブジェクト
     * @return DriverLeader オブジェクト
     */
    DriverLeader* createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) override;

    virtual ~SteppedCoordCurveManufacture();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEMANUFACTURE_H_*/
