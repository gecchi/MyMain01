#ifndef GGAF_DX_STEPPEDCOORDCURVELOCUSVEHICLELEADER_H_
#define GGAF_DX_STEPPEDCOORDCURVELOCUSVEHICLELEADER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * スプライン曲線移動 .
 * 単純に、フレーム毎に順番に補完点座標へ移動。
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordCurveLocusVehicleLeader : public VehicleLeader {

public:
    GgafDx::LocusVehicle* _pLocusVehicle_target;
    SteppedCoordCurveManufacture* _pSteppedSplManuf;

    /** [r]補完点(基準点も含む)の数 */
    int _point_index;
    /** start()からの経過フレーム数 */
    frame _leading_frames;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pLocusVehicle 対象のアクターの移動車両
     */
    SteppedCoordCurveLocusVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::LocusVehicle* prm_pLocusVehicle);

    virtual void restart() override;
    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave() override;

    virtual ~SteppedCoordCurveLocusVehicleLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVELOCUSVEHICLELEADER_H_*/
