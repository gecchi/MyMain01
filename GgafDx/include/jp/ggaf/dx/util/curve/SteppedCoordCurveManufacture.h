#ifndef GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#define GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
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
     * @param prm_coord_spl_file スプライン座標情報ファイル
     */
    SteppedCoordCurveManufacture(const char* prm_coord_spl_file);

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
     * VehicleLeader オブジェクトの生成 .
     * インスタンスは SteppedCoordCurveVecVehicleLeader です。
     * @param GgafDx::AxisVehicle カーブ移動するための操作するオブジェクト
     * @return VehicleLeader オブジェクト
     */
    VehicleLeader* createVecVehicleLeader(GgafDx::VecVehicle* prm_pVecVehicle) override;

    virtual ~SteppedCoordCurveManufacture();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEMANUFACTURE_H_*/
