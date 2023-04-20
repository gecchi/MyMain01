#ifndef GGAF_DX_STEPPEDCOORDCURVELOCOVEHICLELEADER_H_
#define GGAF_DX_STEPPEDCOORDCURVELOCOVEHICLELEADER_H_
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
class SteppedCoordCurveLocoVehicleLeader : public VehicleLeader {

public:
    GgafDx::LocoVehicle* _pLocoVehicle_target;
    SteppedCoordCurveManufacture* _pSteppedSplManuf;

    /** [r]補完点(基準点も含む)の数 */
    int _point_index;
    /** start()からの経過フレーム数 */
    frame _leading_frames;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pLocoVehicle 対象のアクターの移動車両
     */
    SteppedCoordCurveLocoVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::LocoVehicle* prm_pLocoVehicle);

    virtual void restart() override;
    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave() override;

    virtual ~SteppedCoordCurveLocoVehicleLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVELOCOVEHICLELEADER_H_*/
