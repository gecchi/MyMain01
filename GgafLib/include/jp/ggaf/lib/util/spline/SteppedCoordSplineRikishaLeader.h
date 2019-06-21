#ifndef GGAF_LIB_STEPPEDCOORDSPLINERIKISHALEADER_H_
#define GGAF_LIB_STEPPEDCOORDSPLINERIKISHALEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

namespace GgafLib {

/**
 * スプライン曲線移動 .
 * 単純に、フレーム毎に順番に補完点座標へ移動。
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineRikishaLeader : public SplineLeader {

public:
    GgafDx::Rikisha* _pRikisha_target;
    SteppedCoordSplineManufacture* _pSteppedSplManuf;

    /** [r]補完点(基準点も含む)の数 */
    int _point_index;
    /** start()からの経過フレーム数 */
    frame _leading_frames;

public:
    /**
     * コンストラクタ .
     * @param prm_pManufacture
     * @param prm_pRikisha 対象のアクターの力車
     */
    SteppedCoordSplineRikishaLeader(SplineManufacture* prm_pManufacture, GgafDx::Rikisha* prm_pRikisha);

    virtual void restart() override;
    /**
     * 毎フレームの振る舞いメソッド .
     * 利用者は毎フレームこのメソッドを呼び出す必要があります。
     */
    virtual void behave() override;

    virtual ~SteppedCoordSplineRikishaLeader();
};

}
#endif /*GGAF_LIB_FIXEDVELOCITYSPLINERIKISHALEADER_H_*/
