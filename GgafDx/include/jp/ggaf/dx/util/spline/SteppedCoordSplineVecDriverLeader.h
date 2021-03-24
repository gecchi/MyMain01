#ifndef GGAF_DX_STEPPEDCOORDSPLINEVECDRIVERLEADER_H_
#define GGAF_DX_STEPPEDCOORDSPLINEVECDRIVERLEADER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"

namespace GgafDx {

/**
 * スプライン曲線移動 .
 * 単純に、フレーム毎に順番に補完点座標へ移動。
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineVecDriverLeader : public SplineLeader {

public:
    GgafDx::VecDriver* _pVecDriver_target;
    SteppedCoordSplineManufacture* _pSteppedSplManuf;

    /** [r]補完点(基準点も含む)の数 */
    int _point_index;
    /** start()からの経過フレーム数 */
    frame _leading_frames;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pVecDriver 対象のアクターの力車
     */
    SteppedCoordSplineVecDriverLeader(SplineManufacture* prm_pManufacture, GgafDx::VecDriver* prm_pVecDriver);

    virtual void restart() override;
    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave() override;

    virtual ~SteppedCoordSplineVecDriverLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYSPLINEVECDRIVERLEADER_H_*/
